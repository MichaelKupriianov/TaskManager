#pragma once

#include<memory>
#include"SubContext.h"
#include"Command.h"
#include"Reader.h"

class SubFactory;

class SubStep {
public:
    virtual std::unique_ptr<SubStep> execute(SubContext &, std::shared_ptr<SubFactory> &) = 0;
    virtual ~SubStep() = default;
};

class SubStepTitle : public SubStep {
public:
    SubStepTitle(std::shared_ptr<Reader> &, Command);

    std::unique_ptr<SubStep> execute(SubContext &, std::shared_ptr<SubFactory> &) override;
private:
    std::shared_ptr<Reader> reader_;
    Command command_;
};

class SubStepPriority : public SubStep {
public:
    SubStepPriority(std::shared_ptr<Reader> &, Command);

    std::unique_ptr<SubStep> execute(SubContext &, std::shared_ptr<SubFactory> &) override;
private:
    std::shared_ptr<Reader> reader_;
    Command command_;
};

class SubStepDate : public SubStep {
public:
    SubStepDate(std::shared_ptr<Reader> &, Command);

    std::unique_ptr<SubStep> execute(SubContext &, std::shared_ptr<SubFactory> &) override;
private:
    std::shared_ptr<Reader> reader_;
    Command command_;
};