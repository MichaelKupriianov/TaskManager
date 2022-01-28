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
    Task task{CreateTask("first")};
    AddTaskResponse response;
    AddTaskRequest request;
    request.set_allocated_task(new Task(task));

    EXPECT_CALL(*model_, AddTask(task))
            .WillOnce(Return(true));
    auto result = end_point_->AddTask(nullptr, &request, &response);

    EXPECT_TRUE(result.ok());
    EXPECT_EQ(response.result(), true);
}

TEST_F(GRPCEndPointServerTest, ShouldAddSubTask) {
    Task task{CreateTask("first")};
    TaskId id{CreateTaskId(0)};
    AddSubTaskResponse response;
    AddSubTaskRequest request;
    request.set_allocated_task(new Task(task));
    request.set_allocated_parent_id(new TaskId(id));

    EXPECT_CALL(*model_, AddSubTask(task, id))
            .WillOnce(Return(false));
    auto result = end_point_->AddSubTask(nullptr, &request, &response);

    EXPECT_TRUE(result.ok());
    EXPECT_EQ(response.result(), false);
}

TEST_F(GRPCEndPointServerTest, ShouldEditTask) {
    Task task{CreateTask("first")};
    TaskId id{CreateTaskId(0)};
    EditResponse response;
    EditRequest request;
    request.set_allocated_task(new Task(task));
    request.set_allocated_id(new TaskId(id));

    EXPECT_CALL(*model_, Edit(id, task))
            .WillOnce(Return(true));
    auto result = end_point_->Edit(nullptr, &request, &response);

    EXPECT_TRUE(result.ok());
    EXPECT_EQ(response.result(), true);
}

TEST_F(GRPCEndPointServerTest, ShouldCompleteTask) {
    TaskId id{CreateTaskId(1)};
    CompleteResponse response;
    CompleteRequest request;
    request.set_allocated_id(new TaskId(id));

    EXPECT_CALL(*model_, Complete(id))
            .WillOnce(Return(true));
    auto result = end_point_->Complete(nullptr, &request, &response);

    EXPECT_TRUE(result.ok());
    EXPECT_EQ(response.result(), true);
}

