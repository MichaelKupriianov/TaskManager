#pragma once

#include<string>
#include<ctime>
#include<memory>
#include<vector>
#include<optional>
#include"Task.h"
#include"TaskId.h"
#include"TypeOfStep.h"
#include"TypeOfCommand.h"
#include"SortBy.h"
#include"Reader.h"
#include"Printer.h"
#include"Converter.h"

class View {
public:
    View(const std::shared_ptr<Reader> &, const std::shared_ptr<Printer> &);
    virtual ~View() = default;
public:
    virtual void Help();
    virtual void Quit();
    virtual TypeOfStep ReadCommand();
    virtual TaskId ReadId(TypeOfCommand);
    virtual TaskId ReadParentId(TypeOfCommand);
    virtual std::string ReadTitle(TypeOfCommand);
    virtual Task::Priority ReadPriority(TypeOfCommand);
    virtual time_t ReadDate(TypeOfCommand);
    virtual std::string ReadLabel(TypeOfCommand);
    virtual bool Confirm();
    virtual bool ReadIfPrintSubtasks(TypeOfCommand);
    virtual SortBy ReadSortBy(TypeOfCommand);
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
