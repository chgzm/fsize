#include "Time.h"

namespace utils {

std::string secToDateTime(int64_t tv_sec)
{
    struct tm tm;
    ::localtime_r(&(tv_sec), &tm);

    char buf[24];
    std::snprintf(
        buf,
        sizeof(buf),
        "%d-%02d-%02d %02d:%02d:%02d",
        tm.tm_year + 1900,
        tm.tm_mon + 1,
        tm.tm_mday,
        tm.tm_hour,
        tm.tm_min,
        tm.tm_sec);

    return buf;
}

} // namespace utils end
