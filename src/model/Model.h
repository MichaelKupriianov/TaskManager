#include "TaskManager.h"
#include "persistence/TaskPersister.h"

namespace model {
class Model {
public:
    Model(const std::shared_ptr<model::TaskManager>& manager) :
            manager_{manager} {}
    virtual ~Model() = default;

    virtual bool AddTask(const model::Task& task);
    virtual bool AddSubTask(const model::Task& task, model::TaskId id);
    virtual bool Edit(model::TaskId id, const model::Task& task);
    virtual bool Complete(model::TaskId id);
    virtual bool Delete(model::TaskId id);

    virtual model::ManyTasksWithId ShowByLabel(const std::string& label, model::TasksSortBy);
    virtual model::ManyTasksWithId ShowParents(model::TasksSortBy);
    virtual model::CompositeTask ShowTask(model::TaskId id, model::TasksSortBy);
    virtual model::ManyCompositeTasks ShowAll(model::TasksSortBy);

    virtual bool Save(const std::string& filename);
    virtual bool Load(const std::string& filename);
private:
    const std::shared_ptr<TaskManager> manager_;
};
}
