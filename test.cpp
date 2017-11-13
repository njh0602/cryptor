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
