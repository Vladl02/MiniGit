#include "commands/InitCommand.h"

#include "Repository.h"

#include <iostream>

void InitCommand::execute(Repository& repo) {
    repo.init();
    std::cout << "Initialized empty MiniGit repository in .minigit\n";
}
