#include "SubStepMachine.h"
#include"SubContext.h"
#include"SubStep.h"

SubStepMachine::SubStepMachine(std::shared_ptr<SubFactory> &factory) :
        factory_{factory} {}

SubContext SubStepMachine::Run() {
    SubContext sub_context;
    std::unique_ptr<SubStep> step{factory_->GetRootSubStep()};
    while (!sub_context.if_finished()) {
        step = std::move(step->execute(sub_context, factory_));
    }
    return sub_context;
}