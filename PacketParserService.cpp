#include "PacketParserService.h"
#include "customExceptions.h"
PacketParserService::PacketParserService(){};

std::string PacketParserService::parsePacket(string input)
{
    std::string output{""};
    try {
        Packet *packet = packetFactory.createPacket(input);
        output = packet->display();
        delete packet;
    }
    catch(MinPacketLengthNotReachedException e){
        output = e.what();
    }
    catch(MaxPacketLengthExceededException e){
        output = e.what();
    }
    catch (...) {
        output="*invalid input";
    }

    return output;
}
