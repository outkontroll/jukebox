#include "Times.h"
#include <ctime>

std::string jukebox::CurrentDateTime()
{
    time_t now = time(0);
    struct tm* timeStruct;
    char buf[80];
    timeStruct = localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", timeStruct);

    return buf;
}
