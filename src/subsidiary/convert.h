#pragma once

#include<ctime>
#include<string>
#include"Task.h"

time_t ToTime(const std::string &date) {
    tm time = {};
    std::string pattern{"%H:%M %d/%m/%Y"};
    if (!strptime(date.c_str(), pattern.c_str(), &time))
        throw std::runtime_error("Incorrect time entry");
    return mktime(&time);
}

Task::Priority ToPriority(const std::string &priority) {
    if (priority == "high") return Task::Priority::HIGH;
    if (priority == "medium") return Task::Priority::MEDIUM;
    if (priority == "low") return Task::Priority::LOU;
    if (priority == "none") return Task::Priority::NONE;
    throw std::runtime_error("There is no such priority");
}

std::string ToString(Task::Priority priority) {
    if (priority == Task::Priority::HIGH) return "high";
    if (priority == Task::Priority::MEDIUM) return "medium";
    if (priority == Task::Priority::LOU) return "lou";
    return "none";
}
