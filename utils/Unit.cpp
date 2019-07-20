#include <cmath>
#include <array>

#include "Unit.h"

namespace utils {

const std::array<std::string, 6> prefix = {"K", "M", "G", "T", "P", "E"};

std::string byteToHumanReadable(std::size_t byte) noexcept {
    char buf[16];
    if (byte < UNIT) {
        std::snprintf(buf, sizeof(buf), "%lu", byte);
        return buf;
    } 
    
    const int exp = (int)(std::log2(byte) / std::log2(UNIT));

    std::snprintf(buf, sizeof(buf), "%.3f%s", byte / std::pow(UNIT, exp), prefix[exp-1].c_str());

    return buf;
}

} // namespace utils

