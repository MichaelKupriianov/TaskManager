#pragma once

#include <memory>
#include <optional>
#include "ui/Factory.h"
#include "ui/view/View.h"
#include "ui/step/Type.h"

namespace ui::step {
    struct Resources {
    public:
        Resources(const std::shared_ptr<Factory>& i_factory, const std::shared_ptr<View>& i_view)
                : factory{i_factory}, view{i_view} {}

        Resources(const std::shared_ptr<Factory>& i_factory, const std::shared_ptr<View>& i_view, step::Type i_command)
                : factory{i_factory}, view{i_view}, command{i_command} {}

        const std::shared_ptr<Factory> factory;
        const std::shared_ptr<View> view;
        const std::optional<step::Type> command;
    };
}
