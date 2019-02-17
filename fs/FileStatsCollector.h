#ifndef FILESTATSLOADER_H
#define FILESTATSLOADER_H

#include "FileDescriptionLoader.h"
#include "FileStats.h"
#include "CollectorParam.h"
#include "LsColorsParser.h"

#include <cstdint>
#include <queue>
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

FileType getFileType(uint32_t mode);

const std::string getExtention(const std::string& path);

class FileStatsCollector {
public:
    inline FileStatsCollector(const CollectorParam* param) : param_(param), fileStatsList_()
    {
        this->fileStatsList_.reserve(4194304);
    }
    ~FileStatsCollector() {}

    int init();
    int print();

private:
    const CollectorParam* param_;
    std::vector<FileStats> fileStatsList_;
    FileDescriptionLoader descLoader_;
    LsColorsParser lsColorsParser_;
};

} // namespace fs end

#endif
