#include "IP_Packet.h"
#include "ICMP_PacketData.h"
#pragma once
class ICMP_Packet : public IP_Packet
{
protected:
    ICMP_PacketData *icmpPacketData;

public:
    virtual std::string display() override;
    ICMP_Packet(BasePacketData *basePacketData, IP_PacketData *ipPacketData, ICMP_PacketData *icmpPacketData);
    virtual ~ICMP_Packet()
    {
        delete icmpPacketData;
    };
};
