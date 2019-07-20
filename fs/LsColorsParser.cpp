#include <cstdint>
#include <cstdio>

#include "LsColorsParser.h"

namespace fs {

int LsColorsParser::parse(const std::string& lsColors) noexcept {
    std::size_t prev = 0, current = 0;
    while ((current = lsColors.find(":", prev)) != std::string::npos) {
        const std::string kv = lsColors.substr(prev, current - prev);
        prev = current + 1;

        const std::size_t equal = kv.find("=");
        if (equal == std::string::npos) {
            return -1;
        }

        const std::string ftype = kv.substr(0, equal);
        const std::string color = kv.substr(equal + 1, kv.size() - equal - 1);

        if (ftype[0] == '*') {
            this->colorMap_.insert({ftype.substr(2, ftype.size() - 2), color});
        } else {
            this->colorMap_.insert({ftype, color}); 
        }
    }

    return 0;
}

} // namespace fs
