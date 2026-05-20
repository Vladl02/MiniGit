#include "commands/CommandParser.h"

#include "commands/AddCommand.h"
#include "commands/CatObjectCommand.h"
#include "commands/CheckoutCommand.h"
#include "commands/CommitCommand.h"
#include "commands/InitCommand.h"
#include "commands/LogCommand.h"
#include "commands/StatusCommand.h"

#include "exceptions/MiniGitException.h"

#include <iostream>
#include <string>

std::shared_ptr<ICommand> CommandParser::parse(int argc, char* argv[]) {
    if (argc < 2) {
        throw CommandLineException("Missing command");
    }

    const std::string command = argv[1];
    if (command == "init") {
        return std::make_shared<InitCommand>();
    }
    if (command == "add") {
        if (argc != 3) {
            throw CommandLineException("Usage: mgit add <file>");
        }
        return std::make_shared<AddCommand>(argv[2]);
    }
    if (command == "commit") {
        if (argc != 4 || std::string(argv[2]) != "-m") {
            throw CommandLineException("Usage: mgit commit -m \"message\"");
        }
        return std::make_shared<CommitCommand>(argv[3]);
    }
    if (command == "log") {
        return std::make_shared<LogCommand>();
    }
    if (command == "status") {
        return std::make_shared<StatusCommand>();
    }
    if (command == "cat-object") {
        if (argc != 3) {
            throw CommandLineException("Usage: mgit cat-object <hash>");
        }
        return std::make_shared<CatObjectCommand>(argv[2]);
    }
    if (command == "checkout") {
        if (argc != 3) {
            throw CommandLineException("Usage: mgit checkout <commit_hash>");
        }
        return std::make_shared<CheckoutCommand>(argv[2]);
    }

    throw CommandLineException("Unknown command: " + command);
}

void CommandParser::printUsage() {
    std::cout << "MiniGit commands:\n"
              << "  mgit init\n"
              << "  mgit add <file>\n"
              << "  mgit commit -m \"message\"\n"
              << "  mgit log\n"
              << "  mgit status\n"
              << "  mgit cat-object <hash>\n"
              << "  mgit checkout <commit_hash>\n";
}
