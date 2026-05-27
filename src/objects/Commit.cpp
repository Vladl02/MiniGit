#include "objects/Commit.h"

#include "exceptions/MiniGitException.h"

#include <sstream>

Commit::Commit(std::string treeHash,
               std::optional<std::string> parentHash,
               std::string author,
               std::string timestamp,
               std::string message)
    : treeHashValue(std::move(treeHash)),
      parentHashValue(std::move(parentHash)),
      authorValue(std::move(author)),
      timestampValue(std::move(timestamp)),
      messageValue(std::move(message)) {}

const std::string& Commit::treeHash() const {
    return treeHashValue;
}

const std::optional<std::string>& Commit::parentHash() const {
    return parentHashValue;
}

const std::string& Commit::author() const {
    return authorValue;
}

const std::string& Commit::timestamp() const {
    return timestampValue;
}

const std::string& Commit::message() const {
    return messageValue;
}

std::string Commit::type() const {
    return "commit";
}

std::string Commit::serialize() const {
    std::ostringstream out;
    out << "type commit\n";
    out << "tree " << treeHashValue << '\n';
    out << "parent " << (parentHashValue ? *parentHashValue : "none") << '\n';
    out << "author " << authorValue << '\n';
    out << "timestamp " << timestampValue << '\n';
    out << "message " << messageValue << '\n';
    return out.str();
}

std::shared_ptr<GitObject> Commit::clone() const {
    return std::make_shared<Commit>(*this);
}

Commit Commit::deserialize(const std::string& data) {
    std::istringstream in(data);
    std::string line;
    std::string treeHash;
    std::optional<std::string> parentHash;
    std::string author;
    std::string timestamp;
    std::string message;

    std::getline(in, line);
    if (line != "type commit") {
        throw CorruptedDataException("Invalid commit object");
    }

    std::getline(in, line);
    if (line.substr(0, 5) != "tree ") {
        throw CorruptedDataException("Invalid commit field: tree");
    }
    treeHash = line.substr(5);

    std::getline(in, line);
    if (line.substr(0, 7) != "parent ") {
        throw CorruptedDataException("Invalid commit field: parent");
    }
    const std::string parentValue = line.substr(7);
    if (parentValue != "none") {
        parentHash = parentValue;
    }

    std::getline(in, line);
    if (line.substr(0, 7) != "author ") {
        throw CorruptedDataException("Invalid commit field: author");
    }
    author = line.substr(7);

    std::getline(in, line);
    if (line.substr(0, 10) != "timestamp ") {
        throw CorruptedDataException("Invalid commit field: timestamp");
    }
    timestamp = line.substr(10);

    std::getline(in, line);
    if (line.substr(0, 8) != "message ") {
        throw CorruptedDataException("Invalid commit field: message");
    }
    message = line.substr(8);

    return Commit(std::move(treeHash), std::move(parentHash), std::move(author), std::move(timestamp), std::move(message));
}
