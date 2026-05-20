#pragma once

#include "storage/ObjectDatabase.h"

#include <string>

template <typename TObject>
class ObjectStore {
public:
    explicit ObjectStore(const ObjectDatabase& objectDatabase) : database(objectDatabase) {}

    std::string add(const TObject& object) const {
        return database.store(object);
    }

    TObject get(const std::string& hash) const {
        return TObject::deserialize(database.loadRaw(hash));
    }

    bool contains(const std::string& hash) const {
        return database.contains(hash);
    }

private:
    const ObjectDatabase& database;
};