TEST_F(GRPCEndPointServerTest, ShouldDeleteTask) {
    TaskId id{CreateTaskId(2)};
    DeleteResponse response;
    DeleteRequest request;
    request.set_allocated_id(new TaskId(id));

    EXPECT_CALL(*model_, Delete(id))
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

//TEST_F(GRPCServerEndPointTests, DeleteTask_ShouldAskModelToDeleteTaskAndReturnResult) {
//    // Arrange
//    const auto expected_model_result = TaskActionResult::FAIL_NOT_DELETED_SUBTASKS;
//    const bool expected_force_delete = true;
//    EXPECT_CALL(*model_, DeleteTask(expected_task_id_, expected_force_delete)).WillOnce(Return(expected_model_result));
//    GRPCServerEndPoint server_end_point{std::move(model_)};
//    DeleteTaskResponse response;
//    DeleteTaskRequest request;
//    request.set_allocated_task_id(new TaskId(expected_task_id_));
//    request.set_force_delete_subtasks(expected_force_delete);
//    // Act
//    const auto actual_result = server_end_point.DeleteTask(nullptr, &request, &response);
//    // Assert
//    EXPECT_TRUE(actual_result.ok());
//    EXPECT_EQ(TaskManagerServiceResult::FAIL_NOT_DELETED_SUBTASKS, response.result());
//}
//
//TEST_F(GRPCServerEndPointTests, CompleteTask_ShouldAskModelToCompleteTaskAndReturnResult) {
//    // Arrange
//    const auto expected_model_result = TaskActionResult::FAIL_UNCOMPLETED_SUBTASKS;
//    const bool expected_force_complete = true;
//    EXPECT_CALL(*model_, CompleteTask(expected_task_id_, expected_force_complete)).WillOnce(
//            Return(expected_model_result));
//    GRPCServerEndPoint server_end_point{std::move(model_)};
//    CompleteTaskResponse response;
//    CompleteTaskRequest request;
//    request.set_allocated_task_id(new TaskId(expected_task_id_));
//    request.set_force_complete_subtasks(expected_force_complete);
//    // Act
//    const auto actual_result = server_end_point.CompleteTask(nullptr, &request, &response);
//    // Assert
//    EXPECT_TRUE(actual_result.ok());
//    EXPECT_EQ(TaskManagerServiceResult::FAIL_UNCOMPLETED_SUBTASKS, response.result());
//}
//
//TEST_F(GRPCServerEndPointTests, AddTaskLabel_ShouldAskModelToAddTaskLabelAndReturnResult) {
//    // Arrange
//    const auto expected_model_result = TaskActionResult::SUCCESS;
//    EXPECT_CALL(*model_, AddTaskLabel(expected_task_id_, expected_label_)).WillOnce(Return(expected_model_result));
//    GRPCServerEndPoint server_end_point{std::move(model_)};
//    AddTaskLabelResponse response;
//    AddTaskLabelRequest request;
//    request.set_allocated_task_id(new TaskId(expected_task_id_));
//    request.set_label(expected_label_);
//    // Act
//    const auto actual_result = server_end_point.AddTaskLabel(nullptr, &request, &response);
//    // Assert
//    EXPECT_TRUE(actual_result.ok());
//    EXPECT_EQ(TaskManagerServiceResult::SUCCESS, response.result());
//}
//
//TEST_F(GRPCServerEndPointTests, RemoveTaskLabel_ShouldAskModelToRemoveTaskLabelAndReturnResult) {
//    // Arrange
//    const auto expected_model_result = TaskActionResult::FAIL_NO_SUCH_LABEL;
//    EXPECT_CALL(*model_, RemoveTaskLabel(expected_task_id_, expected_label_)).WillOnce(Return(expected_model_result));
//    GRPCServerEndPoint server_end_point{std::move(model_)};
//    RemoveTaskLabelResponse response;
//    RemoveTaskLabelRequest request;
//    request.set_allocated_task_id(new TaskId(expected_task_id_));
//    request.set_label(expected_label_);
//    // Act
//    const auto actual_result = server_end_point.RemoveTaskLabel(nullptr, &request, &response);
//    // Assert
//    EXPECT_TRUE(actual_result.ok());
//    EXPECT_EQ(TaskManagerServiceResult::FAIL_NO_SUCH_LABEL, response.result());
//}
//
//TEST_F(GRPCServerEndPointTests, GetTasks_ShouldGetTasksFromModelAndReturnThem) {
//    // Arrange
//    const std::vector<RelationalTask> expected_returned_tasks{expected_relational_task_, expected_relational_task_};
//    EXPECT_CALL(*model_, GetTasks()).WillOnce(Return(expected_returned_tasks));
//    GRPCServerEndPoint server_end_point{std::move(model_)};
//    GetTasksResponse response;
//    GetTasksRequest request;
//    // Act
//    const auto actual_result = server_end_point.GetTasks(nullptr, &request, &response);
//    const auto actual_returned_tasks = response.tasks();
//    // Assert
//    EXPECT_TRUE(actual_result.ok());
//    ASSERT_EQ(expected_returned_tasks.size(), actual_returned_tasks.size());
//    for (int i = 0; i < expected_returned_tasks.size(); ++i)
//        EXPECT_EQ(expected_returned_tasks[i], actual_returned_tasks[i]);
//}
//
//TEST_F(GRPCServerEndPointTests, GetTask_ShouldGetTaskFromModelAndReturnIt) {
//    // Arrange
//    EXPECT_CALL(*model_, GetTask(expected_task_id_)).WillOnce(Return(expected_relational_task_));
//    GRPCServerEndPoint server_end_point{std::move(model_)};
//    GetTaskResponse response;
//    GetTaskRequest request;
//    request.set_allocated_task_id(new TaskId(expected_task_id_));
//    // Act
//    const auto actual_result = server_end_point.GetTask(nullptr, &request, &response);
//    // Assert
//    EXPECT_TRUE(actual_result.ok());
//    ASSERT_TRUE(response.has_task());
//    EXPECT_EQ(expected_relational_task_, response.task());
//}
//
//TEST_F(GRPCServerEndPointTests, LoadTasks_ShouldGiveModelTasksToLoad) {
//    // Arrange
//    const std::vector<RelationalTask> expected_returned_tasks{expected_relational_task_, expected_relational_task_};
//    const bool expected_model_result = true;
//    EXPECT_CALL(*model_, LoadModelState(expected_returned_tasks)).WillOnce(Return(expected_model_result));
//    GRPCServerEndPoint server_end_point{std::move(model_)};
//    LoadTasksResponse response;
//    LoadTasksRequest request;
//    for (const auto& task: expected_returned_tasks) {
//        request.mutable_tasks()->AddAllocated(new RelationalTask(task));
//    }
//    // Act
//    const auto actual_result = server_end_point.LoadTasks(nullptr, &request, &response);
//    // Assert
//    EXPECT_TRUE(actual_result.ok());
//    EXPECT_EQ(expected_model_result, response.result());
//}