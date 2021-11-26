#pragma once

#include<memory>
#include"SubStep.h"

class SubFactory {
public:
    static std::unique_ptr<SubStep> GetRootSubStep();
    static std::unique_ptr<SubStep> GetNextSubStep(const SubStepTitle &);
    static std::unique_ptr<SubStep> GetNextSubStep(const SubStepPriority &);
    static std::unique_ptr<SubStep> GetNextSubStep(const SubStepTime &);
};