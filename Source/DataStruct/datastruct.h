// Include Guard
#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

// Struct Cipher Content
struct
{
    const int Version = 1;
    const int Timestamp = 8;
    const int IV = 12;
    const int Tag = 16;
} CCL; // Cipher Content Lengths

// Struct Cipher Content
struct
{
    const int Version = CCL.Version;
    const int Timestamp = Version + CCL.Timestamp;
    const int IV = Timestamp + CCL.IV;
    const int Tag = IV + CCL.Tag;
} CCO; // Cipher Content Offsets

// End If
#endif
