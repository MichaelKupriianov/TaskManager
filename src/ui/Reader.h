#pragma once

#include<string>

class Reader {
public:
    static void Help();
    static void Quit();
    static std::string ReadCommand();
    static std::string ReadTitle(const std::string &);
    static std::string ReadPriority(const std::string &);
    static std::string ReadTime(const std::string &);
    static void HandleException(const std::exception &);
};

time_t StringToTime(const std::string &);
std::string TimeToString(time_t);