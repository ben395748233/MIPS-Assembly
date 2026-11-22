#pragma once
//避免重複定義及處理
#include <array>
//提供st::array，用於保存佔存器
#include <cstdint>
//提供固定寬度整數;如std::uint8_t ，數字決定位元數

namespace mipslab {

    class CPUState {
    public:
        static constexpr std::uint32_t InitialPC = 0x00400000u;
        //0x00400000為設定起始位置

        CPUState() = default;
        //預設建構子 依照private建立 不嚴謹
        //*更正 使用編譯器產生的預設建構子 依照成員預設初始化設定 pc_ 與 registers_

        [[nodiscard]]
        //提醒使用者不要忽略回傳值
        std::uint32_t pc() const noexcept;
        //讀取Program Counter
        
        //不嚴謹const 承諾不修改該物件的非 mutable 狀態 
        //*更正 const：此成員函式不能修改物件的一般資料成員

        //不正確 mutable狀態只程式執行時，程式內容可直接被修改，不需建立或更改記憶體位置 
        //*更正  mutable：允許指定的成員在 const 成員函式內被修改
        //*mutable 與是否重新配置記憶體、是否正在執行程式沒有直接關係。

        //noexcept 表示函式不應讓例外傳播出去。若例外真的逃出 noexcept 函式，程式會呼叫 std::terminate()，也就是終止程式

        void set_pc(std::uint32_t value) noexcept;
        //設定Program Counter

        [[nodiscard]]
        std::uint32_t read_reg(std::uint8_t index) const;

        void write_reg(
            std::uint8_t index,
            //代表MIPS的32個General Purpose Registers:詳細在README中
            std::uint32_t value
            //設定index中數值，但0永遠為0
        );

        void reset() noexcept;

    private:
        std::uint32_t pc_ = InitialPC;
        std::array<std::uint32_t, 32> registers_{};
        //{}初始化會將所有元素初始化0
        //這裡真正保存 CPU 的狀態。
    };

}
