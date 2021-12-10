#pragma once

#include<memory>
#include"Factory.h"
#include"View.h"

class Dependency {
public:
    Dependency(const std::shared_ptr<Factory> &, const std::shared_ptr<View> &);

    virtual std::shared_ptr<Factory> factory() { return factory_; }
    virtual std::shared_ptr<View> view() { return view_; }

    virtual ~Dependency() = default;
private:
    const std::shared_ptr<Factory> factory_;
    const std::shared_ptr<View> view_;
};
