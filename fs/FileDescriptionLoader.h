#ifndef FILEDESCRIPTIONLOADER_H
#define FILEDESCRIPTIONLOADER_H

#include <magic.h>
#include <string>

namespace fs {

class FileDescriptionLoader {
public:
    FileDescriptionLoader() : magicCookie_(nullptr) {}
    ~FileDescriptionLoader();

    int init(int flags) noexcept;

    int getFileDescription(const std::string& path, std::string& desc) noexcept;

private:
    magic_t magicCookie_;
};

} // end of namespace fs

#endif
