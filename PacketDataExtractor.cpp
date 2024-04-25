#include <regex>
#include "PacketDataExtractor.h"
#include "customExceptions.h"
using namespace std;
// function for extracting the basic parameters contained in any Packet
template <typename T, int N>
array<T, N> PacketDataExtractor::extractArray(typename std::vector<T>::iterator &itr)
{
    array<T, N> resultArray{};
    for (int i = 0; i < N; i++)
    {
        resultArray[i] = *itr;
        itr++;
    }
    return resultArray;
}
BasePacketData *PacketDataExtractor::extractBase(string input)
{

    // remove whitespaces by using remove_if which returns an iterator to the new end of the string and we erase everything after that using erase
    input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
    // each two character inputs in a string represent a byte so we parse them into a single byte using stoi
    vector<unsigned char> inputBytes{};
    for (int i = 0; i < input.length(); i += 2)
    {
        unsigned char byteValue = std::stoi(input.substr(i, 2), 0, 16);
        inputBytes.push_back(byteValue);
    }
    //------------------------------Data Validation Section-----------------------------------//
    // check if PacketData is at least the size of minimum packet which is 64 Bytes;
    if (inputBytes.size() < MIN_PACKET_LENGTH)
    {
        // throw exception
        throw MinPacketLengthNotReachedException("*this packet is invalid as it doesn't satisify the minimum length condition for a packet");
    }

    if(inputBytes.size() > MAX_PACKET_LENGTH){
        throw MaxPacketLengthExceededException("*this packet is invalid as it exceeds the maximum length of an ethernet packet");
    }
    // place each part of the packetData into its part;
    auto itr_start = inputBytes.begin();

    // assigning destinationMacAddress;
    array<unsigned char, 6> destinationMAC{extractArray<unsigned char, 6>(itr_start)};

    // assigning sourceMacAddress
    array<unsigned char, 6> sourceMAC{extractArray<unsigned char, 6>(itr_start)};

    // assigning type
    array<unsigned char, 2> type{extractArray<unsigned char, 2>(itr_start)};

    // we need to assign checkSum before payLoad as the payload has variable length;
    auto itr_end = inputBytes.end();
    itr_end--;
    array<unsigned char, 4> checkSum{};
    for (int i = 3; i >= 0; i--)
    {
        checkSum[i] = *itr_end;
        itr_end--;
    }
    // finally assigning payload;
    itr_end++;
    vector<unsigned char> payLoad{};
    while (itr_start != itr_end)
    {
        payLoad.push_back(*itr_start);
        itr_start++;
    }

    BasePacketData *data = new BasePacketData{destinationMAC, sourceMAC, type, payLoad, checkSum};
    return data;
}
// function for extracting the ARP PacketData from the payload of the base packet;
ARP_PacketData *PacketDataExtractor::extractARP_PacketData(vector<unsigned char> basePayload)
{
    // get an iterator of the basePayload vector to
    auto basePayLoadItr = basePayload.begin();

    // assign Hardware Type size is 2Bytes
    array<unsigned char, 2> hardwareType{extractArray<unsigned char, 2>(basePayLoadItr)};

    // assign Protocol Type size is 2Bytes
    array<unsigned char, 2> protocolType{extractArray<unsigned char, 2>(basePayLoadItr)};

    // assign Hardware Address Length size is 1 Byte;
    unsigned char hardwareAddressLength{*basePayLoadItr};
    basePayLoadItr++;

    // assign Protocol Address Length size is 1 Byte;
    unsigned char protocolAddressLength{*basePayLoadItr};
    basePayLoadItr++;

    // assign operationCode size is 2Bytes;
    array<unsigned char, 2> operationCode{extractArray<unsigned char, 2>(basePayLoadItr)};

    // assign sender hardware address size is used from hardware addressLength;
    vector<unsigned char> senderHardwareAddress(hardwareAddressLength);
    for (int i = 0; i < hardwareAddressLength; i++)
    {
        senderHardwareAddress[i] = *basePayLoadItr;
        basePayLoadItr++;
    }
    // assign sender protocol address size is used from protocol address Length;
    vector<unsigned char> senderProtocolAddress(protocolAddressLength);
    for (int i = 0; i < protocolAddressLength; i++)
    {
        senderProtocolAddress[i] = *basePayLoadItr;
        basePayLoadItr++;
    }

    // assign target hardware address size is used from hardware addressLength;
    vector<unsigned char> targetHardwareAddress(hardwareAddressLength);
    for (int i = 0; i < hardwareAddressLength; i++)
    {
        targetHardwareAddress[i] = *basePayLoadItr;
        basePayLoadItr++;
    }
    // assign target protocol address size is used from protocol address Length;
    vector<unsigned char> targetProtocolAddress(protocolAddressLength);
    for (int i = 0; i < protocolAddressLength; i++)
    {
        targetProtocolAddress[i] = *basePayLoadItr;
        basePayLoadItr++;
    }

    ARP_PacketData *arpPacketData = new ARP_PacketData{
        hardwareType,
        protocolType,
        hardwareAddressLength,
        protocolAddressLength,
        operationCode,
        senderHardwareAddress,
        senderProtocolAddress,
        targetHardwareAddress,
        targetProtocolAddress};
    return arpPacketData;
}
// function for extracting IP_Packet details from basePacket payload
IP_PacketData *PacketDataExtractor::extractIP_PacketData(vector<unsigned char> basePayLoad)
{
    auto basePayLoadItr = basePayLoad.begin();
    // getting ip version and IHL
    int ipVersion{0};
    int internetHeaderLength{0};
    unsigned char firstByte = *basePayLoadItr;
    basePayLoadItr++;
    // the ip version is represented in the first 4 bits of the byte and the ihl in the other 4 bits we can do a bitwise operation + shift to extract them
    ipVersion = (firstByte & 0xf0) >> 4;
    // the internet header length is multiplied by 4 as it counts 4bytes per bit;
    internetHeaderLength = (firstByte & 0x0f) * 4;

    // assigning the TOS
    unsigned char typeOfService = *basePayLoadItr;
    basePayLoadItr++;
    // assigning the totalLength
    array<unsigned char, 2> totalLength{extractArray<unsigned char, 2>(basePayLoadItr)};
    // assigning identification
    array<unsigned char, 2> identification{extractArray<unsigned char, 2>(basePayLoadItr)};

    // assigning flag and Fragment offset by putting a mask on the first 3 bits then right shifting 4 bits for flag and getting the remainder 5 bits for the fragment offset
    unsigned char flagByte = *basePayLoadItr;
    basePayLoadItr++;
    int flag{0};
    flag += (0xE0 & flagByte) >> 4;
    // getting fragmentoffset first part from the mask b00011111 leftshifted by 8 and then adding the remaining byte
    int fragmentOffset{0};
    fragmentOffset += (0x1F & flagByte) << 8;
    fragmentOffset += *basePayLoadItr;
    basePayLoadItr++;
    // assigning TTL
    unsigned char timeToLive = *basePayLoadItr;
    basePayLoadItr++;

    // assigning Protocol
    unsigned char protocol = *basePayLoadItr;
    basePayLoadItr++;

    // assigning headerCheckSum
    array<unsigned char, 2> headerCheckSum{extractArray<unsigned char, 2>(basePayLoadItr)};

    // assigning sourceAddress
    array<unsigned char, 4> sourceIp{extractArray<unsigned char, 4>(basePayLoadItr)};

    // assigning destinationAddress
    array<unsigned char, 4> destinationIp{extractArray<unsigned char, 4>(basePayLoadItr)};

    // reaching this point we have extracted 20 bytes exactly that must be contained in every IP Header in the following we extract the options using IHL
    vector<unsigned char> options(internetHeaderLength - 20);
    for (int i = 0; i < internetHeaderLength - 20; i++)
    {
        options[i] = *basePayLoadItr;
        basePayLoadItr++;
    }
    // finally we have the remaining data included in the ip packet
    vector<unsigned char> ipData{};
    auto basePayLoadEndItr = basePayLoad.end();
    std::copy(basePayLoadItr, basePayLoadEndItr, back_inserter(ipData));

    // creating the IP_PacketData and returning it
    IP_PacketData *ipPacketData = new IP_PacketData{ipVersion, internetHeaderLength, typeOfService,
                                                    totalLength, identification, flag,
                                                    fragmentOffset, timeToLive, protocol,
                                                    headerCheckSum, sourceIp, destinationIp,
                                                    options, ipData};
    return ipPacketData;
}

ICMP_PacketData *PacketDataExtractor::extractICMP_PacketData(vector<unsigned char> ipPayload)
{
    auto ipPayLoadItr = ipPayload.begin();
    // assigning type
    unsigned char type = *ipPayLoadItr;
    ipPayLoadItr++;
    // assiging code
    unsigned char code = *ipPayLoadItr;
    ipPayLoadItr++;
    // assigning icmpChecksum;
    array<unsigned char, 2> icmpCheckSum{extractArray<unsigned char, 2>(ipPayLoadItr)};
    // assiging identifier
    array<unsigned char, 2> identifier{extractArray<unsigned char, 2>(ipPayLoadItr)};
    // assigning sequenceNumber
    array<unsigned char, 2> sequenceNumber{extractArray<unsigned char, 2>(ipPayLoadItr)};

    ICMP_PacketData *icmpPacketData = new ICMP_PacketData{type, code, icmpCheckSum, identifier, sequenceNumber};
    return icmpPacketData;
}
