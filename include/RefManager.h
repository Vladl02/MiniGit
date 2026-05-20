#pragma once

#include <filesystem>
#include <optional>
#include <string>

class RefManager {
public:
    explicit RefManager(std::filesystem::path miniGitPath);

    void initialize() const;
    std::optional<std::string> headCommit() const;
    void updateHead(std::string commitHash) const;

private:
    std::filesystem::path miniGitPath;
};
