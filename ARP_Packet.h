#include "Packet.h"
#include "ARP_PacketData.h"
#include <array>
#include <string>
#pragma once
using std::array;
class ARP_Packet : public Packet
{
protected:
    ARP_PacketData *arp_PacketData;

public:
    virtual std::string display() override;
    ARP_Packet(BasePacketData *BasePacketData, ARP_PacketData *arp_PacketData);
    virtual ~ARP_Packet(){};
};
