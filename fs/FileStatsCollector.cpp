#include "FileStatsCollector.h"

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <algorithm>
#include <magic.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <Time.h>
#include <Color.h>
#include <Unit.h>

namespace fs {

FileType getFileType(uint32_t mode) noexcept {
    if (S_ISREG(mode)) { 
        if      (mode & S_ISUID) { return FileType::SUID; }
        else if (mode & S_ISGID) { return FileType::SGID; }
        else if (mode & S_IXANY) { return FileType::EXEC; } 
        else                     { return FileType::FILE; }
    }
    else if (S_ISDIR(mode))  { return FileType::DIR;     }
    else if (S_ISCHR(mode))  { return FileType::CHR;     }
    else if (S_ISBLK(mode))  { return FileType::BLK;     }
    else if (S_ISFIFO(mode)) { return FileType::FIFO;    }
    else if (S_ISLNK(mode))  { return FileType::LNK;     }
    else if (S_ISSOCK(mode)) { return FileType::SOCK;    }
    else                     { return FileType::UNKNOWN; }
}

const std::string getExtention(const std::string& path) noexcept {
    const std::size_t lastDotPos = path.find_last_of(".");
    return path.substr(lastDotPos + 1, path.size() - lastDotPos - 1);
}

int FileStatsCollector::init() noexcept {
    char* const paths[] = {const_cast<char*>(this->param_->dirPath.c_str()), nullptr};
    FTS* fts = ::fts_open(paths, 0, nullptr);
    if (fts == nullptr) {
        std::fprintf(stderr, "Invalid directory");
        return -1;
    }

    FTSENT* ent = nullptr;
    while ((ent = ::fts_read(fts)) != nullptr) {
        if (getFileType(ent->fts_statp->st_mode) == FileType::DIR) {
            continue;
        }

        auto stats = std::make_unique<FileStats>(
            ent->fts_statp->st_size,
            ent->fts_statp->st_atim.tv_sec,
            ent->fts_statp->st_mtim.tv_sec,
            ent->fts_path,
            ent->fts_statp->st_mode
        );

        this->fileStatsList_.push_back(std::move(stats));
    }

    if (this->param_->reverseFlag) {
        std::sort(this->fileStatsList_.begin(), this->fileStatsList_.end(), [](std::unique_ptr<FileStats>& lhs, std::unique_ptr<FileStats>& rhs) {
            return lhs->fileSize_ < rhs->fileSize_;
        });
    } else {
        std::sort(this->fileStatsList_.begin(), this->fileStatsList_.end(), [](std::unique_ptr<FileStats>& lhs, std::unique_ptr<FileStats>& rhs) {
            return lhs->fileSize_ > rhs->fileSize_;
        });
    }

    if (::fts_close(fts) != 0) {
        return -1;
    }         

    if (this->descLoader_.init(MAGIC_NONE) != 0) {
        return -1;
    }

    const char* lsColors = ::getenv("LS_COLORS");
    if (this->lsColorsParser_.parse(lsColors) != 0) {
        return -1;
    }

    return 0;
}

int FileStatsCollector::print() noexcept {
    const int indexWidth = std::max(2, (int)(std::log10(this->param_->numOfLines) + 1));

    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) != 0) {
        std::fprintf(stderr, "failed to get winsize\n");
        return -1;
    }
    
    const int pathWidth = w.ws_col - indexWidth - 106;

    utils::printWithColor(
        "30;47",
        "%*s  %10s  %-19s  %-19s  %-48s  %-*s\n",
        indexWidth, "No",
        "File Size", 
        "Access Time",
        "Modification Time", 
        "File Description",
        pathWidth, "Path"
    );

    for (std::size_t i = 0; i < this->fileStatsList_.size(); ++i) {
        std::unique_ptr<FileStats>& stats = this->fileStatsList_[i];

        std::string desc;
        if (this->descLoader_.getFileDescription(stats->path_, desc) != 0) {
            std::fprintf(stderr, "getFileDescription failed\n");
            return -1;
        }

        std::printf(
            "%*lu  %10s  %-19s  %-19s  %-48s  ", 
            indexWidth, i + 1,
            utils::byteToHumanReadable(stats->fileSize_).c_str(),
            utils::secToDateTime(stats->accessTime_).c_str(),
            utils::secToDateTime(stats->modificationTime_).c_str(),
            desc.c_str()
        );


        std::string color;
        switch (getFileType(stats->mode_)) {
        case FileType::FILE: {
            const std::string ext = getExtention(stats->path_);
            color = this->lsColorsParser_.getColorCode(ext);
            if (color == "") {
                color = this->lsColorsParser_.getColorCode("no");
            }
            break;
        }
        case FileType::SUID:    { color = this->lsColorsParser_.getColorCode("su"); break; }
        case FileType::SGID:    { color = this->lsColorsParser_.getColorCode("sg"); break; }
        case FileType::EXEC:    { color = this->lsColorsParser_.getColorCode("ex"); break; }
        case FileType::DIR:     { color = this->lsColorsParser_.getColorCode("di"); break; }
        case FileType::CHR:     { color = this->lsColorsParser_.getColorCode("cd"); break; }
        case FileType::FIFO:    { color = this->lsColorsParser_.getColorCode("pi"); break; }
        case FileType::BLK:     { color = this->lsColorsParser_.getColorCode("bd"); break; }
        case FileType::LNK:     { color = this->lsColorsParser_.getColorCode("ln"); break; }
        case FileType::SOCK:    { color = this->lsColorsParser_.getColorCode("so"); break; }
        case FileType::UNKNOWN: { color = this->lsColorsParser_.getColorCode("no"); break; }
        default:                { color = this->lsColorsParser_.getColorCode("no"); break; }
        }

        utils::printWithColor(color, "%s\n", stats->path_.c_str());

        if (this->param_->numOfLines <= (i + 1)) {
            break;
        }
    }

    return 0;
}

} // namespace fs end
