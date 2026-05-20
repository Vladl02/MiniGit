#pragma once

#include "hashing/IHashStrategy.h"

class SimpleHashStrategy final : public IHashStrategy {
public:
    std::string hash(const std::string& data) const override;
};
