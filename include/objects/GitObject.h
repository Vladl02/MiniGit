#pragma once

#include <memory>
#include <string>

class GitObject {
public:
    virtual std::string type() const = 0;
    virtual std::string serialize() const = 0;
    virtual std::shared_ptr<GitObject> clone() const = 0;
    virtual ~GitObject() = default;
};
