#pragma once

#include<vector>
#include<string>
#include<optional>
#include"Task.pb.h"

class Persister {
public:
    using Tasks = std::vector<std::pair<TaskId, GeneralizedTask>>;
public:
    bool Save(const Tasks &, const std::string &);
    std::optional<Tasks> Load(const std::string &);
};


