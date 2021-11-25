#pragma once

#include<string>
#include<memory>
#include"Step.h"
#include"StepAdd.h"
#include"StepEdit.h"
#include"SubStep.h"

class Factory {
public:
    static std::unique_ptr<Step> CreateStep(const std::string &);

    static std::unique_ptr<Step> GetNextStep();
    static std::unique_ptr<SubStep> GetNextSubStep();
    static std::unique_ptr<SubStep> GetNextSubStep(const SubStepTitle &);
    static std::unique_ptr<SubStep> GetNextSubStep(const SubStepPriority &);
    static std::unique_ptr<SubStep> GetNextSubStep(const SubStepTime &);
};
