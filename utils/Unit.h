#ifndef UNIT_H
#define UNIT_H

#include <cstdint>
#include <string>

namespace utils {

constexpr const uint64_t UNIT = 1024;

std::string byteToHumanReadable(std::size_t byte) noexcept;

} // namespace utils end

#endif
