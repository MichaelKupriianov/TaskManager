#pragma once

#include <memory>
#include "step/Step.h"
#include "step/Add.h"
#include "step/Edit.h"
#include "step/Show.h"
#include "step/SubStep.h"
#include "step/Type.h"

namespace ui {
class Factory {
public:
    virtual std::shared_ptr<step::Step> CreateStep(step::Type);
    virtual std::shared_ptr<step::Step> GetInitialStep();

    virtual std::shared_ptr<step::SubStep> GetInitialSubStep();
    virtual std::shared_ptr<step::SubStep> GetNextSubStepFrom(const step::SubStepTitle&);
    virtual std::shared_ptr<step::SubStep> GetNextSubStepFrom(const step::SubStepPriority&);
    virtual std::shared_ptr<step::SubStep> GetNextSubStepFrom(const step::SubStepDate&);
    virtual std::shared_ptr<step::SubStep> GetNextSubStepFrom(const step::SubStepLabel&);

    virtual ~Factory() = default;
};
}