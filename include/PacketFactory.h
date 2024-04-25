#include "Packet.h"
#include "IP_Packet.h"
#include "ARP_Packet.h"
#include "OtherPacket.h"
#include "PacketDataExtractor.h"
#include <memory>
#pragma once
using std::unique_ptr;
class PacketFactory
{
public:
    PacketFactory() : packetDataExtractor{new PacketDataExtractor{}} {};
    Packet *createPacket(string input);
    ~PacketFactory()
    {
        delete packetDataExtractor;
    }

private:
    PacketDataExtractor *packetDataExtractor;
    const array<unsigned char, 2> IP_TYPE{0x08, 0x00};
    const array<unsigned char, 2> ARP_TYPE{0x08, 0x06};
    const unsigned char ICMP_PROTOCOL{0x01};
};
