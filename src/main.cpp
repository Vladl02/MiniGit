#include "Repository.h"
#include "commands/CommandParser.h"

#include <exception>
#include <filesystem>
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        auto command = CommandParser::parse(argc, argv);
        Repository repo(std::filesystem::current_path());
        command->execute(repo);
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        CommandParser::printUsage();
        return 1;
    }
}
