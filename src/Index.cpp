#include "Index.h"

#include "exceptions/MiniGitException.h"

#include <fstream>

Index::Index(std::filesystem::path indexPathValue) : indexPath(std::move(indexPathValue)) {}

void Index::addOrUpdate(std::string path, std::string blobHash) const {
    auto currentEntries = entries();
    bool updated = false;
    for (auto& entry : currentEntries) {
        if (entry.path == path) {
            entry.blobHash = blobHash;
            updated = true;
            break;
        }
    }
    if (!updated) {
        currentEntries.push_back(TreeEntry{std::move(path), std::move(blobHash)});
    }

    std::filesystem::create_directories(indexPath.parent_path());
    std::ofstream out(indexPath);
    if (!out) {
        throw StorageException("Cannot write index");
    }
    for (const auto& entry : currentEntries) {
        out << entry.path << ' ' << entry.blobHash << '\n';
    }
}

std::vector<TreeEntry> Index::entries() const {
    std::vector<TreeEntry> result;
    if (!std::filesystem::exists(indexPath)) {
        return result;
    }

    std::ifstream in(indexPath);
    if (!in) {
        throw StorageException("Cannot read index");
    }

    TreeEntry entry;
    while (in >> entry.path >> entry.blobHash) {
        result.push_back(entry);
    }
    if (!in.eof()) {
        throw CorruptedDataException("Corrupted index");
    }
    return result;
}

void Index::clear() const {
    std::ofstream out(indexPath, std::ios::trunc);
    if (!out) {
        throw StorageException("Cannot clear index");
    }
}
