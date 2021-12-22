#pragma once

#include<memory>
#include"model/TaskManager.h"
#include"persistence/TaskPersister.h"

namespace ui::command {

    struct Dependency {
    public:
        explicit Dependency(const std::shared_ptr<model::TaskManager>& i_manager,
                            const std::shared_ptr<persistence::TaskPersister>& i_persister) :
                manager{i_manager}, persister{i_persister} {}

        const std::shared_ptr<model::TaskManager> manager;
        const std::shared_ptr<persistence::TaskPersister> persister;
    };
}