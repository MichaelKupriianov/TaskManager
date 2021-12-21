#pragma once

#include <string>
#include <ctime>
#include <memory>
#include <vector>
#include <optional>
#include "Task.pb.h"
#include "step/TypeOfStep.h"
#include "api/TasksSortBy.h"
#include "Reader.h"
#include "Printer.h"
#include "Convert.h"

class View {
public:
    View(const std::shared_ptr<Reader> &, const std::shared_ptr<Printer> &);
    virtual ~View() = default;
public:
    virtual void PrintHelp();
    virtual void PrintQuit();
    virtual TypeOfStep ReadCommand();
    virtual TaskId ReadId(TypeOfStep);
    virtual TaskId ReadParentId(TypeOfStep);
    virtual std::string ReadTitle(TypeOfStep);
    virtual Task::Priority ReadPriority(TypeOfStep);
    virtual google::protobuf::Timestamp ReadDate(TypeOfStep);
    virtual std::string ReadLabel(TypeOfStep);
    virtual bool Confirm();
    virtual bool ReadIfPrintSubtasks(TypeOfStep);
    virtual TasksSortBy ReadSortBy(TypeOfStep);
    virtual std::string ReadFilename(TypeOfStep);
public:
    using IdWithTask = std::pair<TaskId, Task>;
    using ArrayTasks = std::vector<IdWithTask>;
    using TaskWithSubtasks = std::pair<IdWithTask, ArrayTasks>;
public:
    virtual void PrintArrayOfTasks(const ArrayTasks &);
    virtual void PrintTaskWithSubtasks(const TaskWithSubtasks &);
    virtual void PrintAllTasks(
            const std::vector<TaskWithSubtasks> &);
    virtual void PrintException(const std::string &exception);
private:
    const std::shared_ptr<Reader> reader_;
    const std::shared_ptr<Printer> printer_;
};
