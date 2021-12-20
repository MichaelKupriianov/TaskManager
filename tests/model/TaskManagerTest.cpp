#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"TaskManager.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;

class IdGeneratorMock : public IdGenerator {
public:
    MOCK_METHOD(TaskId, GenerateId, (), (override));
};

class PersisterMock : public Persister {
public:
    MOCK_METHOD(bool, Save, (const Tasks &, const std::string &), (override));
    MOCK_METHOD(std::optional<Tasks>, Load, (const std::string &), (override));
};

class TaskManagerTest : public ::testing::Test {
public:
    void SetUp() override {
        generator_ = std::make_shared<IdGeneratorMock>();
        persister_ = std::make_shared<PersisterMock>();
        manager_ = std::make_shared<TaskManager>(generator_, persister_);
    }

    static Task CreateTask(const std::string &title) {
        Task task;
        task.set_title(title);
        return task;
    }

    static Task CreateTask(Task_Priority priority) {
        Task task;
        task.set_priority(priority);
        return task;
    }

    static Task CreateTask(time_t date) {
        Task task;
        google::protobuf::Timestamp time;
        time.set_seconds(date);
        task.set_allocated_date(new google::protobuf::Timestamp(time));
        return task;
    }

    static TaskId CreateId(int value) {
        TaskId id;
        id.set_value(value);
        return id;
    }

protected:
    std::shared_ptr<IdGeneratorMock> generator_;
    std::shared_ptr<PersisterMock> persister_;
    std::shared_ptr<TaskManager> manager_;
};

TEST_F(TaskManagerTest, shouldAddTask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(CreateId(0)))
            .WillOnce(Return(CreateId(1)));

    EXPECT_TRUE(manager_->AddTask(CreateTask("first")));
    EXPECT_EQ(manager_->ShowTask(CreateId(0), SortBy::ID).value().first.second,
              CreateTask("first"));
    EXPECT_TRUE(manager_->AddTask(CreateTask("second")));
    EXPECT_EQ(manager_->ShowTask(CreateId(1), SortBy::ID).value().first.second,
              CreateTask("second"));
}

TEST_F(TaskManagerTest, shouldReturnFalseIfIdGeneratorWorksdBadly) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(CreateId(0)))
            .WillOnce(Return(CreateId(0)));

    EXPECT_TRUE(manager_->AddTask(CreateTask("first")));
    EXPECT_FALSE(manager_->AddTask(CreateTask("first")));
}

TEST_F(TaskManagerTest, shouldAddSubTask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(CreateId(0)))
            .WillOnce(Return(CreateId(1)));

    EXPECT_TRUE(manager_->AddTask(CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(CreateTask("second"), CreateId(0)));
    EXPECT_EQ(manager_->ShowTask(CreateId(1), SortBy::ID).value().first.second,
              CreateTask("second"));
}

TEST_F(TaskManagerTest, shouldReturnFalseIfParentsIdIsIncorrect) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(CreateId(0)));

    EXPECT_TRUE(manager_->AddTask(CreateTask("first")));
    EXPECT_FALSE(manager_->AddSubTask(CreateTask("second"), CreateId(3)));
}

TEST_F(TaskManagerTest, shouldReturnFalseIfAddSubtaskToSubtask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(CreateId(0)))
            .WillOnce(Return(CreateId(1)));

    EXPECT_TRUE(manager_->AddTask(CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(CreateTask("second"), CreateId(0)));
    EXPECT_FALSE(manager_->AddSubTask(CreateTask("third"), CreateId(1)));
}

TEST_F(TaskManagerTest, shouldReturnFalseIfAddSubtaskToCompletedTask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(CreateId(0)));

    EXPECT_TRUE(manager_->AddTask(CreateTask("first")));
    EXPECT_TRUE(manager_->Complete(CreateId(0)));
    EXPECT_FALSE(manager_->AddSubTask(CreateTask("second"), CreateId(0)));
}

