#include "Task.h"
#include<stdexcept>

Task::Parameter::Parameter(const std::string &title, Priority priority, time_t time,
                const std::string &label, State state) :
                title_(title), priority_(priority), date_(time), label_(label), state_(state) {}

Task Task::Create(const Parameter &parameter) {
    if (parameter.title_.empty()) throw std::runtime_error("There are no tasks without title");
    if (parameter.date_ < 0) throw std::runtime_error("Time should be after January 1, 1970");
    return Task(parameter);
}

Task::Task(const Parameter &parameter) :
        title_(parameter.title_), priority_(parameter.priority_), date_(parameter.date_),
        label_(parameter.label_), state_(parameter.state_) {}

bool operator==(const Task &first, const Task &second) {
    return first.title_ == second.title_ && first.priority_ == second.priority_ &&
           first.date_ == second.date_ && first.label_ == second.label_ && first.state_ == second.state_;
}

Task::Priority StringToPriority(const std::string &priority) {
    if (priority == "high") return Task::Priority::HIGH;
    if (priority == "medium") return Task::Priority::MEDIUM;
    if (priority == "lou") return Task::Priority::LOU;
    if (priority == "none") return Task::Priority::NONE;
    throw std::runtime_error("There is no such priority");
}

std::string PriorityToString(Task::Priority priority) {
    if (priority == Task::Priority::HIGH) return "high";
    if (priority == Task::Priority::MEDIUM) return "medium";
    if (priority == Task::Priority::LOU) return "lou";
    return "none";
}

