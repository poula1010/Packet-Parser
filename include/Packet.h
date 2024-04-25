#include "BasePacketData.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <QString>
#pragma once

class Packet
{
protected:
    template <typename T>
    std::string byteArrayToString(T byteArray)
    {
        std::ostringstream oss;
        oss << std::hex << std::setfill('0');

        for (int i = 0; i < byteArray.size(); ++i)
        {
            oss << std::setw(2) << static_cast<int>(byteArray[i]) << " ";
        }

        return oss.str();
    }
    std::string byteToString(unsigned char byte)
    {
        std::ostringstream oss;
        oss << std::hex << std::setfill('0');
        oss << std::setw(2) << static_cast<int>(byte) << " ";
        return oss.str();
    }
    std::string intToString(int num)
    {
        std::stringstream ss;
        ss << num;
        return ss.str();
    }

public:
    BasePacketData *basePacketData;
    Packet(BasePacketData *basePacketData) : basePacketData{basePacketData} {};
    Packet(){};
    virtual ~Packet()
    {
        delete basePacketData;
    };
    virtual std::string display();

};