TEST_F(TaskManagerTest, shouldEditTask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(CreateId(0)))
            .WillOnce(Return(CreateId(1)));

    EXPECT_TRUE(manager_->AddTask(CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(CreateTask("second"), CreateId(0)));
    EXPECT_TRUE(manager_->Edit(CreateId(0), CreateTask("third")));
    EXPECT_TRUE(manager_->Edit(CreateId(1), CreateTask("fourth")));
    EXPECT_EQ(manager_->ShowTask(CreateId(0), SortBy::ID).value().first.second,
              CreateTask("third"));
    EXPECT_EQ(manager_->ShowTask(CreateId(1), SortBy::ID).value().first.second,
              CreateTask("fourth"));
}

TEST_F(TaskManagerTest, shouldReturnFalseWhenEditIfIDNotExist) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(CreateId(0)));

    EXPECT_TRUE(manager_->AddTask(CreateTask("first")));
    EXPECT_FALSE(manager_->Edit(CreateId(1), CreateTask("second")));
}

TEST_F(TaskManagerTest, shouldCompleteTask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(CreateId(0)))
            .WillOnce(Return(CreateId(1)));

    EXPECT_TRUE(manager_->AddTask(CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(CreateTask("second"), CreateId(0)));
    EXPECT_TRUE(manager_->Complete(CreateId(0)));
    EXPECT_EQ(manager_->ShowAll(SortBy::ID).size(), 0);
}

TEST_F(TaskManagerTest, shouldReturnFalseWhenCompleteIfIDNotExist) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(CreateId(0)));

    EXPECT_TRUE(manager_->AddTask(CreateTask("first")));
    EXPECT_FALSE(manager_->Complete(CreateId(1)));
}

TEST_F(TaskManagerTest, shouldDeleteTask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(CreateId(0)))
            .WillOnce(Return(CreateId(1)));

    EXPECT_TRUE(manager_->AddTask(CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(CreateTask("second"), CreateId(0)));
    EXPECT_TRUE(manager_->Delete(CreateId(0)));
    EXPECT_EQ(manager_->ShowAll(SortBy::ID).size(), 0);
}

TEST_F(TaskManagerTest, shouldReturnFalseWhenDeleteIfIDNotExist) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(CreateId(0)));

    EXPECT_TRUE(manager_->AddTask(CreateTask("first")));
    EXPECT_FALSE(manager_->Delete(CreateId(1)));
}

TEST_F(TaskManagerTest, shouldSortById) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(3)
            .WillOnce(Return(CreateId(0)))
            .WillOnce(Return(CreateId(1)))
            .WillOnce(Return(CreateId(2)));

    EXPECT_TRUE(manager_->AddTask(CreateTask("first")));
    EXPECT_TRUE(manager_->AddTask(CreateTask("second")));
    EXPECT_TRUE(manager_->AddTask(CreateTask("third")));
    EXPECT_EQ(manager_->ShowParents(SortBy::ID)[0].second, CreateTask("first"));
    EXPECT_EQ(manager_->ShowParents(SortBy::ID)[1].second, CreateTask("second"));
    EXPECT_EQ(manager_->ShowParents(SortBy::ID)[2].second, CreateTask("third"));
}

TEST_F(TaskManagerTest, shouldSortByPriority) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(3)
            .WillOnce(Return(CreateId(0)))
            .WillOnce(Return(CreateId(1)))
            .WillOnce(Return(CreateId(2)));

    EXPECT_TRUE(manager_->AddTask(CreateTask(Task_Priority_LOW)));
    EXPECT_TRUE(manager_->AddTask(CreateTask(Task_Priority_NONE)));
    EXPECT_TRUE(manager_->AddTask(CreateTask(Task_Priority_HIGH)));
    EXPECT_EQ(manager_->ShowParents(SortBy::PRIORITY)[0].second,
              CreateTask(Task_Priority_HIGH));
    EXPECT_EQ(manager_->ShowParents(SortBy::PRIORITY)[1].second,
              CreateTask(Task_Priority_LOW));
    EXPECT_EQ(manager_->ShowParents(SortBy::PRIORITY)[2].second,
              CreateTask(Task_Priority_NONE));
}

