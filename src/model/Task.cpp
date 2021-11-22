#include "Task.h"
#include<stdexcept>

Task Task::Create(const std::string &title, Priority priority, time_t time,
                  const std::string &label, State state) {
    if (title.empty()) throw std::runtime_error("There are no tasks without title");
    if (time < 0) throw std::runtime_error("Time should be positive");
    return Task(title, priority, time, label, state);
}

Task::Task(const std::string &title, Priority priority, time_t date,
           const std::string &label, State state) :
        title_(title), priority_(priority), due_date_(date),
        label_(label), state_(state) {}

bool operator==(const Task &first, const Task &second) {
    return first.title_ == second.title_ && first.priority_ == second.priority_ &&
           first.due_date_ == second.due_date_ && first.label_==second.label_ && first.state_==second.state_;
}

Task::Priority StringToPriority(const std::string &priority) {
    if (priority == "high") return Task::Priority::HIGH;
    if (priority == "medium") return Task::Priority::MEDIUM;
    if (priority == "low") return Task::Priority::LOU;
    if (priority == "none") return Task::Priority::NONE;
    throw std::runtime_error("There is no such priority");
}

std::string PriorityToString(Task::Priority priority) {
    if (priority == Task::Priority::HIGH) return "high";
    if (priority == Task::Priority::MEDIUM) return "medium";
    if (priority == Task::Priority::LOU) return "lou";
    return "none";
}
