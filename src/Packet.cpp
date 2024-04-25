#include "Packet.h"

std::string Packet::display()
{
    std::string output{""};
    output += "Destination MAC: " + byteArrayToString(basePacketData->destinationMAC) + "\n";
    output += "Source MAC: " + byteArrayToString(basePacketData->sourceMAC) + "\n";
    output += "Type/Length: " + byteArrayToString(basePacketData->type) + "\n";
    output += "PayLoad : " + byteArrayToString(basePacketData->payLoad) + "\n";
    output += "CheckSum : " + byteArrayToString(basePacketData->checkSum) + "\n";
    char buff[32];
    snprintf(buff, sizeof(buff), "%zu", basePacketData->payLoad.size());
    std::string payLoadLength = buff;
    output += "PayLoad Length : " + payLoadLength + "\n";
    return output;
}
