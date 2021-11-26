#include "Task.h"
#include<stdexcept>

Task::Arguments Task::Arguments::Create(const std::string &title, Priority priority, time_t time,
                                        const std::string &label, Condition state) {
    return Arguments(title, priority, time, label, state);
}

Task::Arguments::Arguments(const std::string &title, Priority priority, time_t time,
                           const std::string &label, Condition state) :
        title_(title), priority_(priority), date_(time), label_(label), state_(state) {}

Task Task::Create(const Arguments &parameter) {
    if (parameter.title_.empty()) throw std::runtime_error("There are no tasks without title");
    if (parameter.date_ < 0) throw std::runtime_error("Time should be after January 1, 1970");
    return Task(parameter);
}

Task::Task(const Arguments &parameter) :
        title_(parameter.title_), priority_(parameter.priority_), date_(parameter.date_),
        label_(parameter.label_), state_(parameter.state_) {}

bool operator==(const Task &first, const Task &second) {
    return first.title_ == second.title_ && first.priority_ == second.priority_ &&
           first.date_ == second.date_ && first.label_ == second.label_ && first.state_ == second.state_;
}

