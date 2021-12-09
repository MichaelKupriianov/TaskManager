#pragma once

#include<memory>
#include"Factory.h"
#include"View.h"

class Dependency {
public:
    Dependency(const std::shared_ptr<Factory> &, const std::shared_ptr<View> &);

    std::shared_ptr<Factory> factory() { return factory_; }
    std::shared_ptr<View> view() { return view_; }
private:
    const std::shared_ptr<Factory> factory_;
    const std::shared_ptr<View> view_;
};
