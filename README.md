# cryptor

use xor encryption/decryption + base64 encode/decode

## test

```
g++ -std=c++11 test.cpp -o test
./test
```

## fast sample:

```cpp
#include <iostream>
using namespace std;

#include "cryptor.hpp"

int main()
{
    auto enc = cryptor::encrypt("hello world");
    auto dec = cryptor::decrypt(enc);
    cout << "enc: " << enc << endl;
    cout << "dec: " << dec << endl;
}
```

output:

```
enc: DAAKDRpMAzAZCR0=
dec: hello world
```

## use custom key sample:

```cpp
#include <iostream>
using namespace std;

#include "cryptor.hpp"

int main()
{
    cryptor::set_key("it is my custom key!");
    auto enc = cryptor::encrypt("hello world");
    auto dec = cryptor::decrypt(enc);
    cout << "key: " << cryptor::get_key() << endl;
    cout << "enc: " << enc << endl;
    cout << "dec: " << dec << endl;
}
```

output:

```
key: it is my custom key!
enc: ARFMBRwAGhZSDxE=
dec: hello world
```
