#pragma once

#include <memory>
#include "ui/Context.h"
#include "Type.h"

namespace ui::step {
    class Resources;

    class Step {
    public:
        virtual std::shared_ptr<Step> execute(Context&, const std::shared_ptr<Resources>&) = 0;
        virtual ~Step() = default;
    };

    class Root : public Step {
    public:
        std::shared_ptr<Step> execute(Context&, const std::shared_ptr<Resources>&) override;
        ~Root() override  = default;
    };

    class Quit : public Step {
    public:
        std::shared_ptr<Step> execute(Context&, const std::shared_ptr<Resources>&) override;
        ~Quit() override = default;
    };

    class Help : public Step {
    public:
        std::shared_ptr<Step> execute(Context&, const std::shared_ptr<Resources>&) override;
        ~Help() override = default;
    };

    class Print : public Step {
    public:
        std::shared_ptr<Step> execute(Context&, const std::shared_ptr<Resources>&) override;
        ~Print() override  = default;
    };

    class Complete : public Step {
    public:
        Complete();
        std::shared_ptr<Step> execute(Context&, const std::shared_ptr<Resources>&) override;
        ~Complete() override = default;
    private:
        const Type type_;
    };

    class Delete : public Step {
    public:
        Delete();
        std::shared_ptr<Step> execute(Context&, const std::shared_ptr<Resources>&) override;
        ~Delete() override = default;
    private:
        const Type type_;
    };

    class Save : public Step {
    public:
        Save();
        std::shared_ptr<Step> execute(Context&, const std::shared_ptr<Resources>&) override;
        ~Save() override = default;
    private:
        const Type type_;
    };

    class Load : public Step {
    public:
        Load();
        std::shared_ptr<Step> execute(Context&, const std::shared_ptr<Resources>&) override;
        ~Load() override = default;
    private:
        const Type type_;
    };
}