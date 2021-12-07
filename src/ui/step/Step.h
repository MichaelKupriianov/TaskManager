#pragma once

#include<memory>
#include"Context.h"
#include"Reader.h"
#include"Command.h"

class Factory;

class Step {
public:
    virtual std::unique_ptr<Step> execute(Context &, std::shared_ptr<Factory> &) = 0;
    virtual ~Step() = default;
};

class StepRoot final : public Step {
public:
    explicit StepRoot(std::shared_ptr<Reader> &);
    std::unique_ptr<Step> execute(Context &, std::shared_ptr<Factory> &) override;
private:
    std::shared_ptr<Reader> reader_;
};

class StepQuit : public Step {
public:
    explicit StepQuit(std::shared_ptr<Reader> &);
    std::unique_ptr<Step> execute(Context &, std::shared_ptr<Factory> &) override;
private:
    std::shared_ptr<Reader> reader_;
    Command command_;
};

class StepHelp : public Step {
public:
    explicit StepHelp(std::shared_ptr<Reader> &);
    std::unique_ptr<Step> execute(Context &, std::shared_ptr<Factory> &) override;
private:
    std::shared_ptr<Reader> reader_;
};

class StepComplete : public Step {
public:
    explicit StepComplete(std::shared_ptr<Reader> &);
    std::unique_ptr<Step> execute(Context &, std::shared_ptr<Factory> &) override;
private:
    std::shared_ptr<Reader> reader_;
    Command command_;
};

class StepDelete : public Step {
public:
    explicit StepDelete(std::shared_ptr<Reader> &);
    std::unique_ptr<Step> execute(Context &, std::shared_ptr<Factory> &) override;
private:
    std::shared_ptr<Reader> reader_;
    Command command_;
};

class StepLabel : public Step {
public:
    explicit StepLabel(std::shared_ptr<Reader> &);
    std::unique_ptr<Step> execute(Context &, std::shared_ptr<Factory> &) override;
private:
    std::shared_ptr<Reader> reader_;
    Command command_;
};

class StepShow : public Step {
public:
    explicit StepShow(std::shared_ptr<Reader> &);
    std::unique_ptr<Step> execute(Context &, std::shared_ptr<Factory> &) override;
private:
    std::shared_ptr<Reader> reader_;
    Command command_;
};