#ifndef PATCHER_H
#define PATCHER_H
#include <string>

class Patcher
{
public:
    Patcher();
    int prepare();
    int pull(std::string, std::string);
};

#endif // PATCHER_H
