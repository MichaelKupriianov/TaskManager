#pragma once

class Context {
public:
    bool if_finished() const { return if_finished_; }

    void Finished() { if_finished_ = true; }

private:
    bool if_finished_ = false;
};
