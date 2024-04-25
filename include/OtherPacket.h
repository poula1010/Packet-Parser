#include "Packet.h"
#include <string>
#pragma once
class OtherPacket : public Packet
{
public:
    OtherPacket(BasePacketData *basePacketData) : Packet{basePacketData} {};
    virtual std::string display() override;
    virtual ~OtherPacket(){};
};
