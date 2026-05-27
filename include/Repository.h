#pragma once

#include "Index.h"
#include "RefManager.h"
#include "WorkingDirectory.h"
#include "objects/Blob.h"
#include "objects/Commit.h"
#include "objects/Tree.h"
#include "storage/ObjectDatabase.h"
#include "storage/ObjectStore.h"

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

struct CommitLogEntry {
    std::string hash;
    Commit commit;
};

class Repository {
public:
    explicit Repository(std::filesystem::path root);

    void init();
    void ensureInitialized() const;
    std::string addFile(const std::string& path);
    std::string commit(const std::string& message);
    std::vector<CommitLogEntry> log();
    std::vector<TreeEntry> status() const;
    std::string catObject(const std::string& hash) const;
    void checkout(const std::string& commitHash);

private:
    std::string currentTimestamp() const;

    std::filesystem::path root;
    std::filesystem::path miniGitPath;
    ObjectDatabase database;
    ObjectStore<Blob> blobStore;
    ObjectStore<Tree> treeStore;
    ObjectStore<Commit> commitStore;
    Index index;
    RefManager refs;
    WorkingDirectory workingDirectory;
};
