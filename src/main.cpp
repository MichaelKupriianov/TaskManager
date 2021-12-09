#include<memory>
#include"Reader.h"
#include"Printer.h"
#include"View.h"
#include"Factory.h"
#include"Dependency.h"
#include"StepMachine.h"
#include"TaskManager.h"
#include"Controller.h"

int main() {
    std::shared_ptr<Reader> reader{new Reader};
    std::shared_ptr<Printer> printer{new Printer};
    std::shared_ptr<View> view{new View{reader, printer}};
    std::shared_ptr<Factory> factory{new Factory};
    std::shared_ptr<Dependency> dependency{new Dependency{factory, view}};
    std::shared_ptr<StepMachine> machine{new StepMachine{dependency}};
    std::shared_ptr<TaskManager> manager{new TaskManager};
    Controller controller{machine, manager};
    controller.Run();
    return 0;
}
