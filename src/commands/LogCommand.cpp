#include "commands/LogCommand.h"

#include "Repository.h"

#include <iostream>

void LogCommand::execute(Repository& repo) {
    const auto commits = repo.log();
    if (commits.empty()) {
        std::cout << "No commits yet\n";
        return;
    }

    for (const auto& entry : commits) {
        const auto& commit = entry.commit;
        std::cout << "commit " << entry.hash << '\n';
        std::cout << "Tree:   " << commit.treeHash() << '\n';
        std::cout << "Author: " << commit.author() << '\n';
        std::cout << "Date:   " << commit.timestamp() << '\n';
        if (commit.parentHash()) {
            std::cout << "Parent: " << *commit.parentHash() << '\n';
        }
        std::cout << "\n    " << commit.message() << "\n\n";
    }
}
