#include "BasePacketData.h"
#include "IP_PacketData.h"
#include "ARP_PacketData.h"
#include "ICMP_Packet.h"
#include <string>
#include <algorithm>

#include <array>
#include <vector>
#pragma once
using std::array;
using std::string;
class PacketDataExtractor
{
public:
    BasePacketData *extractBase(string input);
    IP_PacketData *extractIP_PacketData(vector<unsigned char> basePayload);
    ARP_PacketData *extractARP_PacketData(vector<unsigned char> basePayload);
    ICMP_PacketData *extractICMP_PacketData(vector<unsigned char> data);

    template <typename T, int N>
    array<T, N> extractArray(typename std::vector<T>::iterator &itr);
    PacketDataExtractor(){};
private:
    const int MIN_PACKET_LENGTH = 64;
    const int MAX_PACKET_LENGTH = 1518;
};
