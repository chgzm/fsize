#include <algorithm>
#include "FileDescriptionLoader.h"

namespace fs {

FileDescriptionLoader::~FileDescriptionLoader() {
    magic_close(this->magicCookie_);
} 

int FileDescriptionLoader::init(int flags) noexcept {
    this->magicCookie_ = magic_open(flags);
    if (this->magicCookie_ == nullptr) {
        std::fprintf(stderr, "magic_open failed\n");
        return -1;
    }

    return 0;
}

int FileDescriptionLoader::getFileDescription(const std::string& path, std::string& desc) noexcept {
    if (magic_load(this->magicCookie_, nullptr)) {
        std::fprintf(stderr, "magic_load failed\n");
        return -1;
    }

    const char* ret = magic_file(this->magicCookie_, path.c_str());
    if (ret == nullptr) {
        std::fprintf(stderr, "magic_file failed\n");
        return -1;
    }

    const std::string buf = ret;
    if (buf.size() <= 48) {
        desc = std::move(buf);
        return 0;
    }

    const std::size_t pos = buf.find(",");
    desc = buf.substr(0, std::min(pos, 48ul));

    return 0;
}

} // namespace fs

