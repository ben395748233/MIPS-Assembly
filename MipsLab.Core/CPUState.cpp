
#include "pch.h"
#include "CPUState.hpp"

#include <stdexcept>

namespace mipslab {

    std::uint32_t CPUState::pc() const noexcept {
        return pc_;
    }
    //回傳PC的值

    void CPUState::set_pc(std::uint32_t value) noexcept {
        pc_ = value;
    }
    //該函式修改PC的值，但計算不是在這執行:後續會補上

    std::uint32_t CPUState::read_reg(
        std::uint8_t index
    ) const {
        if (index >= registers_.size()) {
            throw std::out_of_range("Invalid MIPS register");
        }
        //檢查是否超出INDEX 0~31(是否合法)

        return index == 0 ? 0 : registers_[index];
        //處理INDEX=0的VALUE必須為0
    }

    void CPUState::write_reg(
        std::uint8_t index,
        std::uint32_t value
    ) {
        if (index >= registers_.size()) {
            throw std::out_of_range("Invalid MIPS register");
        }
        //同上，檢測INDEX是否合法
        if (index != 0) {
            registers_[index] = value;
        }
        //若Index為0，會被忽略，因index=0數值必須為0
    }

    void CPUState::reset() noexcept {
        pc_ = InitialPC;
        //重製PC位置
        registers_.fill(0);
        //把所有 32 個 General Purpose Registers 設為 0。Index 0-31都設為0
    }
    //易誤解 只會重設不會清除
    //*更正  將 CPUState 恢復到預設初始狀態
    //*重點  只清除 GPR 原本保存的數值，但不銷毀 CPUState 物件
    // 此模組尚未管理 Memory，因此不會清除 RAM
    //後續完善

}
