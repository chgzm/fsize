#ifndef COLOR_H
#define COLOR_H

#include <cstdio>
#include <cstdarg>
#include <string>

namespace utils {

void printWithColor(const std::string& color, const char* format, ...);

} // namespace utils end

#endif
