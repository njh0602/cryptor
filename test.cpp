#include <iostream>
using namespace std;

#include "cryptor.hpp"

int main()
{
    auto test_str = "hello world";
    
    {
        // test 1
        // use default key
        cout << "[test #1]" << endl;
        auto enc = cryptor::encrypt(test_str);
        auto dec = cryptor::decrypt(enc);
        cout << "key: " << cryptor::get_key() << endl;
        cout << "origin: " << test_str << endl;
        cout << "enc: " << enc << endl;
        cout << "dec: " << dec << endl;
    }
    
    cout << endl;
    
    {
        // test 2
        // use custom key
        cout << "[test #2]" << endl;
        cryptor::set_key("it is my custom key!");
        auto enc = cryptor::encrypt(test_str);
        auto dec = cryptor::decrypt(enc);
        cout << "key: " << cryptor::get_key() << endl;
        cout << "origin: " << test_str << endl;
        cout << "enc: " << enc << endl;
        cout << "dec: " << dec << endl;
    }
}
