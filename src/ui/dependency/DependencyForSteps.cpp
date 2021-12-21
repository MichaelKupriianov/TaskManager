#include "DependencyForSteps.h"

DependencyForSteps::DependencyForSteps(const std::shared_ptr<Factory> &factory, const std::shared_ptr<View> &view)
        : factory_{factory}, view_{view} {}