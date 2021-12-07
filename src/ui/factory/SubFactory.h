#pragma once

#include<memory>
#include"SubStep.h"
#include"Reader.h"
#include"Command.h"

class SubFactory {
public:
    SubFactory(std::shared_ptr<Reader> &, Command);

    std::unique_ptr<SubStep> GetRootSubStep();
    std::unique_ptr<SubStep> GetNextSubStep(const SubStepTitle &);
    std::unique_ptr<SubStep> GetNextSubStep(const SubStepPriority &);
    std::unique_ptr<SubStep> GetNextSubStep(const SubStepDate &);
private:
    std::shared_ptr<Reader> reader_;
    Command command_;
};