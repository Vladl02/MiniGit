#include "Repository.h"

#include "CommitBuilder.h"
#include "exceptions/MiniGitException.h"
#include "hashing/SimpleHashStrategy.h"
#include "utils/Templates.h"

#include <chrono>
#include <ctime>

Repository::Repository(std::filesystem::path root)
    : root(std::move(root)),
      miniGitPath(this->root / ".minigit"),
      database(miniGitPath / "objects", std::make_shared<SimpleHashStrategy>()),
      blobStore(database),
      treeStore(database),
      commitStore(database),
      index(miniGitPath / "index"),
      refs(miniGitPath),
      workingDirectory(this->root) {}

void Repository::init() {
    std::filesystem::create_directories(miniGitPath / "objects");
    refs.initialize();
    index.clear();
}

void Repository::ensureInitialized() const {
    if (!std::filesystem::exists(miniGitPath) || !std::filesystem::is_directory(miniGitPath)) {
        throw RepositoryException("Repository not initialized. Run 'mgit init' first.");
    }
}

std::string Repository::addFile(const std::string& path) {
    ensureInitialized();
    const Blob blob(workingDirectory.readFile(path));
    const std::string blobHash = blobStore.add(blob);
    index.addOrUpdate(path, blobHash);
    return blobHash;
}

std::string Repository::commit(const std::string& message) {
    ensureInitialized();
    requireNotEmpty(message, "Commit message");

    const auto stagedEntries = index.entries();
    requireNotEmpty(stagedEntries, "Tree entries");

    const Tree tree(stagedEntries);
    const std::string treeHash = treeStore.add(tree);

    const Commit commitObject = CommitBuilder()
        .setTreeHash(treeHash)
        .setParentHash(refs.headCommit())
        .setAuthor("MiniGit User")
        .setTimestamp(currentTimestamp())
        .setMessage(message)
        .build();

    const std::string commitHash = commitStore.add(commitObject);
    refs.updateHead(commitHash);
    index.clear();
    return commitHash;
}

std::vector<CommitLogEntry> Repository::log() const {
    ensureInitialized();
    std::vector<CommitLogEntry> result;
    auto current = refs.headCommit();
    while (current) {
        Commit commitObject = commitStore.get(*current);
        const std::string currentHash = *current;
        current = commitObject.parentHash();
        result.push_back(CommitLogEntry{currentHash, std::move(commitObject)});
    }
    return result;
}

std::vector<TreeEntry> Repository::status() const {
    ensureInitialized();
    return index.entries();
}

std::string Repository::catObject(const std::string& hash) const {
    ensureInitialized();
    return database.loadRaw(hash);
}

void Repository::checkout(const std::string& commitHash) const {
    ensureInitialized();
    const Commit commitObject = commitStore.get(commitHash);
    const Tree tree = treeStore.get(commitObject.treeHash());
    workingDirectory.writeTree(tree, blobStore);
}

std::string Repository::currentTimestamp() const {
    const auto now = std::chrono::system_clock::now();
    const std::time_t time = std::chrono::system_clock::to_time_t(now);
    return std::to_string(static_cast<long long>(time));
}
