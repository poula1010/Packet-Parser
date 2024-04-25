#include <array>
#include <vector>
#include <string>

#pragma once
using std::array;
using std::string;
using std::vector;
class IP_PacketData
{
public:
    int ipVersion;
    int internetHeaderLength;
    unsigned char typeOfService;
    array<unsigned char, 2> totalLength;
    array<unsigned char, 2> identification;
    int flags;
    int fragmentOffset;
    unsigned char timeToLive;
    unsigned char protocol;
    array<unsigned char, 2> headerCheckSum;
    array<unsigned char, 4> sourceIp;
    array<unsigned char, 4> destinationIp;
    vector<unsigned char> options;
    vector<unsigned char> ipData;

    IP_PacketData(int ipVersion,
                  int internetHeaderLength,
                  unsigned char typeOfService,
                  array<unsigned char, 2> totalLength,
                  array<unsigned char, 2> identification,
                  int flags,
                  int fragmentOffset,
                  unsigned char timeToLive,
                  unsigned char protocol,
                  array<unsigned char, 2> headerCheckSum,
                  array<unsigned char, 4> sourceIp,
                  array<unsigned char, 4> destinationIp,
                  vector<unsigned char> options,
                  vector<unsigned char> ipData) : ipVersion{ipVersion},
                                                  internetHeaderLength{internetHeaderLength},
                                                  typeOfService{typeOfService},
                                                  totalLength{totalLength},
                                                  identification{identification},
                                                  flags{flags},
                                                  fragmentOffset{fragmentOffset},
                                                  timeToLive{timeToLive},
                                                  protocol{protocol},
                                                  headerCheckSum{headerCheckSum},
                                                  sourceIp{sourceIp},
                                                  destinationIp{destinationIp},
                                                  options{options},
                                                  ipData{ipData} {};
};