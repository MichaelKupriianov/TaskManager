#pragma once

#include <memory>
#include "step/Step.h"
#include "step/SubStepOwners.h"
#include "step/SubSteps.h"
#include "step/Type.h"
#include "view/View.h"

namespace ui {
class Factory : public std::enable_shared_from_this<Factory> {
public:
    explicit Factory(const std::shared_ptr<View>& view);
    virtual ~Factory() = default;

    virtual std::shared_ptr<step::Step> CreateStep(step::Type type);
    virtual std::shared_ptr<step::Step> GetInitialStep();

    virtual std::shared_ptr<step::Step> GetInitialSubStep();
    virtual std::shared_ptr<step::Step> GetNextSubStepFrom(const step::SubStepTitle&);
    virtual std::shared_ptr<step::Step> GetNextSubStepFrom(const step::SubStepPriority&);
    virtual std::shared_ptr<step::Step> GetNextSubStepFrom(const step::SubStepDate&);
    virtual std::shared_ptr<step::Step> GetNextSubStepFrom(const step::SubStepLabel&);
private:
    const std::shared_ptr<View> view_;
};
}