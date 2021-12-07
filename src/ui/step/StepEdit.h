#pragma once

#include<memory>
#include"Step.h"
#include"Command.h"
#include"Context.h"
#include"Reader.h"

class StepEdit : public Step {
public:
    explicit StepEdit(std::shared_ptr<Reader> &);
    std::unique_ptr<Step> execute(Context &, std::shared_ptr<Factory> &) override;
private:
    std::shared_ptr<Reader> reader_;
    Command command_;
};