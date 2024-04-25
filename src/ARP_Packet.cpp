#include "ARP_Packet.h"
std::string ARP_Packet::display()
{
    std::string output{"Packet Type : ARP \n"};
    output += Packet::display();
    output += "ARP PayLoad: \n";
    output += "Hardware Type: " + byteArrayToString(arp_PacketData->hardwareType) + "\n";
    output += "Protocol Type: " + byteArrayToString(arp_PacketData->protocolType) + "\n";
    output += "Hardware Address Length: " + byteToString(arp_PacketData->hardwareAddressLength) + "\n";
    output += "Protocol Address Length: " + byteToString(arp_PacketData->protocolAddressLength) + "\n";
    output += "Sender Hardware Address: " + byteArrayToString(arp_PacketData->senderHardwareAddress) + "\n";
    output += "Sender Protocol Address: " + byteArrayToString(arp_PacketData->senderProtocolAddress) + "\n";
    output += "Target Hardware Address: " + byteArrayToString(arp_PacketData->targetHardwareAddress) + "\n";
    output += "Target Protocol Address: " + byteArrayToString(arp_PacketData->targetProtocolAddress) + "\n";

    return output;
}
ARP_Packet::ARP_Packet(BasePacketData *basePacketData,
                       ARP_PacketData *arp_PacketData) : Packet{basePacketData}, arp_PacketData{arp_PacketData}
{
}
