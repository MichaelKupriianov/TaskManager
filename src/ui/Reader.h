#pragma once

#include<string>

class Reader {
public:
    void Help();
    void Quit();
    std::string ReadCommand();
    int ReadId(const std::string &);
    std::string ReadTitle(const std::string &);
    std::string ReadPriority(const std::string &);
    std::string ReadTime(const std::string &);
    std::string ReadLabel(const std::string &);
    bool Confirm();
    void HandleException(const std::exception &);
};

time_t StringToTime(const std::string &);
std::string TimeToString(time_t);