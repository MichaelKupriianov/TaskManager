#pragma once

#include <memory>
#include "Step.h"
#include "ui/Context.h"

namespace ui::step {

    class Show : public Step {
    public:
        Show();
        std::shared_ptr<Step> execute(Context&, const std::shared_ptr<Resources>&) override;
    private:
        const step::Type type_;
    };

    class ShowTask : public Step {
    public:
        ShowTask();
        std::shared_ptr<Step> execute(Context&, const std::shared_ptr<Resources>&) override;
    private:
        const step::Type type_;
    };

    class ShowLabel : public Step {
    public:
        ShowLabel();
        std::shared_ptr<Step> execute(Context&, const std::shared_ptr<Resources>&) override;
    private:
        const step::Type type_;
    };
}