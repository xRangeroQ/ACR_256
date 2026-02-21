// ınclude Guard
#ifndef PARSER_HPP
#define PARSER_HPP

// Include Libraries
#include <map>
#include <string>
#include <vector>

// Include Header(s)
#include "../DataStruct/datastruct.h"
#include "../Base64/base64.hpp"

// Class Parser
class Parser
{
    public:
        // Parser Methods (Concate and Scrap)
        static vector<uint8_t> Concate(const map<string, vector<uint8_t>> &DataVectorList);
        static map<string, vector<uint8_t>> Scrap(const vector<uint8_t> &DataVectorList);
};

// End If
#endif
