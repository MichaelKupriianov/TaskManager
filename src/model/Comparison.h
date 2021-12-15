#pragma once

#include"TaskId.pb.h"
#include"Task.pb.h"

bool operator<(const TaskId &first, const TaskId &second);

bool operator==(const TaskId &first, const TaskId &second);

bool operator==(const Task &first, const Task &second);