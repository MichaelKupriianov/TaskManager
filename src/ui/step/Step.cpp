#include"Step.h"
#include<string>
#include"Factory.h"

StepRoot::StepRoot(std::shared_ptr<Reader> &reader) :
        reader_{reader} {}

std::unique_ptr<Step> StepRoot::execute(Context &context, std::shared_ptr<Factory> &factory) {
    TypeOfStep command(reader_->ReadCommand());
    return factory->CreateStep(command);
}

StepQuit::StepQuit(std::shared_ptr<Reader> &reader) :
        reader_{reader}, command_{Command::QUIT} {}

std::unique_ptr<Step> StepQuit::execute(Context &context, std::shared_ptr<Factory> &factory) {
    reader_->Quit();
    context.set_command(command_);
    return factory->GetRootStep();
}

StepHelp::StepHelp(std::shared_ptr<Reader> &reader) :
        reader_{reader} {}

std::unique_ptr<Step> StepHelp::execute(Context &context, std::shared_ptr<Factory> &factory) {
    reader_->Help();
    return factory->GetRootStep();
}

StepComplete::StepComplete(std::shared_ptr<Reader> &reader) :
        reader_{reader}, command_{Command::COMPLETE} {}

std::unique_ptr<Step> StepComplete::execute(Context &context, std::shared_ptr<Factory> &factory) {
    int id{reader_->ReadId(command_)};
    if (reader_->Confirm()) {
        context.set_command(command_);
        context.set_id(id);
    }
    return factory->GetRootStep();
}

StepDelete::StepDelete(std::shared_ptr<Reader> &reader) :
        reader_{reader}, command_{Command::DELETE} {}

std::unique_ptr<Step> StepDelete::execute(Context &context, std::shared_ptr<Factory> &factory) {
    int id{reader_->ReadId(command_)};
    if (reader_->Confirm()) {
        context.set_command(command_);
        context.set_id(id);
    }
    return factory->GetRootStep();
}

StepLabel::StepLabel(std::shared_ptr<Reader> &reader) :
        reader_{reader}, command_{Command::LABEL} {}

std::unique_ptr<Step> StepLabel::execute(Context &context, std::shared_ptr<Factory> &factory) {
    int id{reader_->ReadId(command_)};
    std::string label{reader_->ReadLabel(command_)};
    if (reader_->Confirm()) {
        context.set_command(command_);
        context.set_id(id);
        context.set_label(label);
    }
    return factory->GetRootStep();
}

StepShow::StepShow(std::shared_ptr<Reader> &reader) :
        reader_{reader}, command_{Command::SHOW} {}

std::unique_ptr<Step> StepShow::execute(Context &context, std::shared_ptr<Factory> &factory) {
    context.set_command(command_);
    return factory->GetRootStep();
}