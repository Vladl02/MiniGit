#pragma once

#include "objects/GitObject.h"
#include "objects/TreeEntry.h"

#include <string>
#include <vector>

class Tree final : public GitObject {
public:
    explicit Tree(std::vector<TreeEntry> entries);

    const std::vector<TreeEntry>& entries() const;
    std::string type() const override;
    std::string serialize() const override;
    std::shared_ptr<GitObject> clone() const override;

    static Tree deserialize(const std::string& data);

private:
    std::vector<TreeEntry> entriesValue;
};
