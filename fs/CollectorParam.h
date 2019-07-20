#ifndef COLLECTORPARAM_H
#define COLLECTORPARAM_H

#include <cstdint>
#include <string>

namespace fs {

struct CollectorParam {
    CollectorParam() 
      : dirPath(),
        numOfLines(30),
        reverseFlag(false)
    {}

    std::string dirPath;
    std::size_t numOfLines;
    bool        reverseFlag;
};

} // namespace fs end

#endif
