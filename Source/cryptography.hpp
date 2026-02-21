// Include Guard
#ifndef CRYPTOGRAPHY_HPP
#define CRYPTOGRAPHY_HPP

// Build Control
#ifdef DYNAMIC_BUILD
    #ifdef BUILD
        #define API __declspec(dllexport)
    #else
        #define API __declspec(dllimport)
    #endif
#else
    #define API
#endif

// Include Libraries
#include <ctime>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <stdexcept>
#include <openssl/evp.h>
#include <openssl/rand.h>

// Include Header(s)
#include "DataStruct/datastruct.h"
#include "Base64/base64.hpp"
#include "Parser/parser.hpp"

// Using Namespaces
using namespace std;

// Class Cryptography
class API Cryptography
{
    private:
        // Variables
        EVP_CIPHER_CTX* evp;
        vector<uint8_t> Key;

    public:
        // Destructor
        ~Cryptography()
        {
            // Free Context
            if (evp) EVP_CIPHER_CTX_free(evp);
        }

        // AES Methods
        string Encrypt(const string &Content);
        string Decrypt(const string &Content);

        // Key Methods
        string LoadKey();
        void SetKey();
        void SetKey(string *Key);
        void SetKey(vector<uint8_t> *Key);
        
};

// End If
#endif
