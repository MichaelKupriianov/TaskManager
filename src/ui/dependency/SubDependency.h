#pragma once

#include<memory>
#include"SubFactory.h"
#include"View.h"
#include"TypeOfCommand.h"

class SubDependency {
public:
    SubDependency(const std::shared_ptr<SubFactory> &, const std::shared_ptr<View> &, TypeOfCommand);

    std::shared_ptr<SubFactory> factory() { return factory_; }
    std::shared_ptr<View> view() { return view_; }
    TypeOfCommand command() { return command_; }
private:
    const std::shared_ptr<SubFactory> factory_;
    const std::shared_ptr<View> view_;
    const TypeOfCommand command_;
};
