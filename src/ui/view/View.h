#pragma once

#include <string>
#include <ctime>
#include <memory>
#include <vector>
#include <optional>
#include "Reader.h"
#include "Printer.h"
#include "Convert.h"
#include "Task.pb.h"
#include "ui/step/Type.h"
#include "ui/command/Error.h"
#include "model/TasksSortBy.h"
#include "utilities/AliasesProtoObjects.h"

namespace ui {
    class View {
    public:
        View(const std::shared_ptr<Reader>&, const std::shared_ptr<Printer>&);
        virtual ~View() = default;
    public:
        virtual void PrintHelp();
        virtual void PrintQuit();
        virtual step::Type ReadCommand();
        virtual proto::TaskId ReadId(step::Type);
        virtual proto::TaskId ReadParentId(step::Type);
        virtual std::string ReadTitle(step::Type);
        virtual proto::Task::Priority ReadPriority(step::Type);
        virtual google::protobuf::Timestamp ReadDate(step::Type);
        virtual std::string ReadLabel(step::Type);
        virtual bool Confirm();
        virtual bool ReadIfPrintSubtasks(step::Type);
        virtual model::TasksSortBy ReadSortBy(step::Type);
        virtual std::string ReadFilename(step::Type);

        virtual void PrintArrayOfTasks(const proto::ArraySimpleTasks&);
        virtual void PrintTaskWithSubtasks(const proto::CompositeTask&);
        virtual void PrintAllTasks(const proto::ArrayCompositeTasks&);
        virtual void PrintError(command::Error);
    private:
        const std::shared_ptr<Reader> reader_;
        const std::shared_ptr<Printer> printer_;
    };
}
