#pragma once

#include "objects/Commit.h"

#include <optional>
#include <string>

class CommitBuilder {
public:
    CommitBuilder& setTreeHash(std::string treeHash);
    CommitBuilder& setParentHash(std::optional<std::string> parentHash);
    CommitBuilder& setAuthor(std::string author);
    CommitBuilder& setTimestamp(std::string timestamp);
    CommitBuilder& setMessage(std::string message);

    Commit build() const;

private:
    std::string treeHashValue;
    std::optional<std::string> parentHashValue;
    std::string authorValue;
    std::string timestampValue;
    std::string messageValue;
};
