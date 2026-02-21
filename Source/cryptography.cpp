// Include Headaer(s)
#include "cryptography.hpp"

// Encrypt
string Cryptography::Encrypt(const string &Content)
{
    // Create Timestamp
    uint64_t TimestampFullNow = static_cast<uint64_t>(time(nullptr));              // Get Unix Timestamp 8 Byte
    uint8_t* TimestampStriptedNow = reinterpret_cast<uint8_t*>(&TimestampFullNow); // Get Unix Timestamp 1 byte * 8 Part

    // Create Content and Buffer
    vector<uint8_t> Version{0x02};                                                         // Create and Fill Version Byte
    vector<uint8_t> Timestamp{TimestampStriptedNow, TimestampStriptedNow + CCL.Timestamp}; // Create and Fill Timestamp
    vector<uint8_t> IV(CCL.IV);                                                            // Create IV Buffer
    vector<uint8_t> Tag(CCL.Tag);                                                          // Create Tag Buffer
    vector<uint8_t> CipherContent(Content.size());                                         // Create Content Buffer
    int Length = 0;                                                                        // Create Content Length
    int CipherContentLength = 0;                                                           // Create Final Content Length
    if (RAND_bytes(IV.data(), IV.size()) != 1) throw runtime_error("IV Creation Error!");  // Fill IV
    

    // Create CTX
    evp = EVP_CIPHER_CTX_new();
    if (!evp) throw runtime_error("CTX Creation Error!");

    // First Step (Context Initialization)
    if (1 != EVP_EncryptInit_ex(evp, EVP_aes_256_gcm(), nullptr, nullptr, nullptr)) throw runtime_error("Encrypt Mode Set Error!");                // Mode Link
    if (1 != EVP_CIPHER_CTX_ctrl(evp, EVP_CTRL_GCM_SET_IVLEN, CCL.IV, nullptr)) throw runtime_error("Encrypt IV Size Concate Error!");             // IV Size Link
    if (1 != EVP_EncryptInit_ex(evp, EVP_aes_256_gcm(), nullptr, Key.data(), IV.data())) throw runtime_error("Encrypt IV and Key Concate Error!"); // Key and IV Link

    // Second Step (Update Content)
    if (1 != EVP_EncryptUpdate(evp, CipherContent.data(), &Length, reinterpret_cast<const uint8_t*>(Content.data()), Content.size())) throw runtime_error("Encrypt Update Error!");
    CipherContentLength += Length; // Update Content Length

    // Last Step (Final and Get Tag)
    if (1 != EVP_EncryptFinal_ex(evp, CipherContent.data() + Length, &Length)) throw runtime_error("Encrypt Final Error!");         // Finalize Encryption
    if (1 != EVP_CIPHER_CTX_ctrl(evp, EVP_CTRL_GCM_GET_TAG, Tag.size(), Tag.data())) throw runtime_error("Encrypt Get Tag Error!"); // Get Tag
    CipherContentLength += Length;             // Update Content Length
    CipherContent.resize(CipherContentLength); // Resize Content

    // Release CTX
    EVP_CIPHER_CTX_free(evp);
    evp = nullptr;

    // Result
    std::map<std::string, std::vector<uint8_t>> DataList = {
        {"Version", Version},
        {"Timestamp", Timestamp},
        {"IV", IV},
        {"Tag", Tag},
        {"CipherContent", CipherContent}
    };
    vector<uint8_t> Result = Parser::Concate(DataList);

    // Return Result
    return Base64::Encode(Result);
}

// Decrypt
string Cryptography::Decrypt(const string &Content)
{
    // Prepare Content and Create Buffer
    vector<uint8_t> DecodedContent = Base64::Decode(Content);                             // Get Raw Data
    std::map<std::string, std::vector<uint8_t>> DataList = Parser::Scrap(DecodedContent); // Get Data List
    vector<uint8_t> PlainContent(DataList.at("CipherContent").size());                    // Create Content Buffer
    int Length = 0;                                                                       // Create Content Length
    int PlainContentLength = 0;                                                           // Create Final Content Length

    // Create CTX
    evp = EVP_CIPHER_CTX_new();
    if (!evp) throw runtime_error("CTX Creation Error!");

    // First Step (Context Initialization)
    if (1 != EVP_DecryptInit_ex(evp, EVP_aes_256_gcm(), nullptr, nullptr, nullptr)) throw runtime_error("Decrypt Mode Set Error!");                               // Mode Link
    if (1 != EVP_CIPHER_CTX_ctrl(evp, EVP_CTRL_GCM_SET_IVLEN, CCL.IV, nullptr)) throw runtime_error("Decrypt IV Size Concate Error!");                            // IV Size Link
    if (1 != EVP_DecryptInit_ex(evp, EVP_aes_256_gcm(), nullptr, Key.data(), DataList.at("IV").data())) throw runtime_error("Decrypt IV and Key Concate Error!"); // Key and IV Link

    // Second Step (Set Tag and Update Content)
    if (1 != EVP_CIPHER_CTX_ctrl(evp, EVP_CTRL_GCM_SET_TAG, DataList.at("Tag").size(), DataList.at("Tag").data())) throw runtime_error("Decrypt Set Tag Error!");                          // Set Tag
    if (1 != EVP_DecryptUpdate(evp, PlainContent.data(), &Length, DataList.at("CipherContent").data(), DataList.at("CipherContent").size())) throw runtime_error("Decrypt Update Error!"); // Update Conte
    PlainContentLength += Length; // Update Content Length
    
    // Last Step (Final)
    if (1 != EVP_DecryptFinal_ex(evp, PlainContent.data() + Length, &Length)) throw runtime_error("Decrypt Final Error!"); // Finalize Decryption
    PlainContentLength += Length;            // Update Content Length
    PlainContent.resize(PlainContentLength); // Resize Content

    // Release CTX
    EVP_CIPHER_CTX_free(evp);
    evp = nullptr;

    // Return Result
    return string(PlainContent.begin(), PlainContent.end());
}

// LoadKey
string Cryptography::LoadKey()
{
    return Base64::Encode(Key);
}

void Cryptography::SetKey()
{
    if (this->Key.empty()) this->Key.resize(32);
    if (RAND_bytes(this->Key.data(), this->Key.size()) != 1) throw runtime_error("Key Creation Error!");
}

void Cryptography::SetKey(string *Key)
{
    if (Key == nullptr)
    {
        if (this->Key.empty()) this->Key.resize(32);
        if (RAND_bytes(this->Key.data(), this->Key.size()) != 1) throw runtime_error("Key Creation Error!");
    }
    else this->Key = Base64::Decode(*Key);
}

void Cryptography::SetKey(vector<uint8_t> *Key)
{
    if (Key == nullptr)
    {
        if (this->Key.empty()) this->Key.resize(32);
        if (RAND_bytes(this->Key.data(), this->Key.size()) != 1) throw runtime_error("Key Creation Error!");
    }

    else this->Key = *Key;
}
