//
//  cryptor.hpp
//  realtrick games
//
//  Created by NamJunHyeon on 2017. 11. 12..
//
//  origin base64 eocnde/decode source : https://github.com/ReneNyffenegger/cpp-base64
//


#pragma once

#include <string>
#include <type_traits>

template <typename dummy>
class cryptor_static_base
{
protected:
    static const std::string m_base64_chars;
    static std::string m_key;
};

template <typename dummy>
const std::string cryptor_static_base<dummy>::m_base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

template <typename dummy>
std::string cryptor_static_base<dummy>::m_key = "default_key";

class cryptor : public cryptor_static_base<void>
{
    
public:
    
    cryptor() = delete;
    
    template <typename buffer_type>
    static decltype(auto) encrypt(buffer_type&& in, const std::string& key = m_key)
    {
        return base64_encode(do_xor(std::forward<buffer_type>(in), key, std::is_same<const char*, std::decay_t<buffer_type>>()));
    }
    
    template <typename buffer_type>
    static decltype(auto) decrypt(buffer_type&& in, const std::string& key = m_key)
    {
        return do_xor(base64_decode(std::forward<buffer_type>(in), std::is_same<const char*, std::decay_t<buffer_type>>()),
                      key, std::is_same<const char*, std::decay_t<buffer_type>>());
    }
    
    static const std::string& get_key() { return m_key; }
    static void set_key(const std::string& key) { m_key = key; }
    
private:
    
    template <typename buffer_type>
    static decltype(auto) do_xor(buffer_type&& data, const std::string& key, std::true_type)
    {
        std::string ret(data);
        xor_impl(ret, key);
        return ret;
    }
    
    template <typename buffer_type>
    static decltype(auto) do_xor(buffer_type&& data, const std::string& key, std::false_type)
    {
        std::decay_t<buffer_type> ret(std::forward<buffer_type>(data));
        xor_impl(ret, key);
        return ret;
    }
    
    template <typename buffer_type>
    static void xor_impl(buffer_type& data, const std::string& key)
    {
        for (int i = 0; i < data.size(); ++i)
        {
            data[i] ^= key.at(i % key.size());
        }
    }
    
    template <typename buffer_type>
    static decltype(auto) base64_encode(buffer_type&& in)
    {
        buffer_type ret;
        
        auto bytes_to_encode = in.data();
        auto in_len = in.size();
        
        int i = 0;
        int j = 0;
        uint8_t char_array_3[3];
        uint8_t char_array_4[4];
        
        while (in_len--)
        {
            char_array_3[i++] = *(bytes_to_encode++);
            if (i == 3)
            {
                char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
                char_array_4[3] = char_array_3[2] & 0x3f;
                
                for (i = 0; i < 4 ; ++i)
                {
                    ret.push_back(m_base64_chars.at(char_array_4[i]));
                }
                
                i = 0;
            }
        }
        
        if (i)
        {
            for (j = i; j < 3; ++j)
            {
                char_array_3[j] = '\0';
            }
            
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            
            for (j = 0; j < i + 1; ++j)
            {
                ret.push_back(m_base64_chars.at(char_array_4[j]));
            }
            
            while ( i++ < 3 )
            {
                ret.push_back('=');
            }
        }
        
        return ret;
    }
    
    template <typename buffer_type>
    static decltype(auto) base64_decode(buffer_type&& encoded_data, std::true_type)
    {
        std::string buffer(encoded_data), out;
        base64_decode_impl(std::move(buffer), out);
        return out;
    }
    
    template <typename buffer_type>
    static decltype(auto) base64_decode(buffer_type&& encoded_data, std::false_type)
    {
        std::decay_t<buffer_type> out;
        base64_decode_impl(std::forward<buffer_type>(encoded_data), out);
        return out;
    }
    
    template <typename buffer_type, typename out_type>
    static void base64_decode_impl(buffer_type&& encoded_data, out_type& out)
    {
        auto in_len = encoded_data.size();
        int i = 0;
        int j = 0;
        int in_ = 0;
        uint8_t char_array_4[4], char_array_3[3];
        
        while (in_len-- && ( encoded_data[in_] != '=') && is_base64(encoded_data[in_]))
        {
            char_array_4[i++] = encoded_data[in_]; in_++;
            if ( i == 4 )
            {
                for (i = 0; i <4; ++i)
                {
                    char_array_4[i] = m_base64_chars.find(char_array_4[i]);
                }
                
                char_array_3[0] = ( char_array_4[0] << 2       ) + ((char_array_4[1] & 0x30) >> 4);
                char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
                char_array_3[2] = ((char_array_4[2] & 0x3) << 6) +   char_array_4[3];
                
                for (i = 0; i < 3; ++i)
                {
                    out.push_back(char_array_3[i]);
                }
                
                i = 0;
            }
        }
        
        if ( i )
        {
            for (j = 0; j < i; ++j)
            {
                char_array_4[j] = m_base64_chars.find(char_array_4[j]);
            }
            
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            
            for (j = 0; j < i - 1; ++j)
            {
                out.push_back(char_array_3[j]);
            }
        }
    }
    
    static bool is_base64(uint8_t c)
    {
        return (isalnum(c) || (c == '+') || (c == '/'));
    }
    
};

