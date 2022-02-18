#include "gtest/gtest.h"
#include <thread>
#include "ui/controller/DefaultController.h"
#include "ui/command/Command.h"

class MultiThreadServerTest : public ::testing::Test {
public:
    void SetUp() override {
        controller_ = std::make_shared<ui::DefaultController>(
                std::make_shared<model::Model>(
                        std::make_shared<model::TaskManager>(std::make_shared<model::IdGenerator>())));
    }

    std::shared_ptr<ui::command::Command> CreateRandomCommand() {
        int cmd_type = rand() % 3;

        TaskId id;
        id.set_value(rand() % 200);
        auto task = CreateTask("task");

        switch (cmd_type) {
            case 0:
                return std::make_shared<ui::command::Add>(task);
            case 1:
                return std::make_shared<ui::command::Edit>(id, task);
            case 3:
                return std::make_shared<ui::command::Complete>(id);
            default:
                return nullptr;
        }
    }

    void ExecuteRandomCommandToTaskManager(const int times) {
        for (int i = 0; i < times; ++i) {
            auto command = CreateRandomCommand();
            command->execute(controller_);
        }
    }
protected:
    std::shared_ptr<ui::Controller> controller_;
};

TEST_F(MultiThreadServerTest, shouldWorkWhenReceivesManyCommandsFromDifferentThreads) {
    const int thread_count = 8;
    const int commands_per_thread = 1000;

    std::vector<std::thread> threads;
    for (int i = 0; i < thread_count; ++i) {
        std::thread t{&MultiThreadServerTest::ExecuteRandomCommandToTaskManager, this, commands_per_thread};
        threads.push_back(std::move(t));
    }

    for (auto& thread: threads)
        thread.join();
}