#pragma once

#include <memory>
#include "ui/Context.h"

namespace ui::step {
    class Resources;

    class SubStep {
    public:
        virtual std::shared_ptr<SubStep> execute(SubContext&, const std::shared_ptr<Resources>&) = 0;
        virtual ~SubStep() = default;
    };

    class SubStepTitle : public SubStep {
    public:
        std::shared_ptr<SubStep> execute(SubContext&, const std::shared_ptr<Resources>&) override;
        ~SubStepTitle() override = default;
    };

    class SubStepPriority : public SubStep {
    public:
        std::shared_ptr<SubStep> execute(SubContext&, const std::shared_ptr<Resources>&) override;
        ~SubStepPriority() override = default;
    };

    class SubStepDate : public SubStep {
    public:
        std::shared_ptr<SubStep> execute(SubContext&, const std::shared_ptr<Resources>&) override;
        ~SubStepDate() override = default;
    };

    class SubStepLabel : public SubStep {
    public:
        std::shared_ptr<SubStep> execute(SubContext&, const std::shared_ptr<Resources>&) override;
        ~SubStepLabel() override = default;
    };
}