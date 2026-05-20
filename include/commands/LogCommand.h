#pragma once

#include "commands/ICommand.h"

class LogCommand final : public ICommand {
public:
    void execute(Repository& repo) override;
};
