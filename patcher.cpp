#include <cstdlib>
#include "patcher.h"

Patcher::Patcher()
{

}

int Patcher::prepare() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    std::string command = "mkdir %USERPROFILE%\\bsqmu\\apk\\old\\ && ";
    command += "mkdir %USERPROFILE%\\bsqmu\\apk\\extracted\\ && ";
    command += "mkdir %USERPROFILE%\\bsqmu\\apk\\new\\";
#else
    std::string command = "mkdir -p ~/bsqmu/apk/old/ && ";
    command += "mkdir -p ~/bsqmu/apk/extracted/ && ";
    command += "mkdir -p ~/bsqmu/apk/new/";
#endif
    return std::system(command.c_str());
}

int Patcher::pull(std::string apkPath, std::string adbPath) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    const std::string command = adbPath + " pull " + apkPath + " %USERPROFILE%\bsqmu\apk\old\";
#else
    const std::string command = "adb pull " + apkPath + " ~/bsqmu/apk/old/";
#endif
    return std::system(command.c_str());
}
