#ifndef FILESTATS_H
#define FILESTATS_H

#include <cstdint>
#include <string>

namespace fs {

struct FileStats {
    FileStats(
        std::size_t fileSize, 
        int64_t accessTime,
        int64_t modificationTime, 
        const std::string& path,
         uint32_t mode
    )
      : fileSize_(fileSize),
        accessTime_(accessTime),
        modificationTime_(modificationTime),
        path_(path),
        mode_(mode) {
    }

    FileStats(const FileStats&)  = default;
    FileStats(FileStats&& stats) = default;
    FileStats& operator=(const FileStats&) = default;

    std::size_t  fileSize_;
    int64_t      accessTime_;
    int64_t      modificationTime_;
    std::string  path_;
    uint32_t     mode_;
};

} // namespace fs

#endif
