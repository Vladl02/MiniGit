#include "CommitBuilder.h"

#include "utils/Templates.h"

CommitBuilder& CommitBuilder::setTreeHash(std::string treeHash) {
    treeHashValue = std::move(treeHash);
    return *this;
}

CommitBuilder& CommitBuilder::setParentHash(std::optional<std::string> parentHash) {
    parentHashValue = std::move(parentHash);
    return *this;
}

CommitBuilder& CommitBuilder::setAuthor(std::string author) {
    authorValue = std::move(author);
    return *this;
}

CommitBuilder& CommitBuilder::setTimestamp(std::string timestamp) {
    timestampValue = std::move(timestamp);
    return *this;
}

CommitBuilder& CommitBuilder::setMessage(std::string message) {
    messageValue = std::move(message);
    return *this;
}

Commit CommitBuilder::build() const {
    requireNotEmpty(treeHashValue, "Tree hash");
    requireNotEmpty(authorValue, "Author");
    requireNotEmpty(timestampValue, "Timestamp");
    requireNotEmpty(messageValue, "Commit message");
    return Commit(treeHashValue, parentHashValue, authorValue, timestampValue, messageValue);
}
