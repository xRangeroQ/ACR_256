// Include Header(s)
#include "base64.hpp"

// Encode
string Base64::Encode(const vector<uint8_t> &Content)
{
    // Base64 Operations
    int ExpectedSize = EVP_ENCODE_LENGTH(Content.size());                                                                      // Get Expected Output Size
    vector<uint8_t> EncodedContent(ExpectedSize);                                                                              // Create Buffer
    int ActualSize = EVP_EncodeBlock(EncodedContent.data(), reinterpret_cast<const uint8_t*>(Content.data()), Content.size()); // Get Actual Output Data and Size

    // Final Resize
    EncodedContent.resize(ActualSize);

    // Return Content
    return string(EncodedContent.begin(), EncodedContent.begin() + ActualSize);
}

// Decode
vector<uint8_t> Base64::Decode(const string &Content)
{
    // Base64 Operations
    int ExpectedSize = EVP_DECODE_LENGTH(Content.size());                                                                      // Get Expected Data Size
    vector<uint8_t> DecodedContent(ExpectedSize);                                                                              // Create Output Buffer
    int ActualSize = EVP_DecodeBlock(DecodedContent.data(), reinterpret_cast<const uint8_t*>(Content.data()), Content.size()); // Get Actual Data Size

    // Clear Paddings
    int Padding = 0;
    if (Content.length() > 0 && Content[Content.length() - 1] == '=') Padding++;
    if (Content.length() > 1 && Content[Content.length() - 2] == '=') Padding++;

    // Final Resize
    int FinalSize = ActualSize - Padding;
    if (FinalSize < 0) throw runtime_error("Invalid Base64 Format!");
    DecodedContent.resize(FinalSize);

    // Return Content
    return DecodedContent;
}
