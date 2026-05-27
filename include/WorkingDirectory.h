#pragma once

#include "objects/Tree.h"

#include <filesystem>
#include <string>

class Blob;
template <typename TObject>
class ObjectStore;

class WorkingDirectory {
public:
    explicit WorkingDirectory(std::filesystem::path root);

    std::string readFile(const std::string& relativePath) const;
    void writeTree(const Tree& tree, ObjectStore<Blob>& blobs) const;

private:
    void clearFiles() const;
    std::filesystem::path resolve(const std::string& relativePath) const;

    std::filesystem::path root;
};
