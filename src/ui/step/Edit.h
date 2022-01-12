#pragma once

#include <memory>
#include "Step.h"
#include "ui/Context.h"

namespace ui::step {
class Edit : public Step {
public:
    Edit();
    std::shared_ptr<Step> execute(Context&, const std::shared_ptr<Resources>&) override;
private:
    const step::Type type_;
};
}