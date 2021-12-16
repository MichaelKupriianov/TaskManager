#pragma once

#include<memory>
#include"SubStep.h"

class SubFactory {
public:
    virtual std::shared_ptr<SubStep> GetRootSubStep();
    virtual std::shared_ptr<SubStep> GetNextSubStep(const SubStepTitle &);
    virtual std::shared_ptr<SubStep> GetNextSubStep(const SubStepPriority &);
    virtual std::shared_ptr<SubStep> GetNextSubStep(const SubStepDate &);
    virtual std::shared_ptr<SubStep> GetNextSubStep(const SubStepLabel &);
    virtual ~SubFactory() = default;
};