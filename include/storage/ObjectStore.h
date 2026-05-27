#pragma once

#include "storage/ObjectDatabase.h"

#include <map>
#include <string>

template <typename TObject>
class ObjectStore {
public:
    explicit ObjectStore(const ObjectDatabase& objectDatabase) : database(objectDatabase) {}

    std::string add(const TObject& object) {
        const std::string hash = database.store(object);
        objectCache.emplace(hash, object);
        return hash;
    }

    TObject get(const std::string& hash) {
        const auto cached = objectCache.find(hash);
        if (cached != objectCache.end()) {
            return cached->second;
        }

        TObject object = TObject::deserialize(database.loadRaw(hash));
        objectCache.emplace(hash, object);
        return object;
    }

    bool contains(const std::string& hash) const {
        return objectCache.find(hash) != objectCache.end() || database.contains(hash);
    }

private:
    const ObjectDatabase& database;
    std::map<std::string, TObject> objectCache;
};
