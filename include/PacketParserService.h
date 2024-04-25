#pragma once
#include "PacketFactory.h"
#include <string>
class PacketParserService
{
private:
    PacketFactory packetFactory;

public:
    PacketParserService();
    std::string parsePacket(string input);
};
