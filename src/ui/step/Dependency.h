#pragma once

#include <memory>
#include "ui/factory/Factory.h"
#include "ui/view/View.h"

namespace step {
    struct Dependency {
    public:
        Dependency(const std::shared_ptr<Factory> &i_factory, const std::shared_ptr<View> &i_view)
                : factory{i_factory}, view{i_view} {}

        const std::shared_ptr<Factory> factory;
        const std::shared_ptr<View> view;
    };
}
