#pragma once

#include "exceptions/MiniGitException.h"

#include <iostream>
#include <string>

template <typename T>
void requireNotEmpty(const T& value, const std::string& fieldName) {
    if (value.empty()) {
        throw ValidationException(fieldName + " must not be empty");
    }
}

template <typename TCollection, typename TPrinter>
void printCollection(const TCollection& collection, TPrinter printer) {
    for (const auto& item : collection) {
        printer(std::cout, item);
    }
}
