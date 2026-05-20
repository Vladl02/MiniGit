#pragma once

#include "commands/ICommand.h"

class StatusCommand final : public ICommand {
public:
    void execute(Repository& repo) override;
};
