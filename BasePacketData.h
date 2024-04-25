#include <array>
#include <vector>
#pragma once
using std::array;
using std::vector;
class BasePacketData
{
public:
    array<unsigned char, 6> destinationMAC;
    array<unsigned char, 6> sourceMAC;
    array<unsigned char, 2> type;
    vector<unsigned char> payLoad;
    array<unsigned char, 4> checkSum;

    BasePacketData(array<unsigned char, 6> destinationMAC,
                   array<unsigned char, 6> sourceMAC,
                   array<unsigned char, 2> pType,
                   vector<unsigned char> payLoad,
                   array<unsigned char, 4> checkSum) : destinationMAC{destinationMAC}, sourceMAC{sourceMAC}, type{pType}, payLoad{payLoad}, checkSum{checkSum} {};
};