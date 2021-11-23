#include"Factory.h"
#include"StateAdd.h"

std::unique_ptr<State> Factory::CreateState(const std::string &state) {
    if (state == "command") return std::unique_ptr<State>(new StateCommand);
    if (state == "quit") return std::unique_ptr<State>(new StateQuit);
    if (state == "help") return std::unique_ptr<State>(new StateHelp);
    if (state == "add") return std::unique_ptr<State>(new StateAdd);
    if (state == "edit") return std::unique_ptr<State>(new StateEdit);
    if (state == "complete") return std::unique_ptr<State>(new StateComplete);
    if (state == "delete") return std::unique_ptr<State>(new StateDelete);
    if (state == "label") return std::unique_ptr<State>(new StateLabel);
    if (state == "show") return std::unique_ptr<State>(new StateShow);
    throw std::runtime_error("There is no such state");
}

std::unique_ptr<State> Factory::CreateStateAdd(const std::string &state) {
    if (state == "title") return std::unique_ptr<State>(new StateAddTitle);
    if (state == "priority") return std::unique_ptr<State>(new StateAddPriority);
    if (state == "time") return std::unique_ptr<State>(new StateAddTime);
    throw std::runtime_error("There is no such state");
}