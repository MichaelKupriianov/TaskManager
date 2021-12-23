#pragma once

#include <map>
#include <utility>
#include <memory>
#include <vector>
#include <optional>
#include "Task.pb.h"
#include "IdGenerator.h"
#include "api/TasksSortBy.h"
#include "api/ComparisonProtoObjects.h"
#include "api/CreateProtoObjects.h"
#include "api/AliasesProtoObjects.h"
#include "persistence/TaskPersister.h"

namespace model {
    class TaskManager {
    public:
        explicit TaskManager(const std::shared_ptr<IdGenerator>&);
        virtual ~TaskManager() = default;

        virtual bool AddTask(const api::Task&);
        virtual bool AddSubTask(const api::Task&, api::TaskId);
        virtual bool Edit(api::TaskId, const api::Task&);
        virtual bool Complete(api::TaskId);
        virtual bool Delete(api::TaskId);

        virtual api::ArrayTasks ShowLabel(const std::string& label, api::TasksSortBy) const;
        virtual api::ArrayTasks ShowParents(api::TasksSortBy) const;
        virtual std::optional<api::TaskWithSubtasks> ShowTask(api::TaskId, api::TasksSortBy) const;
        virtual api::AllTasks ShowAll(api::TasksSortBy) const;

        virtual api::ArrayFamilyTasks Save();
        virtual void Load(const api::ArrayFamilyTasks&);
    private:
        static bool ComparatorPriority(const std::unique_ptr<api::IdWithTask>&,
                                       const std::unique_ptr<api::IdWithTask>&);
        static bool ComparatorDate(const std::unique_ptr<api::IdWithTask>&,
                                   const std::unique_ptr<api::IdWithTask>&);
        static bool ComparatorId(const std::unique_ptr<api::IdWithTask>&,
                                 const std::unique_ptr<api::IdWithTask>&);
    private:
        std::map<api::TaskId, api::FamilyTask> tasks_;
        std::shared_ptr<IdGenerator> generator_;
    };
}