#pragma once

#include <stdexcept>
#include <string>

class MiniGitException : public std::runtime_error {
public:
    explicit MiniGitException(const std::string& message)
        : std::runtime_error(message) {}
};

class ValidationException : public MiniGitException {
public:
    explicit ValidationException(const std::string& message)
        : MiniGitException("Validation error: " + message) {}
};

class NotFoundException : public MiniGitException {
public:
    explicit NotFoundException(const std::string& message)
        : MiniGitException("Not found: " + message) {}
};

class StorageException : public MiniGitException {
public:
    explicit StorageException(const std::string& message)
        : MiniGitException("Storage error: " + message) {}
};

class RepositoryException : public MiniGitException {
public:
    explicit RepositoryException(const std::string& message)
        : MiniGitException("Repository error: " + message) {}
};

class CorruptedDataException : public MiniGitException {
public:
    explicit CorruptedDataException(const std::string& message)
        : MiniGitException("Corrupted data: " + message) {}
};

class CommandLineException : public MiniGitException {
public:
    explicit CommandLineException(const std::string& message)
        : MiniGitException("Command line error: " + message) {}
};
