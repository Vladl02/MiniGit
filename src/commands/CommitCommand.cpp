#include "commands/CommitCommand.h"

#include "Repository.h"

#include <iostream>
#include <utility>

CommitCommand::CommitCommand(std::string commitMessage) : message(std::move(commitMessage)) {}

void CommitCommand::execute(Repository& repo) {
    const std::string hash = repo.commit(message);
    std::cout << "Created commit " << hash << '\n';
}
