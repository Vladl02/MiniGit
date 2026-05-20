#include "commands/AddCommand.h"

#include "Repository.h"

#include <iostream>
#include <utility>

AddCommand::AddCommand(std::string pathValue) : path(std::move(pathValue)) {}

void AddCommand::execute(Repository& repo) {

    if (path == "."){
        // identifies what files have any changes
        //
    }
    const std::string hash = repo.addFile(path);
    std::cout << "Added " << path << " as blob " << hash << '\n';
}
