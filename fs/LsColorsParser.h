#ifndef LSCOLORSPARSER_H
#define LSCOLORSPARSER_H

#include <string>
#include <unordered_map>

namespace fs {

class LsColorsParser {
public:
    LsColorsParser() {}
    ~LsColorsParser() {}

    int parse(const std::string& lsColors);

    inline const std::string& getColorCode(const std::string& fileType)
    {
        return this->colorMap_[fileType];
    }

private:
    std::unordered_map<std::string, std::string> colorMap_;
};

} // end of namespace fs

#endif
