#pragma once

#include"Task.pb.h"

bool operator<(const TaskId &first, const TaskId &second);

bool operator==(const TaskId &first, const TaskId &second);

bool operator==(const Task &first, const Task &second);

bool operator==(const GeneralizedTask &first, const GeneralizedTask &second);