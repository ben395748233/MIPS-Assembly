環境 c++20,MSVC x64

因某些原因 該專案會變成手搓一顆虛擬cpu了 不只是 CPU 模擬器，還包含 Compiler、Assembler、Linker、Loader 等系統軟體。

MIPS Assembly 主控台。

**MppsLab.Core 靜態函式庫。
  ---CPUState.hpp 介面及資料結構定義
     ---MIPS 有 32 個 General Purpose Registers	
     編號	名稱	常見用途
     0	    $zero	永遠為 0
     1	    $at	Assembler Temporary
     2–3	$v0–$v1	函式回傳值
     4–7	$a0–$a3	函式參數
     8–15	$t0–$t7	Temporary
     16–23	$s0–$s7	Saved Registers
     24–25	$t8–$t9	Temporary
     26–27	$k0–$k1	Kernel Reserved
     28	    $gp	        Global Pointer
     29	    $sp	        Stack Pointer
     30	    $fp / $s8	Frame Pointer
     31	$ra	Return Address	

  ---CPUState.cpp 實作及狀態管理

**Workflow 各項設定的意義
設定	功能
push	推送程式碼時自動執行
pull_request	建立或更新 PR 時執行
workflow_dispatch	在 GitHub 網頁手動執行
windows-2022	使用 VS2022 Windows Runner
actions/checkout@v6	取得 Repository 原始碼
pwsh	使用 PowerShell 執行指令
validate.ps1	執行 Debug / Release 編譯及測試