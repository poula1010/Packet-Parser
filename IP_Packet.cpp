#include "IP_Packet.h"
std::string IP_Packet::display()
{
    std::string output{"Packet Type : IP \n"};
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
    std::string protocol = IPProtocols.count(ip_PacketData->protocol) != 0 ? IPProtocols.at(ip_PacketData->protocol) : byteToString(ip_PacketData->protocol);
    output += "Protocol : " + protocol + "\n";
    output += "Header Checksum: " + byteArrayToString(ip_PacketData->headerCheckSum) + "\n";
    output += "Source IP Address: " + byteArrayToString(ip_PacketData->sourceIp) + "\n";
    output += "Destination IP Address: " + byteArrayToString(ip_PacketData->destinationIp) + "\n";
    return output;
}
IP_Packet::IP_Packet(BasePacketData *basePacketData, IP_PacketData *ip_PacketData) : Packet(basePacketData), ip_PacketData{ip_PacketData}
{
}
