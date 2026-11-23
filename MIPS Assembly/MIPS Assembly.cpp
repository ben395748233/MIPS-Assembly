
#include <iostream>
#include <string_view>

namespace {

    constexpr std::string_view Version = "0.1.0";

    void print_version() {
        std::cout
            << "MIPS Architecture Lab v"
            << Version << '\n';
    }

    void print_help() {
        std::cout
            << "MIPS Architecture Lab\n\n"
            << "Usage:\n"
            << "  mipslab --help\n"
            << "  mipslab --version\n\n"
            << "Future commands:\n"
            << "  assemble\n"
            << "  disasm\n"
            << "  run\n"
            << "  trace\n"
            << "  compare\n"
            << "  benchmark\n";
    }

}

int main(int argc, char* argv[]) {

    // argc：命令列參數數量，包含程式名稱
    // argv：每個參數對應的字串

    if (argc == 1) {
        print_help();
        return 0;
    }

    if (argc != 2) {
        std::cerr << "Error: Invalid arguments\n";
        return 2;
    }

    std::string_view argument{ argv[1] };

    if (argument == "--help" || argument == "-h") {
        print_help();
        return 0;
    }

    if (argument == "--version") {
        print_version();
        return 0;
    }

    std::cerr
        << "Error: Unknown argument: "
        << argument << '\n';

    return 2;
}
