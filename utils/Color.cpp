#include "Color.h"

namespace utils {

void printWithColor(const std::string& color, const char* format, ...) noexcept {
    va_list args;
    va_start(args, format);

    std::string coloredFormat= "\033[";
    coloredFormat += color;
    coloredFormat += "m";
    coloredFormat += format;
    coloredFormat += "\033[0m";

    std::vprintf(coloredFormat.c_str(), args);
    va_end(args);
}

} // namespace utils

