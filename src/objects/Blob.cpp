#include "objects/Blob.h"

#include "exceptions/MiniGitException.h"

#include <sstream>

Blob::Blob(std::string content) : contentValue(std::move(content)) {}

const std::string& Blob::content() const {
    return contentValue;
}

std::string Blob::type() const {
    return "blob";
}

std::string Blob::serialize() const {
    return "type blob\ncontent:\n" + contentValue;
}

std::shared_ptr<GitObject> Blob::clone() const {
    return std::make_shared<Blob>(*this);
}

Blob Blob::deserialize(const std::string& data) {
    const std::string marker = "type blob\ncontent:\n";
    if (data.substr(0, marker.size()) != marker) {
        throw CorruptedDataException("Invalid blob object");
    }
    return Blob(data.substr(marker.size()));
}
