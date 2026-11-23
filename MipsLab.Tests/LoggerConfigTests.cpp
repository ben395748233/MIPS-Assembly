#include <cstdint>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>

#include "Logger.hpp"
#include "SimulationConfig.hpp"

namespace {

    int passed = 0;
    int failed = 0;

    void check(bool condition, const char* name) {
        if (condition) {
            ++passed;
            std::cout << "[PASS] " << name << '\n';
        }
        else {
            ++failed;
            std::cerr << "[FAIL] " << name << '\n';
        }
    }

    // 用 RAII 保證測試結束後恢復 stderr
    class CerrCapture {
    public:
        CerrCapture()
            : old_buffer_(std::cerr.rdbuf(buffer_.rdbuf())) {
        }

        ~CerrCapture() {
            std::cerr.rdbuf(old_buffer_);
        }

        CerrCapture(const CerrCapture&) = delete;
        CerrCapture& operator=(const CerrCapture&) = delete;

        std::string str() const {
            return buffer_.str();
        }

    private:
        std::ostringstream buffer_;
        std::streambuf* old_buffer_;
    };

    void test_logger() {

        // LOG-001：Info Log
        {
            CerrCapture capture;

            mipslab::Logger::info("Logger initialized");

            check(
                capture.str().find("[INFO] Logger initialized")
                != std::string::npos,
                "LOG-001 Info Log"
            );
        }

        // LOG-002：Error Log
        {
            CerrCapture capture;

            mipslab::Logger::error("Invalid configuration");

            check(
                capture.str().find("[ERROR] Invalid configuration")
                != std::string::npos,
                "LOG-002 Error Log"
            );
        }

        // LOG-003：確認 Logger 寫入 stderr，
        // 而非 stdout
        {
            CerrCapture capture;

            mipslab::Logger::warning("Test warning");

            check(
                capture.str() == "[WARNING] Test warning\n",
                "LOG-003 stderr Output"
            );
        }
    }

    void test_configuration() {

        mipslab::SimulationConfig config;

        // CFG-001：預設使用 Sequential Engine
        check(
            config.engine == mipslab::EngineType::Sequential,
            "CFG-001 Default Engine"
        );

        // CFG-002：預設最大週期數
        check(
            config.max_cycles == 1'000'000ULL,
            "CFG-002 Default Max Cycles"
        );

        // CFG-003：預設不啟用 verbose
        check(
            config.verbose == false,
            "CFG-003 Default Verbose"
        );

        // CFG-004：修改設定
        config.engine = mipslab::EngineType::Pipeline;
        config.max_cycles = 5000;
        config.verbose = true;

        check(
            config.engine == mipslab::EngineType::Pipeline &&
            config.max_cycles == 5000 &&
            config.verbose,
            "CFG-004 Config Modification"
        );
    }

} // namespace

int main() {
    try {
        test_logger();
        test_configuration();
    }
    catch (const std::exception& e) {
        std::cerr << "[ERROR] " << e.what() << '\n';
        return 1;
    }

    std::cout << "\nTests passed: " << passed
        << "\nTests failed: " << failed
        << '\n';

    return failed == 0 ? 0 : 1;
}
