#include "SubDependency.h"

SubDependency::SubDependency(const std::shared_ptr<SubFactory> &factory,
                             const std::shared_ptr<View> &view, TypeOfCommand command)
        : factory_{factory}, view_{view}, command_{command} {}