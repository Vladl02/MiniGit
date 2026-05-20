#pragma once

#include "commands/ICommand.h"

#include <string>

class CatObjectCommand final : public ICommand {
public:
    explicit CatObjectCommand(std::string hash);
    void execute(Repository& repo) override;

private:
    std::string hash;
};
