#include "objects/Tree.h"

#include "exceptions/MiniGitException.h"

#include <sstream>

Tree::Tree(std::vector<TreeEntry> entries) : entriesValue(std::move(entries)) {}

const std::vector<TreeEntry>& Tree::entries() const {
    return entriesValue;
}

std::string Tree::type() const {
    return "tree";
}

std::string Tree::serialize() const {
    std::ostringstream out;
    out << "type tree\n";
    for (const auto& entry : entriesValue) {
        out << "entry " << entry.path << ' ' << entry.blobHash << '\n';
    }
    return out.str();
}

std::shared_ptr<GitObject> Tree::clone() const {
    return std::make_shared<Tree>(*this);
}

Tree Tree::deserialize(const std::string& data) {
    std::istringstream in(data);
    std::string firstLine;
    std::getline(in, firstLine);
    if (firstLine != "type tree") {
        throw CorruptedDataException("Invalid tree object");
    }

    std::vector<TreeEntry> entries;
    std::string marker;
    while (in >> marker) {
        if (marker != "entry") {
            throw CorruptedDataException("Invalid tree entry");
        }
        TreeEntry entry;
        in >> entry.path >> entry.blobHash;
        if (entry.path.empty() || entry.blobHash.empty()) {
            throw CorruptedDataException("Invalid tree entry");
        }
        entries.push_back(std::move(entry));
    }
    return Tree(std::move(entries));
}
