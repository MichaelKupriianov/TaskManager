#pragma once

#include <map>
#include <utility>
#include <memory>
#include <vector>
#include <optional>
#include "Task.pb.h"
#include "IdGenerator.h"
#include "TasksSortBy.h"
#include "utilities/ComparisonProtoObjects.h"
#include "utilities/CreateProtoObjects.h"
#include "utilities/AliasesProtoObjects.h"
#include "persistence/TaskPersister.h"

namespace model {
    class TaskManager {
    public:
        explicit TaskManager(const std::shared_ptr<IdGenerator>&);
        virtual ~TaskManager() = default;

        virtual bool AddTask(const proto::Task&);
        virtual bool AddSubTask(const proto::Task&, proto::TaskId);
        virtual bool Edit(proto::TaskId, const proto::Task&);
        virtual bool Complete(proto::TaskId);
        virtual bool Delete(proto::TaskId);

        virtual proto::ArraySimpleTasks ShowLabel(const std::string& label, TasksSortBy) const;
        virtual proto::ArraySimpleTasks ShowParents(TasksSortBy) const;
        virtual std::optional<proto::CompositeTask> ShowTask(proto::TaskId, TasksSortBy) const;
        virtual proto::ArrayCompositeTasks ShowAll(TasksSortBy) const;

        virtual proto::ArrayHierarchicalTasks GetAllTasks();
        virtual void Rewrite(const proto::ArrayHierarchicalTasks &);
    private:
        static bool ComparatorPriority(const std::unique_ptr<proto::SimpleTask>&,
                                       const std::unique_ptr<proto::SimpleTask>&);
        static bool ComparatorDate(const std::unique_ptr<proto::SimpleTask>&,
                                   const std::unique_ptr<proto::SimpleTask>&);
        static bool ComparatorId(const std::unique_ptr<proto::SimpleTask>&,
                                 const std::unique_ptr<proto::SimpleTask>&);
    private:
        std::map<proto::TaskId, proto::HierarchicalTask> tasks_;
        std::shared_ptr<IdGenerator> generator_;
    };
}