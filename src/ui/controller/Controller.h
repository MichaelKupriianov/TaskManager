#pragma once

#include<memory>
#include"StepMachine.h"
#include"TaskManager.h"

class Controller {
public:
    Controller(const std::shared_ptr<StepMachine> &, const std::shared_ptr<TaskManager> &);

    void Run();
private:
    const std::shared_ptr<StepMachine> step_machine_;
    const std::shared_ptr<TaskManager> task_manager_;
};
