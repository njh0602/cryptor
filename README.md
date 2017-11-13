# cryptor

xor encrytion/decryption, base64 encode/decode

## sample:

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

