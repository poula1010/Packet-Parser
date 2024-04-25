#include "Packet.h"
#include "IP_PacketData.h"
#include <array>
#include <map>
#include <string>
#pragma once
using std::array;
using std::string;

class IP_Packet : public Packet
{
private:
    // a const set containing the most used protocols
    const std::map<unsigned char, std::string> IPProtocols = {
        {1, "Internet Control Message Protocol (ICMP)"},
        {6, "Transmission Control Protocol (TCP)"},
        {17, "User Datagram Protocol (UDP)"},
    };

protected:
    IP_PacketData *ip_PacketData;

public:
    virtual string display() override;
    IP_Packet(BasePacketData *basePacketData, IP_PacketData *ip_PacketData);
    IP_Packet(){};
    virtual ~IP_Packet()
    {
        delete ip_PacketData;
    };
};
