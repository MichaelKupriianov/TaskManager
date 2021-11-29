#include"Step.h"
#include<string>
#include<stdexcept>
#include"Factory.h"

std::unique_ptr<Step> StepRoot::execute(Context &context) {
    TypeOfStep command(reader_.ReadCommand());
    return Factory::CreateStep(command);
}

std::unique_ptr<Step> StepQuit::execute(Context &context) {
    reader_.Quit();
    context.finished();
    return Factory::GetRootStep();
}

std::unique_ptr<Step> StepHelp::execute(Context &context) {
    reader_.Help();
    return Factory::GetRootStep();
}

std::unique_ptr<Step> StepComplete::execute(Context &context) {
    context.set_id(reader_.ReadId());
    if (!reader_.Confirm()) {}
    return Factory::GetRootStep();
}

std::unique_ptr<Step> StepDelete::execute(Context &context) {
    context.set_id(reader_.ReadId());
    if (!reader_.Confirm()) {}
    return Factory::GetRootStep();
}

std::unique_ptr<Step> StepLabel::execute(Context &context) {
    context.set_id(reader_.ReadId());
    std::string label(reader_.ReadLabel());
    if (!reader_.Confirm()) {}
    return Factory::GetRootStep();
}

std::unique_ptr<Step> StepShow::execute(Context &context) {
    return Factory::GetRootStep();
}