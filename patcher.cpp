#include <cstdlib>
#include <ctime>
#include "patcher.h"

Patcher::Patcher()
{

}

int Patcher::prepare() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    std::string command = "mkdir %USERPROFILE%\\bsqmu\\apk\\old\\ && ";
    command += "mkdir %USERPROFILE%\\bsqmu\\apk\\extracted\\ && ";
    command += "mkdir %USERPROFILE%\\bsqmu\\apk\\new\\ && ";
    command += "mkdir %USERPROFILE%\\bsqmu\\backup\\";
#else
    std::string command = "mkdir -p ~/bsqmu/apk/ && ";
    command += "mkdir -p ~/bsqmu/tools/ && ";
    command += "mkdir -p ~/bsqmu/userdata/ && ";
    command += "mkdir -p ~/bsqmu/backup/";
#endif
    return std::system(command.c_str());
}

int Patcher::pull(std::string apkPath, std::string adbPath, bool backup) {
    std::string ts;
    if (backup) {
        ts = Patcher::timeString();
    }
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    std::string command = adbPath + " pull " + apkPath + " %USERPROFILE%\\bsqmu\\apk\\";
    if (backup) {
        command += " && mkdir %USERPROFILE%\\bsqmu\\backup\\ " + ts + "\\apk\\ && cp /y %USERPROFILE%\\bsqmu\\apk\\base.apk %USERPROFILE%\\bsqmu\\backup\\ " + ts + "\\apk\\base.apk";
    }
#else
    std::string command = "adb pull " + apkPath + " ~/bsqmu/apk/";
    if (backup) {
        command += " && mkdir -p ~/bsqmu/backup/" + ts + "/apk/ && cp ~/bsqmu/apk/base.apk ~/bsqmu/backup/" + ts + "/apk/base.apk";
    }
#endif
    return std::system(command.c_str());
}

int Patcher::cleanup() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    const std::string command = "del /Q /F %USERPROFILE%\\bsqmu\\apk\\base.apk";
#else
    const std::string command = "rm -f ~/bsqmu/apk/base.apk";
#endif
    return std::system(command.c_str());
}

std::string Patcher::timeString() {
    char tca[20];
    const std::time_t curTime = std::time(nullptr);
    std::strftime(tca, 20, "%F-%H-%M-%S", std::localtime(&curTime));
    return std::string(tca);
}
