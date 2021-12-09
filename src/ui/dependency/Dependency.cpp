#include "Dependency.h"

Dependency::Dependency(const std::shared_ptr<Factory> &factory, const std::shared_ptr<View> &view)
        : factory_{factory}, view_{view} {}