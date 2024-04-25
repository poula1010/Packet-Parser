#include <array>
#pragma once
using std::array;
class ICMP_PacketData
{
public:
    unsigned char type;
    unsigned char code;
    array<unsigned char, 2> icmpCheckSum;
    array<unsigned char, 2> identifier;
    array<unsigned char, 2> sequenceNumber;
    ICMP_PacketData(unsigned char type,
                    unsigned char code,
                    array<unsigned char, 2> icmpCheckSum,
                    array<unsigned char, 2> identifier,
                    array<unsigned char, 2> sequenceNumber) : type{type}, code{code},
                                                              icmpCheckSum{icmpCheckSum}, identifier{identifier},
                                                              sequenceNumber{sequenceNumber} {};
};