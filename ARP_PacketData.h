#include <array>
#include<vector>
#pragma once
using std::array;
using std::vector;
class ARP_PacketData
{
public:
    array<unsigned char, 2> hardwareType;
    array<unsigned char, 2> protocolType;
    unsigned char hardwareAddressLength;
    unsigned char protocolAddressLength;
    array<unsigned char, 2> operationCode;
    vector<unsigned char> senderHardwareAddress;
    vector<unsigned char> senderProtocolAddress;
    vector<unsigned char> targetHardwareAddress;
    vector<unsigned char> targetProtocolAddress;

    ARP_PacketData(
        array<unsigned char, 2> hardwareType,
        array<unsigned char, 2> protocolType,
        unsigned char hardwareAddressLength,
        unsigned char protocolAddressLength,
        array<unsigned char, 2> operationCode,
        vector<unsigned char> senderHardwareAddress,
        vector<unsigned char> senderProtocolAddress,
        vector<unsigned char> targetHardwareAddress,
        vector<unsigned char> targetProtocolAddress) : hardwareType{hardwareType},
                                                       protocolType{protocolType},
                                                       hardwareAddressLength{hardwareAddressLength},
                                                       protocolAddressLength{protocolAddressLength},
                                                       operationCode{operationCode},
                                                       senderHardwareAddress{senderHardwareAddress},
                                                       senderProtocolAddress{senderProtocolAddress},
                                                       targetHardwareAddress{targetHardwareAddress},
                                                       targetProtocolAddress{targetProtocolAddress} {};
};
