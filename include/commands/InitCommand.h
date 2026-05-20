#pragma once

#include "commands/ICommand.h"

class InitCommand final : public ICommand {
public:
    void execute(Repository& repo) override;
};
