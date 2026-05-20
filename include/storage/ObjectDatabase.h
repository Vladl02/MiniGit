#pragma once

#include "hashing/IHashStrategy.h"
#include "objects/GitObject.h"

#include <filesystem>
#include <memory>
#include <string>

class ObjectDatabase {
public:
    ObjectDatabase(std::filesystem::path objectsPath, std::shared_ptr<IHashStrategy> hashStrategy);

    std::string store(const GitObject& object) const;
    std::string loadRaw(const std::string& hash) const;
    bool contains(const std::string& hash) const;

private:
    std::filesystem::path objectPath(const std::string& hash) const;

    std::filesystem::path objectsPath;
    std::shared_ptr<IHashStrategy> hashStrategy;
};
