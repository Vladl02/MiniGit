#include "commands/CatObjectCommand.h"

#include "Repository.h"

#include <iostream>
#include <utility>

CatObjectCommand::CatObjectCommand(std::string objectHash) : hash(std::move(objectHash)) {}

void CatObjectCommand::execute(Repository& repo) {
    std::cout << repo.catObject(hash) << '\n';
}
