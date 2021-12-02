#include"Step.h"
#include<string>
#include"Factory.h"

std::unique_ptr<Step> StepRoot::execute(Context &context) {
    TypeOfStep command(reader_.ReadCommand());
    return Factory::CreateStep(command);
}

std::unique_ptr<Step> StepQuit::execute(Context &context) {
    reader_.Quit();
    context.set_command(Command::QUIT);
    return Factory::GetRootStep();
}

std::unique_ptr<Step> StepHelp::execute(Context &context) {
    reader_.Help();
    return Factory::GetRootStep();
}

std::unique_ptr<Step> StepComplete::execute(Context &context) {
    context.set_id(reader_.ReadId());
    if (reader_.Confirm()) {
        context.set_command(Command::COMPLETE);
    }
    return Factory::GetRootStep();
}

std::unique_ptr<Step> StepDelete::execute(Context &context) {
    context.set_id(reader_.ReadId());
    if (reader_.Confirm()) {
        context.set_command(Command::DELETE);
    }
    return Factory::GetRootStep();
}

std::unique_ptr<Step> StepLabel::execute(Context &context) {
    context.set_id(reader_.ReadId());
    context.set_label(reader_.ReadLabel());
    if (reader_.Confirm()) {
        context.set_command(Command::LABEL);
    }
    return Factory::GetRootStep();
}

std::unique_ptr<Step> StepShow::execute(Context &context) {
    context.set_command(Command::SHOW);
    return Factory::GetRootStep();
}