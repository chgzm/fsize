#ifndef LSCOLORSPARSER_H
#define LSCOLORSPARSER_H

#include <string>
#include <unordered_map>

namespace fs {

class LsColorsParser {
public:
    LsColorsParser()  = default;
    ~LsColorsParser() = default;

    int parse(const std::string& lsColors) noexcept;

    inline const std::string& getColorCode(const std::string& fileType) noexcept {
        return this->colorMap_[fileType];
    }

private:
    std::unordered_map<std::string, std::string> colorMap_;
};

} // namespace fs

#endif
