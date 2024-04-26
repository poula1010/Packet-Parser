#include "ICMP_Packet.h"
std::string ICMP_Packet::display()
{
    string output{""};
    output += IP_Packet::display();
    output += "ICMP PayLoad: \n";
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
