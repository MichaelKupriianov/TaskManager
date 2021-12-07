#include<memory>
#include"Controller.h"
#include"Reader.h"
#include"Printer.h"
#include"Factory.h"
#include"StepMachine.h"
#include"TaskManager.h"

int main() {
    std::shared_ptr<Reader> reader(new Reader);
    std::shared_ptr<Printer> printer(new Printer);
    std::shared_ptr<Factory> factory(new Factory(reader));
    std::shared_ptr<StepMachine> machine(new StepMachine(factory));
    std::shared_ptr<TaskManager> manager(new TaskManager);
    Controller controller(machine, manager, printer);
    controller.Run();
    return 0;
}
