#include "gtest/gtest.h"
#include <thread>
#include "model/Model.h"

class MultiThreadingTest : public ::testing::Test {
public:
    void SetUp() override {
        model_ = std::make_shared<model::Model>(
                std::make_shared<model::TaskManager>(std::make_shared<model::IdGenerator>()));
    }

    void ExecuteRandomCommand() {
        int type{rand() % 11};
        auto task{CreateTask("title")};
        auto id{CreateTaskId(rand() % 64)};
        auto sort_by{static_cast<TasksSortBy>(rand() % 3)};

        switch (type) {
            case 0:
                model_->AddTask(task);
            case 1:
                model_->AddSubTask(task, id);
            case 2:
                model_->Edit(id, task);
            case 3:
                model_->Complete(id);
            case 4:
                model_->Delete(id);
            case 5:
                model_->ShowByLabel("", sort_by);
            case 6:
                model_->ShowParents(sort_by);
            case 7:
                model_->ShowTask(id, sort_by);
            case 8:
                model_->ShowAll(sort_by);
            case 9:
                model_->Save("multi_threading_test");
            case 10:
                model_->Load("multi_threading_test");
        }
    }

    void Run(int number) {
        for (int i = 0; i < number; i++)
            ExecuteRandomCommand();
    }
protected:
    std::shared_ptr<model::Model> model_;
};

TEST_F(MultiThreadingTest, shouldWorkWhenReceivesManyCommandsFromDifferentThreads) {
    int number_of_thread = 16;
    int number_of_commands = 1024;

    std::vector<std::thread> threads;
    for (int i = 0; i < number_of_thread; i++)
        threads.emplace_back(&MultiThreadingTest::Run, this, number_of_commands);

    for (auto& thread: threads)
        thread.join();

    remove("multi_threading_test");
}