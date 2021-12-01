#include "SubStepMachine.h"

SubContext SubStepMachine::Run(const Reader &manager) {
    SubContext sub_context;
    while(!sub_context.if_finished()) {
        state_=std::move(state_->execute(sub_context, manager));
    }
    return sub_context;
}