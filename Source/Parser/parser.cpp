// Include Header(s)
#include "parser.hpp"

// Concate
vector<uint8_t> Parser::Concate(const map<string, vector<uint8_t>> &DataVectorList)
{
    // Create Output Vector
    vector<uint8_t> Output;

    // Reserve Output Size
    size_t TotalSize = 0;
    for (const auto &Element : DataVectorList) TotalSize += Element.second.size();
    Output.reserve(TotalSize);

    // Concate Vectors
    Output.insert(Output.end(), DataVectorList.at("Version").begin(), DataVectorList.at("Version").end());
    Output.insert(Output.end(), DataVectorList.at("Timestamp").begin(), DataVectorList.at("Timestamp").end());
    Output.insert(Output.end(), DataVectorList.at("IV").begin(), DataVectorList.at("IV").end());
    Output.insert(Output.end(), DataVectorList.at("Tag").begin(), DataVectorList.at("Tag").end());
    Output.insert(Output.end(), DataVectorList.at("CipherContent").begin(), DataVectorList.at("CipherContent").end());

    // Return Output
    return Output;
}

// Scrap
map<string, vector<uint8_t>> Parser::Scrap(const vector<uint8_t> &DataVectorList)
{
    // Create Output Buffers
    vector<uint8_t> Version(DataVectorList.begin(), DataVectorList.begin() + CCO.Version);
    vector<uint8_t> Timestamp(DataVectorList.begin() + CCO.Version, DataVectorList.begin() + CCO.Timestamp);
    vector<uint8_t> IV(DataVectorList.begin() + CCO.Timestamp, DataVectorList.begin() + CCO.IV);
    vector<uint8_t> Tag(DataVectorList.begin() + CCO.IV, DataVectorList.begin() + CCO.Tag);
    vector<uint8_t> CipherContent(DataVectorList.begin() + CCO.Tag, DataVectorList.end());

    // Create Vectors Map
    map<string, vector<uint8_t>> VectorList = {
        {"Version", Version},
        {"Timestamp", Timestamp},
        {"IV", IV},
        {"Tag", Tag},
        {"CipherContent", CipherContent}
    };

    // Return VectorList
    return VectorList;
}
