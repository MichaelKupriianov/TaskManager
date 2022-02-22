#pragma once

#include "TaskManager.h"
#include "persistence/TaskPersister.h"

namespace model {

/**
 * \brief Interface of core
 * \details Manages TaskManager and TaskPersister
 * \author Michael Kupriianov
 */
class Model {
public:
    /**
     * Constructor that creates an instance of the model
     * @param manager - pointer to task manager instance
     */
    explicit Model(const std::shared_ptr<model::TaskManager>& manager) :
            manager_{manager} {}
    /**
     * Virtual destructor for correct inheritance
     */
    virtual ~Model() = default;

    /**
     * Adds a new task
     * @param task - protobuf message containing the task to be added
     * @return bool - is addition successful
     */
    virtual bool AddTask(const Task& task);
    /**
     * Adds a new subtask with exiting parent
     * @param task - protobuf message containing the subtask to be added
     * @param id - protobuf message containing the id of parent
     * @return bool - is addition successful
     */
    virtual bool AddSubTask(const Task& task, const TaskId& id);
    /**
     * Edits existing task
     * @param id - protobuf message containing id of task to be edited
     * @param task - protobuf message containing new content of task
     * @return bool - is edition successful
     */
    virtual bool Edit(const TaskId& id, const Task& task);
    /**
     * Completes existing task
     * @param id - protobuf message containing id of task to be completed
     * @return bool - is completion successful
     * @warning All subtasks of this task will also be completed
     */
    virtual bool Complete(const TaskId& id);
    /**
     * Deletes existing task
     * @param id - protobuf message containing id of task to be deleted
     * @return bool - is deletion successful
     * @warning All subtasks of this task will also be deleted
     */
    virtual bool Delete(const TaskId& id);

    /**
     * Shows all tasks containing the given label
     * @param label - string with label
     * @param sort_by - enum which informs by what parameter sort requested tasks
     * @return ManyTasksWithId - protobuf message containing requesting tasks
     */
    virtual ManyTasksWithId ShowByLabel(const std::string& label, const TasksSortBy& sort_by);
    /**
     * Shows all tasks expect subtasks
     * @param sort_by - enum which informs by what parameter sort requested tasks
     * @return ManyTasksWithId - protobuf message containing requesting tasks
     */
    virtual ManyTasksWithId ShowParents(const TasksSortBy& sort_by);
    /**
     * Shows task with given id with ith subtasks
     * @param id - protobuf message containing id of task to be shown
     * @param sort_by - enum which informs by what parameter sort children of requesting task
     * @return CompositeTask - protobuf message containing requesting task
     */
    virtual CompositeTask ShowTask(const TaskId& id, const TasksSortBy& sort_by);
    /**
     * Shows all tasks with subtasks
     * @param sort_by - enum which informs by what parameter sort requested tasks
     * @return ManyCompositeTasks - protobuf message containing requesting tasks
     */
    virtual ManyCompositeTasks ShowAll(const TasksSortBy& sort_by);

    /**
     * Saves state of TaskManager to given file
     * @param filename - string with name of file
     * @return bool - is saving successful
     */
    virtual bool Save(const std::string& filename);
    /**
     * Loads state of TaskManager from existing file
     * @param filename - string with name of file
     * @return bool - is loading successful
     * @warning Current state of TaskManager will be completely erased
     */
    virtual bool Load(const std::string& filename);
private:
    const std::shared_ptr<TaskManager> manager_;
};
}

