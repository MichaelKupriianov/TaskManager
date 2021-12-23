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
#include "api/TasksSortBy.h"
#include "api/AliasesProtoObjects.h"

namespace ui {
    class View {
    public:
        View(const std::shared_ptr<Reader>&, const std::shared_ptr<Printer>&);
        virtual ~View() = default;
    public:
        virtual void PrintHelp();
        virtual void PrintQuit();
        virtual step::Type ReadCommand();
        virtual api::TaskId ReadId(step::Type);
        virtual api::TaskId ReadParentId(step::Type);
        virtual std::string ReadTitle(step::Type);
        virtual api::Task::Priority ReadPriority(step::Type);
        virtual google::protobuf::Timestamp ReadDate(step::Type);
        virtual std::string ReadLabel(step::Type);
        virtual bool Confirm();
        virtual bool ReadIfPrintSubtasks(step::Type);
        virtual api::TasksSortBy ReadSortBy(step::Type);
        virtual std::string ReadFilename(step::Type);

        virtual void PrintArrayOfTasks(const api::ArrayTasks&);
        virtual void PrintTaskWithSubtasks(const api::TaskWithSubtasks&);
        virtual void PrintAllTasks(const api::AllTasks&);
        virtual void PrintException(const std::string& exception);
    private:
        const std::shared_ptr<Reader> reader_;
        const std::shared_ptr<Printer> printer_;
    };
}
