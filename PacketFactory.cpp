#include "PacketFactory.h"

Packet *PacketFactory::createPacket(string input)
{
    BasePacketData *basePacketData = packetDataExtractor->extractBase(input);
    if (basePacketData->type == IP_TYPE)
    {
        IP_PacketData *ipPacketData = packetDataExtractor->extractIP_PacketData(basePacketData->payLoad);
        if (ipPacketData->protocol == ICMP_PROTOCOL)
        {
            ICMP_PacketData *icmpPacketData = packetDataExtractor->extractICMP_PacketData(ipPacketData->ipData);
            return new ICMP_Packet(basePacketData, ipPacketData, icmpPacketData);
        }
        return new IP_Packet(basePacketData, ipPacketData);
    }
    else if (basePacketData->type == ARP_TYPE)
    {
        ARP_PacketData *arpPacketData = packetDataExtractor->extractARP_PacketData(basePacketData->payLoad);
        return new ARP_Packet(basePacketData, arpPacketData);
    }
    else
    {
        return new OtherPacket(basePacketData);
    }
}