#pragma once

#include <string>

class IHashStrategy {
public:
    virtual std::string hash(const std::string& data) const = 0;
    virtual ~IHashStrategy() = default;
};
