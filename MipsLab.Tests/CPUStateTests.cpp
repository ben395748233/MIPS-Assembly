
#include <cstdint>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "CPUState.hpp"

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

    void test_cpu_state() {
        mipslab::CPUState cpu;

        // TEST-001：確認初始 PC
        check(
            cpu.pc() == 0x00400000u,
            "Initial PC"
        );

        // TEST-002：確認 32 個 GPR 初始為 0
        bool all_zero = true;

        for (std::uint8_t i = 0; i < 32; ++i) {
            if (cpu.read_reg(i) != 0u) {
                all_zero = false;
            }
        }

        check(all_zero, "Initial GPR");

        // TEST-003：一般暫存器寫入與讀取
        cpu.write_reg(8, 42u);

        check(
            cpu.read_reg(8) == 42u,
            "Register Read/Write"
        );

        // TEST-004：$zero 不可修改
        cpu.write_reg(0, 999u);

        check(
            cpu.read_reg(0) == 0u,
            "Zero Register Protection"
        );

        // TEST-005：PC 更新
        cpu.set_pc(0x00400004u);

        check(
            cpu.pc() == 0x00400004u,
            "PC Update"
        );

        // TEST-006：32-bit 最大值
        cpu.write_reg(9, 0xFFFFFFFFu);

        check(
            cpu.read_reg(9) == 0xFFFFFFFFu,
            "32-bit Boundary Value"
        );

        // TEST-007：非法 Register Index
        bool exception_caught = false;

        try {
            (void)cpu.read_reg(32);
        }
        catch (const std::out_of_range&) {
            exception_caught = true;
        }

        check(
            exception_caught,
            "Invalid Register Index"
        );

        // TEST-008：CPU Reset
        cpu.reset();

        bool reset_ok =
            cpu.pc() == mipslab::CPUState::InitialPC;

        for (std::uint8_t i = 0; i < 32; ++i) {
            if (cpu.read_reg(i) != 0u) {
                reset_ok = false;
            }
        }

        check(reset_ok, "CPU Reset");
    }

} // namespace

int main() {
    try {
        test_cpu_state();
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
