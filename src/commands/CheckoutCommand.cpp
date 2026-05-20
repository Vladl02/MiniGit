#include "commands/CheckoutCommand.h"

#include "Repository.h"

#include <iostream>
#include <utility>

CheckoutCommand::CheckoutCommand(std::string commitHashValue) : commitHash(std::move(commitHashValue)) {}

void CheckoutCommand::execute(Repository& repo) {
    repo.checkout(commitHash);
    std::cout << "Checked out commit " << commitHash << '\n';
}
