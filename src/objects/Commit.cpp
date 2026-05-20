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

    auto readPrefixedLine = [&in](const std::string& prefix) {
        std::string current;
        if (!std::getline(in, current) || current.rfind(prefix, 0) != 0) {
            throw CorruptedDataException("Invalid commit field: " + prefix);
        }
        return current.substr(prefix.size());
    };

    treeHash = readPrefixedLine("tree ");
    const std::string parentValue = readPrefixedLine("parent ");
    if (parentValue != "none") {
        parentHash = parentValue;
    }
    author = readPrefixedLine("author ");
    timestamp = readPrefixedLine("timestamp ");
    message = readPrefixedLine("message ");

    return Commit(std::move(treeHash), std::move(parentHash), std::move(author), std::move(timestamp), std::move(message));
}
