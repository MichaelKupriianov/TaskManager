#pragma once

#include <memory>
#include "factory/Factory.h"
#include "view/View.h"

class DependencyForSteps {
public:
    DependencyForSteps(const std::shared_ptr<Factory> &, const std::shared_ptr<View> &);

    virtual std::shared_ptr<Factory> factory() { return factory_; }
    virtual std::shared_ptr<View> view() { return view_; }

    virtual ~DependencyForSteps() = default;
private:
    const std::shared_ptr<Factory> factory_;
    const std::shared_ptr<View> view_;
};
