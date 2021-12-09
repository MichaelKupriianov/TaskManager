#pragma once

#include<string>
#include<ctime>
#include<memory>
#include<vector>
#include"Task.h"
#include"TaskId.h"
#include"TypeOfStep.h"
#include"TypeOfCommand.h"
#include"Reader.h"
#include"Printer.h"

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
public:
    using IdWithTask = std::pair<TaskId, Task>;
    using ArrayOfIdWithTask = std::vector<IdWithTask>;
public:
    virtual void PrintSomeTasks(const ArrayOfIdWithTask &, const std::string &);
    virtual void PrintAllTasks(
            const std::vector<std::pair<IdWithTask, ArrayOfIdWithTask>> &);
    virtual void PrintException(const std::string &exception);
private:
    void PrintTask(const std::pair<TaskId, Task> &);
private:
    const std::shared_ptr<Reader> reader_;
    const std::shared_ptr<Printer> printer_;
};
