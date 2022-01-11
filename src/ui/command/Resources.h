#pragma once

#include <memory>
#include "model/TaskManager.h"
#include "persistence/TaskPersister.h"

namespace ui::command {
    struct Resources {
    public:
        explicit Resources(const std::shared_ptr<model::TaskManager>& i_manager,
                            const std::shared_ptr<TaskPersister>& i_persister) :
                manager{i_manager}, persister{i_persister} {}

        const std::shared_ptr<model::TaskManager> manager;
        const std::shared_ptr<TaskPersister> persister;
    };
}