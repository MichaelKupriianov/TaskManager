#pragma once

#include <memory>
#include "factory/SubFactory.h"
#include "view/View.h"

class DependencyForSubSteps {
public:
    DependencyForSubSteps(const std::shared_ptr<SubFactory> &, const std::shared_ptr<View> &, TypeOfStep);

    std::shared_ptr<SubFactory> factory() { return factory_; }
    std::shared_ptr<View> view() { return view_; }
    TypeOfStep command() { return command_; }
private:
    const std::shared_ptr<SubFactory> factory_;
    const std::shared_ptr<View> view_;
    const TypeOfStep command_;
};
