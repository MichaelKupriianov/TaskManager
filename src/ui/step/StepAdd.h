#pragma once

#include<memory>
#include"Step.h"
#include"Command.h"
#include"Reader.h"
#include"Context.h"

class StepAdd : public Step {
public:
    explicit StepAdd(std::shared_ptr<Reader> &);
    std::unique_ptr<Step> execute(Context &, std::shared_ptr<Factory> &) override;
private:
    std::shared_ptr<Reader> reader_;
    Command command_;
};