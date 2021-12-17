#pragma once

#include<vector>
#include<string>
#include<optional>
#include"TransportationTask.pb.h"

class Persister {
public:
    bool Save(const std::vector<TransportationTask> &, const std::string &);
    std::optional<std::vector<TransportationTask>> Load(const std::string &);
};


