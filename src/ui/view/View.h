#pragma once

#include <string>
#include <ctime>
#include <memory>
#include <vector>
#include <optional>
#include "Reader.h"
#include "Printer.h"
#include "utilities/Convert.h"
#include "Task.pb.h"
#include "TaskStructures.pb.h"
#include "ui/step/Type.h"
#include "ui/command/Error.h"

namespace ui {
class View {
public:
    View(const std::shared_ptr<Reader>&, const std::shared_ptr<Printer>&);
    virtual ~View() = default;
public:
    virtual void PrintHelp();
    virtual void PrintQuit();
    virtual step::Type ReadCommand();
    virtual TaskId ReadId(const std::string& command);
    virtual TaskId ReadParentId(const std::string& command);
    virtual std::string ReadTitle(const std::string& command);
    virtual Task::Priority ReadPriority(const std::string& command);
    virtual google::protobuf::Timestamp ReadDate(const std::string& command);
    virtual std::vector<std::string> ReadLabels(const std::string& command);
    virtual bool Confirm();
    virtual bool ReadIfPrintSubtasks(const std::string& command);
    virtual std::string ReadLabel(const std::string& command);
    virtual TasksSortBy ReadSortBy(const std::string& command);
    virtual std::string ReadFilename(const std::string& command);

    virtual void PrintManyTasksWithId(const ManyTasksWithId&);
    virtual void PrintCompositeTask(const CompositeTask&);
    virtual void PrintManyCompositeTasks(const ManyCompositeTasks&);
    virtual void PrintError(const command::Error&);
private:
    const std::shared_ptr<Reader> reader_;
    const std::shared_ptr<Printer> printer_;
};
}
