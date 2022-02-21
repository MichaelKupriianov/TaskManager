#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ui/controller/DefaultController.h"
#include "model/ModelMock.h"

using ::testing::Return;

class DefaultControllerTest : public ::testing::Test {
public:
    void SetUp() override {
        model_ = std::make_shared<ModelMock>(
                std::make_shared<model::TaskManager>(std::make_shared<model::IdGenerator>()));
        controller_ = std::make_shared<ui::DefaultController>(model_);
    }

protected:
    std::shared_ptr<ui::DefaultController> controller_;
    std::shared_ptr<ModelMock> model_;
};

TEST_F(DefaultControllerTest, shouldAddTask) {
    Task task{CreateTask("add")};
    EXPECT_CALL(*model_, AddTask(*task_)).WillOnce(Return(true));
    EXPECT_TRUE(controller_->AddTask(*task_));
}

bool AddTask(const Task& task)
override {
return model_->
AddTask(task);
}
bool AddSubTask(const Task& task, const TaskId& id)
override {
return model_->
AddSubTask(task, id
); }
bool Edit(const TaskId& id, const Task& task)
override {
return model_->
Edit(id, task
); }
bool Complete(const TaskId& id)
override {
return model_->
Complete(id);
}
bool Delete(const TaskId& id)
override {
return model_->
Delete(id);
}

ManyTasksWithId ShowByLabel(const std::string& label, const TasksSortBy& sort_by)
override {
return model_->
ShowByLabel(label, sort_by
);
}
ManyTasksWithId ShowParents(const TasksSortBy& sort_by)
override {
return model_->
ShowParents(sort_by);
}
CompositeTask ShowTask(const TaskId& id, const TasksSortBy& sort_by)
override {
return model_->
ShowTask(id, sort_by
);
}
ManyCompositeTasks ShowAll(const TasksSortBy& sort_by)
override {
return model_->
ShowAll(sort_by);
}

bool Save(const std::string& filename)
override {
return model_->
Save(filename);
}
bool Load(const std::string& filename)
override {
return model_->
Load(filename);
}