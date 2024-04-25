#include "OtherPacket.h"

std::string OtherPacket::display()
{
    std::string output{"Packet Type : Other \n"};
    output += Packet::display();
    return output;
}
