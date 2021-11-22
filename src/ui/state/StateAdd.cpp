#include "StateAdd.h"

#include<ctime>
#include<string>

time_t StringToTime(const std::string &date) {
    tm time = {};
    std::string pattern{"%H:%M %d/%m/%Y"};
    if (!strptime(date.c_str(), pattern.c_str(), &time))
        throw std::runtime_error("Incorrect time entry");
    return mktime(&time);
}

std::string TimeToString(time_t time) {
    return ctime(&time);
}