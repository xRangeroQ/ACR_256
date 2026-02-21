// Include Libraries
#include <cctype>
#include <chrono>
#include <iostream>
#include <algorithm>
#include "../Source/cryptography.hpp"

// Using Namespaces
using namespace std;

// ToLower Function
string ToLower(const string &Content)
{
    string Word = Content;
    transform(Word.begin(), Word.end(), Word.begin(), [](unsigned char c){return tolower(c);});
    return Word;
}

// Main Function
int main(int argc, char* argv[])
{
    // Init Variables
    auto StartTime = chrono::high_resolution_clock::now();
    string Content = "Example Content";
    
    // Create Cryptography
    Cryptography Crypto;
    Crypto.SetKey();

    // Create Buffers
    string CipherText; bool CipherStatus = true;
    string PlainText;

    // Get Arguments
    for (int i = 1; i < argc; i++)
    {
        // Variables
        string Argument = ToLower(argv[i]);
        string AfterArgument = (i + 1 < argc) ? argv[i + 1] : "";

        // Terminal Commands
        if (Argument == "--content" && (i + 1 < argc)) { Content = argv[i + 1]; i++; }
        else if (Argument == "--set-key" && (i + 1 < argc)) { Crypto.SetKey(&AfterArgument); i++; }
        else if (Argument == "-d" && (i + 1 < argc)) {CipherText = AfterArgument; CipherStatus = false; i++; }

    }

    // Encrypt && Decrypt
    if (CipherStatus) CipherText = Crypto.Encrypt(Content);
    PlainText = Crypto.Decrypt(CipherText);

    // End Time
    auto EndTime = chrono::high_resolution_clock::now();

    // Display
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << "Key Base64 >> " << Crypto.LoadKey() << endl;
    cout << "Cipher Text >> " << CipherText << endl;
    cout << "Plain Text >> " << PlainText << endl;
    cout << "Duration Time >> " << chrono::duration_cast<chrono::milliseconds>(EndTime - StartTime).count() << "ms" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;

    // Return Function
    return 0;
}
