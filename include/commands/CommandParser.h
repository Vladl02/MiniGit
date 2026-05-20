#pragma once

#include "commands/ICommand.h"

#include <memory>

class CommandParser {
public:
    static std::shared_ptr<ICommand> parse(int argc, char* argv[]);
    static void printUsage();
};
