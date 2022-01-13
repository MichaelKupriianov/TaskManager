#pragma once

#include <memory>
#include "Step.h"
#include "ui/Context.h"

namespace ui::step {

class Show : public Step {
public:
    Show(const std::shared_ptr<Factory>&, const std::shared_ptr<View>&);
    ~Show() override = default;

    std::shared_ptr<Step> execute(Context&) override;
    std::string name();
private:
    std::shared_ptr<Factory> factory_;
    std::shared_ptr<View> view_;
};

class ShowTask : public Step {
public:
    ShowTask(const std::shared_ptr<Factory>&, const std::shared_ptr<View>&);
    ~ShowTask() override = default;

    std::shared_ptr<Step> execute(Context&) override;
    std::string name();
private:
    std::shared_ptr<Factory> factory_;
    std::shared_ptr<View> view_;
};

class ShowLabel : public Step {
public:
    ShowLabel(const std::shared_ptr<Factory>&, const std::shared_ptr<View>&);
    ~ShowLabel() override = default;

    std::shared_ptr<Step> execute(Context&) override;
    std::string name();
private:
    std::shared_ptr<Factory> factory_;
    std::shared_ptr<View> view_;
};
}