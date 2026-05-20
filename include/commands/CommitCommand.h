#pragma once

#include "commands/ICommand.h"

#include <string>

class CommitCommand final : public ICommand {
public:
    explicit CommitCommand(std::string message);
    void execute(Repository& repo) override;

private:
    std::string message;
};
