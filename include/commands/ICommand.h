#pragma once

class Repository;

class ICommand {
public:
    virtual void execute(Repository& repo) = 0;
    virtual ~ICommand() = default;
};
