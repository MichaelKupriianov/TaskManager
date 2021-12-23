#pragma once

#include <memory>
#include "Step.h"
#include "ui/Context.h"

namespace ui::step {

    class Add : public Step {
    public:
        Add();
        std::shared_ptr<Step> execute(Context&, const std::shared_ptr<Resources>&) override;
    private:
        const Type type_;
    };

    class AddSub : public Step {
    public:
        AddSub();
        std::shared_ptr<Step> execute(Context&, const std::shared_ptr<Resources>&) override;
    private:
        const Type type_;
    };
}