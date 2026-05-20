#pragma once

#include "commands/ICommand.h"

#include <string>

class CheckoutCommand final : public ICommand {
public:
    explicit CheckoutCommand(std::string commitHash);
    void execute(Repository& repo) override;

private:
    std::string commitHash;
};
