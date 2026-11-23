1.
std::uint8_t 不代表只有 8 個 Register
代表這個參數是 8-bit 無號整數，通常可表示 0～255。
但 MIPS 只有 32 個 GPR，因此程式還需要：
if (index >= registers_.size()) {
    throw std::out_of_range("Invalid MIPS register");
}
實際 MIPS 機器指令只需要 5 bits 表示 Register Index：2^5=32
使用 uint8_t 是因為標準 C++ 沒有獨立的 5-bit 整數型別。
2.
pc() 和 read_reg() 的 const 不同於 constexpr
std::uint32_t pc() const noexcept;
這個 const 表示函式不修改物件的一般成員，不代表回傳值不能改變。
例：
cpu.pc();                  // 0x00400000
cpu.set_pc(0x00400004);
cpu.pc();                  // 0x00400004
即使 pc() 是 const 成員函式，每次呼叫仍然能讀取最新的 PC
3.