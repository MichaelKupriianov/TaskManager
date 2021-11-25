#pragma once

#include<string>
#include<optional>

class Validator {
public:
    static std::optional<std::string> ValidateCommand(const std::string &);
    static std::optional<std::string> ValidateId(const std::string &);
    static std::optional<std::string> ValidateTitle(const std::string &);
    static std::optional<std::string> ValidatePriority(const std::string &);
    static std::optional<std::string> ValidateTime(const std::string &);
    static std::optional<std::string> ValidateConfirm(const std::string &);
};

time_t StringToTime(const std::string &);