#ifndef CUSTOMEXCEPTIONS_H
#define CUSTOMEXCEPTIONS_H
#include <stdexcept>
class MinPacketLengthNotReachedException :public std::runtime_error{
    public:
    MinPacketLengthNotReachedException(std::string msg):std::runtime_error(msg){};
};

class MaxPacketLengthExceededException :public std::runtime_error{
public:
    MaxPacketLengthExceededException(std::string msg):std::runtime_error(msg){};
};
class InvalidInputException:public std::runtime_error{
    public:
    InvalidInputException(std::string msg):std::runtime_error(msg){};
};
#endif // CUSTOMEXCEPTIONS_H
