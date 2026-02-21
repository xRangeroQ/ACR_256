// Include Guard
#ifndef BASE64_HPP
#define BASE64_HPP

// Include Libraries
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <openssl/evp.h>

// Using Namespace(s)
using namespace std;

// Class Base64
class Base64
{
    public:
        // Base64 Methods (Encode and Decode)
        static string Encode(const vector<uint8_t> &Content);
        static vector<uint8_t> Decode(const string &Content);
};

// End If
#endif
