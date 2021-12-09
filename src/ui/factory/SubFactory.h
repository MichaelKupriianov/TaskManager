#pragma once

#include<memory>
#include"SubStep.h"

class SubFactory {
public:
    std::unique_ptr<SubStep> GetRootSubStep();
    std::unique_ptr<SubStep> GetNextSubStep(const SubStepTitle &);
    std::unique_ptr<SubStep> GetNextSubStep(const SubStepPriority &);
    std::unique_ptr<SubStep> GetNextSubStep(const SubStepDate &);
};