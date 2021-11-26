#include"Step.h"
#include<string>
#include<stdexcept>
#include"Factory.h"

std::unique_ptr<Step> StepRoot::execute(Context &context) {
    TypeOfStep command(console_manager_.ReadCommand());
    return Factory::CreateStep(command);
}

std::unique_ptr<Step> StepQuit::execute(Context &context) {
    console_manager_.Quit();
    context.finished();
    return Factory::GetRootStep();
}

std::unique_ptr<Step> StepHelp::execute(Context &context) {
    console_manager_.Help();
    return Factory::GetRootStep();
}

std::unique_ptr<Step> StepComplete::execute(Context &context) {
    context.set_id(console_manager_.ReadId());
    if (!console_manager_.Confirm()) {}
    return Factory::GetRootStep();
}

std::unique_ptr<Step> StepDelete::execute(Context &context) {
    context.set_id(console_manager_.ReadId());
    if (!console_manager_.Confirm()) {}
    return Factory::GetRootStep();
}

std::unique_ptr<Step> StepLabel::execute(Context &context) {
    context.set_id(console_manager_.ReadId());
    std::string label(console_manager_.ReadLabel());
    if (!console_manager_.Confirm()) {}
    return Factory::GetRootStep();
}

std::unique_ptr<Step> StepShow::execute(Context &context) {
    return Factory::GetRootStep();
}