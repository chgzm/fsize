#include <CollectorParam.h>
#include <FileStatsCollector.h>

#include <cstdio>
#include <unistd.h>
#include <getopt.h>

static constexpr struct option longopts[] = {
    { "num",     required_argument, nullptr, 'n' },
    { "reverse", no_argument,       nullptr, 'r' },
    { "help",    no_argument,       nullptr, 'h' },
    { 0,         0,                 0,        0  },
};

static void usage() noexcept {
    std::printf(
        "Usage: fsize [-r] [-n num] [-h] [directory]\n"
        " -n, --num=N    Set number of files displayed\n"
        " -r, --reverse  Show files in ascending order\n"
        " -h, --help     Show help and exit\n"
    );        
} 

static int parseCommandLine(int argc, char* argv[], fs::CollectorParam& param) noexcept {
    int opt = 0, longIndex = 0;
    while ((opt = getopt_long(argc, argv, ":n:rh", longopts, &longIndex)) != -1) {
        switch (opt) {
        case 'n': { param.numOfLines   = std::stoi(optarg); break;   }
        case 'r': { param.reverseFlag  = true;              break;   }
        case 'h': { usage();                                exit(0); }
        default:  { 
            std::fprintf(stderr, "Invalid option '%c'\n", opt);
            return -1;
        }
        }
    }    

    if (optind < argc) {
        param.dirPath = argv[optind];
    } else {
        param.dirPath = ".";
    }

    return 0;
}

int main(int argc, char* argv[]) {
    fs::CollectorParam param;
    if (parseCommandLine(argc, argv, param) != 0) {
        usage();
        return -1;
    }

    fs::FileStatsCollector fileStatsCollector(&param);
    if (fileStatsCollector.init() != 0) {
        return -1;
    }

    if (fileStatsCollector.print() != 0) {
        return -1;
    }

    return 0;
}
