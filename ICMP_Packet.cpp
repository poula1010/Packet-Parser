#include "ICMP_Packet.h"
std::string ICMP_Packet::display()
{
    std::string output{"Packet Type : ICMP \n"};
    output += Packet::display();
    output += ip_PacketData->ipVersion == 4   ? "IPv4 PayLoad: \n"
              : ip_PacketData->ipVersion == 6 ? "IPv6 PayLoad: \n"
                                              : "IP PayLoad: \n";
    output += "IP version: " + intToString(ip_PacketData->ipVersion) + "\n";
    output += "Internet Header Length : " + intToString(ip_PacketData->internetHeaderLength) + "\n";
    output += "Type of Service : " + byteToString(ip_PacketData->typeOfService) + "\n";
    output += "Total Length: " + byteArrayToString(ip_PacketData->totalLength) + "\n";
    output += "Identification: " + byteArrayToString(ip_PacketData->identification) + "\n";
    output += "Flags: " + intToString(ip_PacketData->flags) + "\n";
    output += "Fragment Offset: " + intToString(ip_PacketData->fragmentOffset) + "\n";
    output += "Time to Live: " + byteToString(ip_PacketData->timeToLive) + "\n";
    output += "Protocol : ICMP \n";
    output += "Header Checksum: " + byteArrayToString(ip_PacketData->headerCheckSum) + "\n";
    output += "Source IP Address: " + byteArrayToString(ip_PacketData->sourceIp) + "\n";
    output += "Destination IP Address: " + byteArrayToString(ip_PacketData->destinationIp) + "\n";
    output += "ICMP Type : " + byteToString(icmpPacketData->type) + "\n";
    output += "ICMP code : " + byteToString(icmpPacketData->code) + "\n";
    output += "ICMP CheckSum : " + byteArrayToString(icmpPacketData->icmpCheckSum) + "\n";
    output += "ICMP Identifier : " + byteArrayToString(icmpPacketData->identifier) + "\n";
    output += "ICMP SequenceNumber : " + byteArrayToString(icmpPacketData->sequenceNumber) + "\n";
    return output;
}
ICMP_Packet::ICMP_Packet(BasePacketData *basePacketData,
                         IP_PacketData *ipPacketData,
                         ICMP_PacketData *icmpPacketData) : IP_Packet{basePacketData, ipPacketData},
                                                            icmpPacketData{icmpPacketData} {}
