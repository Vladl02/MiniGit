#include "hashing/SimpleHashStrategy.h"

#include <functional>
#include <sstream>

std::string SimpleHashStrategy::hash(const std::string& data) const {
    std::ostringstream out;
    out << std::hex << std::hash<std::string>{}(data);
    return out.str();
}
