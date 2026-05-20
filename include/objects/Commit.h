#pragma once

#include "objects/GitObject.h"

#include <optional>
#include <string>

class Commit final : public GitObject {
public:
    Commit(std::string treeHash,
           std::optional<std::string> parentHash,
           std::string author,
           std::string timestamp,
           std::string message);

    const std::string& treeHash() const;
    const std::optional<std::string>& parentHash() const;
    const std::string& author() const;
    const std::string& timestamp() const;
    const std::string& message() const;

    std::string type() const override;
    std::string serialize() const override;
    std::shared_ptr<GitObject> clone() const override;

    static Commit deserialize(const std::string& data);

private:
    std::string treeHashValue;
    std::optional<std::string> parentHashValue;
    std::string authorValue;
    std::string timestampValue;
    std::string messageValue;
};
