#include "WorkingDirectory.h"

#include "exceptions/MiniGitException.h"
#include "objects/Blob.h"
#include "storage/ObjectStore.h"

#include <fstream>

WorkingDirectory::WorkingDirectory(std::filesystem::path rootPath) : root(std::move(rootPath)) {}

std::string WorkingDirectory::readFile(const std::string& relativePath) const {
    const auto path = resolve(relativePath);
    if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path)) {
        throw NotFoundException("File not found: " + relativePath);
    }

    std::ifstream in(path, std::ios::binary);
    if (!in) {
        throw StorageException("Cannot read file: " + relativePath);
    }
    return std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
}

void WorkingDirectory::writeTree(const Tree& tree, const ObjectStore<Blob>& blobs) const {
    for (const auto& entry : tree.entries()) {
        const auto path = resolve(entry.path);
        std::filesystem::create_directories(path.parent_path());

        const Blob blob = blobs.get(entry.blobHash);
        std::ofstream out(path, std::ios::binary);
        if (!out) {
            throw StorageException("Cannot write file: " + entry.path);
        }
        out << blob.content();
    }
}

std::filesystem::path WorkingDirectory::resolve(const std::string& relativePath) const {
    const std::filesystem::path path(relativePath);
    if (path.is_absolute()) {
        throw ValidationException("Expected a path relative to repository root");
    }
    return root / path;
}
