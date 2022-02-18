#include "gtest/gtest.h"
#include <thread>
#include "ui/controller/DefaultController.h"
#include "ui/command/Command.h"

class MultiThreadingTest : public ::testing::Test {
public:
    void SetUp() override {
        controller_ = std::make_shared<ui::DefaultController>(
                std::make_shared<model::Model>(
                        std::make_shared<model::TaskManager>(std::make_shared<model::IdGenerator>())));
    }

    std::shared_ptr<ui::command::Command> RandomCommand() {
        int type{rand() % 10};
        auto task{CreateTask("title")};
        auto id{CreateTaskId(rand() % 64)};
        auto if_print_subtasks{static_cast<bool>(rand() % 2)};
        auto sort_by{static_cast<TasksSortBy>(rand() % 3)};

        switch (type) {
            case 0:
                return std::make_shared<ui::command::Add>(task);
            case 1:
                return std::make_shared<ui::command::AddSub>(task, id);
            case 2:
                return std::make_shared<ui::command::Edit>(id, task);
            case 3:
                return std::make_shared<ui::command::Complete>(id);
            case 4:
                return std::make_shared<ui::command::Delete>(id);
            case 5:
                return std::make_shared<ui::command::Show>(if_print_subtasks, sort_by);
            case 6:
                return std::make_shared<ui::command::ShowTask>(id, sort_by);
            case 7:
                return std::make_shared<ui::command::ShowByLabel>("", sort_by);
            case 8:
                return std::make_shared<ui::command::Save>("multi_threading_test");
            case 9:
                return std::make_shared<ui::command::Load>("multi_threading_test");
            default:
                return nullptr;
        }
    }

    void Run(int number) {
        for (int i = 0; i < number; i++)
            RandomCommand()->execute(controller_);
    }
protected:
    std::shared_ptr<ui::Controller> controller_;
};

TEST_F(MultiThreadingTest, shouldWorkWhenReceivesManyCommandsFromDifferentThreads) {
    int number_of_thread = 8;
    int number_of_commands = 512;

    std::vector<std::thread> threads;
    for (int i = 0; i < number_of_thread; i++)
        threads.emplace_back(&MultiThreadingTest::Run, this, number_of_commands);

    for (auto& thread: threads)
        thread.join();

    remove("multi_threading_test");
}