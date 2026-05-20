#pragma once

#include "objects/GitObject.h"

#include <string>

class Blob final : public GitObject {
public:
    explicit Blob(std::string content);

    const std::string& content() const;
    std::string type() const override;
    std::string serialize() const override;
    std::shared_ptr<GitObject> clone() const override;

    static Blob deserialize(const std::string& data);

private:
    std::string contentValue;
};
