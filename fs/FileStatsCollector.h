#ifndef FILESTATSLOADER_H
#define FILESTATSLOADER_H

#include "FileDescriptionLoader.h"
#include "FileStats.h"
#include "CollectorParam.h"
#include "LsColorsParser.h"

#include <cstdint>
#include <queue>
#include <memory>
#include <string>
#include <fts.h>
#include <sys/stat.h>

namespace fs {

constexpr const uint32_t S_IXANY = (S_IXUSR | S_IXGRP | S_IXOTH);

enum class FileType : uint8_t {
    FILE,
    DIR, 
    LNK,
    FIFO, 
    SOCK,
    BLK,
    CHR, 
    SUID,
    SGID,
    EXEC, 
    UNKNOWN
};

FileType getFileType(uint32_t mode) noexcept;

const std::string getExtention(const std::string& path) noexcept;

class FileStatsCollector {
public:
    inline FileStatsCollector(const CollectorParam* param) 
      : param_(param), 
        fileStatsList_() {
        this->fileStatsList_.reserve(4194304);
    }
    ~FileStatsCollector() = default;

    int init()  noexcept;
    int print() noexcept;

private:
    const CollectorParam*                   param_;
    std::vector<std::unique_ptr<FileStats>> fileStatsList_;
    FileDescriptionLoader                   descLoader_;
    LsColorsParser                          lsColorsParser_;
};

} // namespace fs end

#endif
