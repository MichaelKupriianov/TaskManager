#pragma once

#include "Controller.h"
#include "model/Model.h"

namespace ui {
class DefaultController : public Controller {
public:
    DefaultController(const std::shared_ptr<model::Model>& model) : model_{model} {}
    ~DefaultController() override = default;

    bool AddTask(const model::Task& task) override { return model_->AddTask(task); }
    bool AddSubTask(const model::Task& task, const model::TaskId& id) override { return model_->AddSubTask(task, id); }
    bool Edit(const model::TaskId& id, const model::Task& task) override { return model_->Edit(id, task); }
    bool Complete(const model::TaskId& id) override { return model_->Complete(id); }
    bool Delete(const model::TaskId& id) override { return model_->Delete(id); }

    model::ManyTasksWithId ShowByLabel(const std::string& label, const model::TasksSortBy& sort_by) override {
        return model_->ShowByLabel(label, sort_by);
    }
    model::ManyTasksWithId ShowParents(const model::TasksSortBy& sort_by) override {
        return model_->ShowParents(sort_by);
    }
    model::CompositeTask ShowTask(const model::TaskId& id, const model::TasksSortBy& sort_by) override {
        return model_->ShowTask(id, sort_by);
    }
    model::ManyCompositeTasks ShowAll(const model::TasksSortBy& sort_by) override {
        return model_->ShowAll(sort_by);
    }

    bool Save(const std::string& filename) override { return model_->Save(filename); }
    bool Load(const std::string& filename) override { return model_->Load(filename); }
private:
    const std::shared_ptr<model::Model> model_;
};
}
