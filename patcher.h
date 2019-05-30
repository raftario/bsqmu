#ifndef PATCHER_H
#define PATCHER_H
#include <string>

class Patcher
{
public:
    Patcher();
    int prepare();
    int pull(std::string, std::string, bool);
    int cleanup();
private:
    static std::string timeString();
};

#endif // PATCHER_H
