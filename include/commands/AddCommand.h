#pragma once

#include "commands/ICommand.h"

#include <string>

class AddCommand final : public ICommand {
public:
    explicit AddCommand(std::string path);
    void execute(Repository& repo) override;

private:
    std::string path;
};
