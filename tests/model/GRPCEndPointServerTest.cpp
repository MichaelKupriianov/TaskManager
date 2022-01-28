#include <memory>
#include <utility>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "model/GRPCEndPoint.h"
#include "ModelMock.h"

using namespace model;
using ::testing::Return;

class GRPCEndPointServerTest : public ::testing::Test {
public:
    void SetUp() override {
        model_ = std::make_shared<ModelMock>(
                std::make_shared<TaskManager>(std::make_shared<IdGenerator>()));
        end_point_ = std::make_shared<GRPCEndPoint>(model_);

        task_ = std::make_shared<model::Task>();
        id_ = std::make_shared<model::TaskId>();
        auto task_with_id = std::make_shared<model::TaskWithId>(CreateTaskWithId(*id_, *task_));
        many_tasks_with_id = std::make_shared<model::ManyTasksWithId>();
        composite_task_ = std::make_shared<model::CompositeTask>(
                CreateCompositeTask(*task_with_id, *many_tasks_with_id));
        many_composite_tasks_ = std::make_shared<model::ManyCompositeTasks>();
    }
protected:
    std::shared_ptr<ModelMock> model_;
    std::shared_ptr<GRPCEndPoint> end_point_;

    std::shared_ptr<model::Task> task_;
    std::shared_ptr<model::TaskId> id_;
    std::shared_ptr<model::ManyTasksWithId> many_tasks_with_id;
    std::shared_ptr<model::CompositeTask> composite_task_;
    std::shared_ptr<model::ManyCompositeTasks> many_composite_tasks_;
};

TEST_F(GRPCEndPointServerTest, ShouldAddTask) {
    AddTaskResponse response;
    AddTaskRequest request;
    request.set_allocated_task(new Task(*task_));

    EXPECT_CALL(*model_, AddTask(*task_))
            .WillOnce(Return(true));
    auto result = end_point_->AddTask(nullptr, &request, &response);

    EXPECT_TRUE(result.ok());
    EXPECT_EQ(response.result(), true);
}

TEST_F(GRPCEndPointServerTest, ShouldAddSubTask) {
    AddSubTaskResponse response;
    AddSubTaskRequest request;
    request.set_allocated_task(new Task(*task_));
    request.set_allocated_parent_id(new TaskId(*id_));

    EXPECT_CALL(*model_, AddSubTask(*task_, *id_))
            .WillOnce(Return(false));
    auto result = end_point_->AddSubTask(nullptr, &request, &response);

    EXPECT_TRUE(result.ok());
    EXPECT_EQ(response.result(), false);
}

TEST_F(GRPCEndPointServerTest, ShouldEditTask) {
    EditResponse response;
    EditRequest request;
    request.set_allocated_task(new Task(*task_));
    request.set_allocated_id(new TaskId(*id_));

    EXPECT_CALL(*model_, Edit(*id_, *task_))
            .WillOnce(Return(true));
    auto result = end_point_->Edit(nullptr, &request, &response);

    EXPECT_TRUE(result.ok());
    EXPECT_EQ(response.result(), true);
}

TEST_F(GRPCEndPointServerTest, ShouldCompleteTask) {
    CompleteResponse response;
    CompleteRequest request;
    request.set_allocated_id(new TaskId(*id_));

    EXPECT_CALL(*model_, Complete(*id_))
            .WillOnce(Return(true));
    auto result = end_point_->Complete(nullptr, &request, &response);

    EXPECT_TRUE(result.ok());
    EXPECT_EQ(response.result(), true);
}

TEST_F(GRPCEndPointServerTest, ShouldDeleteTask) {
    DeleteResponse response;
    DeleteRequest request;
    request.set_allocated_id(new TaskId(*id_));

    EXPECT_CALL(*model_, Delete(*id_))
            .WillOnce(Return(true));
    auto result = end_point_->Delete(nullptr, &request, &response);

    EXPECT_TRUE(result.ok());
    EXPECT_EQ(response.result(), true);
}

TEST_F(GRPCEndPointServerTest, ShouldShowTasksByLabel) {
    ShowByLabelResponse response;
    ShowByLabelRequest request;
    request.set_label("label");
    request.set_sort_by(TasksSortBy::ID);

    EXPECT_CALL(*model_, ShowByLabel("label", TasksSortBy::ID))
            .WillOnce(Return(*many_tasks_with_id));
    auto result = end_point_->ShowByLabel(nullptr, &request, &response);

    EXPECT_TRUE(result.ok());
    EXPECT_EQ(response.tasks(), *many_tasks_with_id);
}

TEST_F(GRPCEndPointServerTest, ShouldShowParents) {
    ShowParentsResponse response;
    ShowParentsRequest request;
    request.set_sort_by(TasksSortBy::DATE);

    EXPECT_CALL(*model_, ShowParents(TasksSortBy::DATE))
            .WillOnce(Return(*many_tasks_with_id));
    auto result = end_point_->ShowParents(nullptr, &request, &response);

    EXPECT_TRUE(result.ok());
    EXPECT_EQ(response.tasks(), *many_tasks_with_id);
}

TEST_F(GRPCEndPointServerTest, ShouldShowTask) {
    ShowTaskResponse response;
    ShowTaskRequest request;
    request.set_sort_by(TasksSortBy::DATE);
    request.set_allocated_id(new TaskId(*id_));

    EXPECT_CALL(*model_, ShowTask(*id_, TasksSortBy::DATE))
            .WillOnce(Return(*composite_task_));
    auto result = end_point_->ShowTask(nullptr, &request, &response);

    EXPECT_TRUE(result.ok());
    EXPECT_EQ(response.task(), *composite_task_);
}

TEST_F(GRPCEndPointServerTest, ShouldShowAllTasks) {
    ShowAllResponse response;
    ShowAllRequest request;
    request.set_sort_by(TasksSortBy::ID);

    EXPECT_CALL(*model_, ShowAll(TasksSortBy::ID))
            .WillOnce(Return(*many_composite_tasks_));
    auto result = end_point_->ShowAll(nullptr, &request, &response);

    EXPECT_TRUE(result.ok());
    EXPECT_EQ(response.tasks(), *many_composite_tasks_);
}

TEST_F(GRPCEndPointServerTest, ShouldSave) {
    SaveResponse response;
    SaveRequest request;
    request.set_filename("filename");

    EXPECT_CALL(*model_, Save("filename"))
            .WillOnce(Return(false));
    auto result = end_point_->Save(nullptr, &request, &response);

    EXPECT_TRUE(result.ok());
    EXPECT_EQ(response.result(), false);
}

TEST_F(GRPCEndPointServerTest, ShouldLoad) {
    LoadResponse response;
    LoadRequest request;
    request.set_filename("filename");

    EXPECT_CALL(*model_, Load("filename"))
            .WillOnce(Return(true));
    auto result = end_point_->Load(nullptr, &request, &response);

    EXPECT_TRUE(result.ok());
    EXPECT_EQ(response.result(), true);
}