TEST_F(TaskManagerTest, shouldSortByDate) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(3)
            .WillOnce(Return(CreateId(0)))
            .WillOnce(Return(CreateId(1)))
            .WillOnce(Return(CreateId(2)));

    EXPECT_TRUE(manager_->AddTask(CreateTask(100)));
    EXPECT_TRUE(manager_->AddTask(CreateTask(300)));
    EXPECT_TRUE(manager_->AddTask(CreateTask(200)));
    EXPECT_EQ(manager_->ShowParents(SortBy::DATE)[0].second, CreateTask(100));
    EXPECT_EQ(manager_->ShowParents(SortBy::DATE)[1].second, CreateTask(200));
    EXPECT_EQ(manager_->ShowParents(SortBy::DATE)[2].second, CreateTask(300));
}

TEST_F(TaskManagerTest, shouldShowTaskWithSubtasks) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(3)
            .WillOnce(Return(CreateId(0)))
            .WillOnce(Return(CreateId(1)))
            .WillOnce(Return(CreateId(2)));

    EXPECT_TRUE(manager_->AddTask(CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(CreateTask("second"), CreateId(0)));
    EXPECT_TRUE(manager_->AddSubTask(CreateTask("third"), CreateId(0)));

    std::optional<TaskManager::TaskWithSubtasks> task =
            manager_->ShowTask(CreateId(0), SortBy::ID);
    ASSERT_TRUE(task.has_value());
    EXPECT_EQ(task.value().first.second, CreateTask("first"));
    EXPECT_EQ(task.value().second[0].second, CreateTask("second"));
    EXPECT_EQ(task.value().second[1].second, CreateTask("third"));
}

TEST_F(TaskManagerTest, shouldReturnNullptrIfIDNotExist) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(CreateId(0)));

    EXPECT_TRUE(manager_->AddTask(CreateTask("first")));
    std::optional<TaskManager::TaskWithSubtasks> task =
            manager_->ShowTask(CreateId(1), SortBy::ID);
    ASSERT_FALSE(task.has_value());
}

TEST_F(TaskManagerTest, shouldShowAll) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(4)
            .WillOnce(Return(CreateId(0)))
            .WillOnce(Return(CreateId(1)))
            .WillOnce(Return(CreateId(2)))
            .WillOnce(Return(CreateId(3)));

    EXPECT_TRUE(manager_->AddTask(CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(CreateTask("second"), CreateId(0)));
    EXPECT_TRUE(manager_->AddTask(CreateTask("third")));
    EXPECT_TRUE(manager_->AddSubTask(CreateTask("fourth"), CreateId(2)));

    std::vector<TaskManager::TaskWithSubtasks> task =
            manager_->ShowAll(SortBy::ID);
    EXPECT_EQ(task[0].first.second, CreateTask("first"));
    EXPECT_EQ(task[0].second[0].second, CreateTask("second"));
    EXPECT_EQ(task[1].first.second, CreateTask("third"));
    EXPECT_EQ(task[1].second[0].second, CreateTask("fourth"));
}

TEST_F(TaskManagerTest, shouldSaveTasks) {
    EXPECT_CALL(*persister_, Save(_, "file"))
            .Times(1)
            .WillOnce(Return(true));

    manager_->AddTask(CreateTask("first"));
    EXPECT_TRUE(manager_->Save("file"));
}

TEST_F(TaskManagerTest, shouldRerurnFalseIfCantSaveTasks) {
    EXPECT_CALL(*persister_, Save(_, "file"))
            .Times(1)
            .WillOnce(Return(false));

    EXPECT_FALSE(manager_->Save("file"));
}

TEST_F(TaskManagerTest, shouldLoadTasks) {
    GeneralizedTask task;
    task.set_allocated_parent(new TaskId);
    task.set_allocated_task(new Task);
    std::pair<TaskId, GeneralizedTask> gen_task{CreateId(0), task};
    Persister::Tasks result;
    result.push_back(gen_task);

    EXPECT_CALL(*persister_, Load("file"))
            .Times(1)
            .WillOnce(Return(result));

    EXPECT_TRUE(manager_->Load("file"));
}

TEST_F(TaskManagerTest, shouldRerurnFalseIfCantLoadTasks) {
    EXPECT_CALL(*persister_, Load("file"))
            .Times(1)
            .WillOnce(Return(std::nullopt));

    EXPECT_FALSE(manager_->Load("file"));
}