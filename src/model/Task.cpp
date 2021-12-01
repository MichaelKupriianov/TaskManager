#include "Task.h"

Task::Arguments Task::Arguments::Create(const std::string &title, Priority priority, time_t time,
                                        const std::string &label, Condition state) {
    return Arguments({title, priority, time, label, state});
}

Task::Arguments::Arguments(const std::string &title, Priority priority, time_t time,
                           const std::string &label, Condition state) :
        title_(title), priority_(priority), date_(time), label_(label), condition_(state) {}

std::optional<Task> Task::Create(const Arguments &parameter) {
    if (parameter.title_.empty()) return std::nullopt;
    return Task(parameter);
}

Task::Task(const Arguments &parameter) :
        title_(parameter.title_), priority_(parameter.priority_), date_(parameter.date_),
        label_(parameter.label_), condition_(parameter.condition_) {}

bool operator==(const Task &first, const Task &second) {
    return first.title() == second.title() && first.priority() == second.priority() &&
           first.date() == second.date() && first.label() == second.label() && first.condition() == second.condition();
}

