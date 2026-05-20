#include "commands/StatusCommand.h"

#include "Repository.h"
#include "utils/Templates.h"

#include <iostream>

void StatusCommand::execute(Repository& repo) {
    const auto entries = repo.status();
    if (entries.empty()) {
        std::cout << "No staged files\n";
        return;
    }

    std::cout << "Staged files:\n";
    printCollection(entries, [](std::ostream& out, const TreeEntry& entry) {
        out << "  " << entry.path << " -> " << entry.blobHash << '\n';
    });
}
