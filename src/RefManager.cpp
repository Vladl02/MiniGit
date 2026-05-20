#include "RefManager.h"

#include "exceptions/MiniGitException.h"

#include <fstream>

RefManager::RefManager(std::filesystem::path miniGitPathValue) : miniGitPath(std::move(miniGitPathValue)) {}

void RefManager::initialize() const {
    std::filesystem::create_directories(miniGitPath / "refs" / "heads");
    {
        std::ofstream head(miniGitPath / "HEAD");
        if (!head) {
            throw StorageException("Cannot write HEAD");
        }
        head << "refs/heads/main\n";
    }
    {
        std::ofstream mainRef(miniGitPath / "refs" / "heads" / "main");
        if (!mainRef) {
            throw StorageException("Cannot write main ref");
        }
    }
}

std::optional<std::string> RefManager::headCommit() const {
    const auto mainPath = miniGitPath / "refs" / "heads" / "main";
    if (!std::filesystem::exists(mainPath)) {
        return std::nullopt;
    }
    std::ifstream in(mainPath);
    if (!in) {
        throw StorageException("Cannot read main ref");
    }
    std::string hash;
    std::getline(in, hash);
    if (hash.empty()) {
        return std::nullopt;
    }
    return hash;
}

void RefManager::updateHead(std::string commitHash) const {
    std::ofstream out(miniGitPath / "refs" / "heads" / "main");
    if (!out) {
        throw StorageException("Cannot update HEAD");
    }
    out << commitHash << '\n';
}
