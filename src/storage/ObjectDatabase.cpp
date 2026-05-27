#include "storage/ObjectDatabase.h"

#include "exceptions/MiniGitException.h"

#include <fstream>

ObjectDatabase::ObjectDatabase(std::filesystem::path objectsPath, std::shared_ptr<IHashStrategy> hashStrategy)
    : objectsPath(std::move(objectsPath)), hashStrategy(std::move(hashStrategy)) {
    if (!this->hashStrategy) {
        throw ValidationException("Hash strategy must not be null");
    }
}

std::string ObjectDatabase::store(const GitObject& object) const {
    const std::string data = object.serialize();
    const std::string objectHash = hashStrategy->hash(data);
    std::filesystem::create_directories(objectsPath);

    std::ofstream out(objectPath(objectHash), std::ios::binary);
    if (!out) {
        throw StorageException("Cannot write object: " + objectHash);
    }
    out << data;
    return objectHash;
}

std::string ObjectDatabase::loadRaw(const std::string& hash) const {
    std::ifstream in(objectPath(hash), std::ios::binary);
    if (!in) {
        throw NotFoundException("Object hash not found: " + hash);
    }

    std::string data;
    char character;
    while (in.get(character)) {
        data += character;
    }
    return data;
}

bool ObjectDatabase::contains(const std::string& hash) const {
    return std::filesystem::exists(objectPath(hash));
}

std::filesystem::path ObjectDatabase::objectPath(const std::string& hash) const {
    return objectsPath / hash;
}
