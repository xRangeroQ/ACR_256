// Include Libraries
#include <iostream>
#include "../Source/cryptography.hpp"

// Using Namespace(s)
using namespace std;

// Main Function
int main()
{
  // Initialization
  Cryptography Crypto;              // Create Cryptography Object
  Crypto.SetKey();                  // Sets Key (If the parameter is left blank, it will generate a random key.)
  cout << Crypto.LoadKey() << endl; // Get Base64 Encoded Key

  // Variables
  string Content = "Test Content";
  string CipherText;
  string PlainText;

  // Encrypt and Decrypt Methods
  CipherText = Crypto.Encrypt(Content); // Encrypt (It encrypts the given value and returns an output.)
  PlainText = Crypto.Decrypt(Content);  // Decrypt (It decrypts the given value and returns an output.)

  // Display
  cout << CipherText << endl;
  cout << PlainText << endl;

  // Return Function
  return 0;
  
}
