#pragma once

#include "objects/TreeEntry.h"

#include <filesystem>
#include <string>
#include <vector>

class Index {
public:
    explicit Index(std::filesystem::path indexPath);

    void addOrUpdate(std::string path, std::string blobHash) const;
    std::vector<TreeEntry> entries() const;
    void clear() const;

private:
    std::filesystem::path indexPath;
};
