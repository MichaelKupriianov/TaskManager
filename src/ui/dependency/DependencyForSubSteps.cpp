#include "DependencyForSubSteps.h"

DependencyForSubSteps::DependencyForSubSteps(const std::shared_ptr<SubFactory> &factory,
                             const std::shared_ptr<View> &view, TypeOfStep command)
        : factory_{factory}, view_{view}, command_{command} {}