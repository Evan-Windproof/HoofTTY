# HoofTTY

**Beta 0.3.0 · 受《My Little Pony》（彩虹小馬）啟發的 x86-64 純文字優先業餘作業系統。**

[English](README.md) · [简体中文](README.zh-CN.md) · [繁體中文](README.zh-TW.md)

> **開發狀態：實驗性 Beta。** HoofTTY 是由 **Kernseed OS Phase 7** 延伸而來的獨立業餘作業系統，不是 Linux 發行版、既有 Shell 主題，也不是終端機模擬器。請勿用於正式工作或儲存重要資料。
>
> **授權提醒：** 本儲存庫使用 **PolyForm Noncommercial 1.0.0**。原始碼公開，但授權限制商業使用，**並非 OSI 認可的開放原始碼授權**；詳見文末。

## 專案簡介

HoofTTY 嘗試不依賴傳統圖形桌面，透過獨立的 Shell、MLP 主題指令、彩色文字與像素藝術，讓小型作業系統擁有鮮明的小馬風格。它不是替既有 Linux 終端機換皮，而是在自己的核心和開機流程上進行開發。

專案延續了 **Kernseed OS Phase 7 的教學型 x86-64 巨集核心（monolithic kernel）基礎**。為避免破壞現有可用的建置路徑，部分內部名稱依舊保留 `kernseed`，例如標頭檔目錄、編譯巨集與 ISO/ELF 檔名；對使用者顯示的產品名稱仍為 **HoofTTY**。

這是個人興趣性質的非商業同人專案，與 Hasbro 並無從屬、贊助或官方認可關係。

## Beta 0.3.0 目前進度

| 項目 | 目前狀況 |
| --- | --- |
| 開機 | 使用 Limine 開機載入器；儲存庫附有 QEMU 執行腳本 |
| 核心 | 以 Kernseed 為基礎的 x86-64 教學巨集核心，保留中斷、記憶體管理、排程和內建 Ring 3 範例 |
| 顯示 | Framebuffer 終端機，5×7 ASCII 點陣字型放大顯示，支援 **16 色前景文字** |
| 開機畫面 | 彩色 HoofTTY 歡迎文字與實驗性 Evan 像素頭像（原始索引色尺寸 48×54） |
| Shell | `hoof>` 提示符號、指令註冊、有界參數剖析與基本輸入編輯 |
| MLP 主題 | 已加入 `friendship`、`party`、`rainboom`、`yay` 等指令 |
| 診斷資訊 | 系統資訊、實體記憶體頁面統計、工作狀態及 PIT 開機時間 |
| 應用程式 | 固定的一組內建 Ring 3 範例；**尚無通用 ELF 載入器** |

**目前指令清單共有 13 條。** 先前討論過的 `pony` 與隱藏指令 `Who's Evan?` 並未列入這個版本已實作的 Shell 指令；開機時繪製 Evan 頭像是另一項顯示功能。

## 建置與執行

### 環境需求

建議在 Linux 環境（或已裝妥工具的 WSL）準備：

- 支援 x86-64 的 GCC、GNU binutils（`ld`、`objcopy`）、GNU Make、主機端 C 編譯器
- Python 3、Git、`sha256sum`、基本 POSIX Shell 工具和 `xorriso`
- QEMU（`qemu-system-x86_64`），供專案內建執行目標使用
- 首次取得相依項目須有網路連線：腳本會擷取固定提交版本的 Limine，並檢查已記錄的雜湊值

在**儲存庫根目錄**執行：

```sh
git clone https://github.com/Evan-Windproof/HoofTTY.git
cd HoofTTY
make iso
make run
```

目前 Makefile 輸出的 ISO 位於 **`build/kernseed.iso`**。這是沿用的內部檔名，**不需要為了統一品牌而更名**。預設 QEMU 設定使用 128 MiB 記憶體、單一虛擬 CPU 和標準 VGA。

開發者常用指令：

```sh
make test-host     # 主機端單元測試
make check         # ELF 檢查（需要時先進行建置）
make headless      # 不開圖形視窗，顯示序列埠輸出
make debug         # 暫停 QEMU，GDB 伺服器位於 127.0.0.1:1234
make clean         # 清除建置產物
```

`make test` 會執行更完整、涵蓋多種建置設定的測試流程，也可能改變目前的建置設定，適合在發行前使用。以上為已檢查的 Makefile／腳本功能，不代表 Beta 0.3.0 的每個測試目標都已經實際通過。**開發期間已於 QEMU 圖形視窗展示；不保證 VMware 或實體硬體的相容性。**

## Shell 指令速查

進入系統後輸入 `friendship` 可列出指令，`friendship colors` 等可查看個別指令的說明。指令名稱有大小寫之分。

| 指令 | 用法 | 功能 |
| --- | --- | --- |
| `about` | `about` | 顯示系統資訊、授權與部分實作限制 |
| `apps` | `apps` | 列出內建原生示範應用程式 |
| `colors` | `colors` | 示範終端機 **16 色前景** 調色盤 |
| `echo` | `echo [text ...]` | 輸出解析後的引數，最多七個文字引數 |
| `friendship` | `friendship [command]` | 列出指令或查看指定指令的說明 |
| `meminfo` | `meminfo` | 查看實體記憶體頁面及頁表等統計 |
| `party` | `party` | 印出 Pinkie Pie 風格的彩色派對訊息 |
| `rainboom` | `rainboom` | 清除終端機畫面 |
| `reboot` | `reboot` | 透過 i8042 控制器要求重新啟動電腦 |
| `run` | `run name` | 執行指定的內建 Ring 3 原生範例 |
| `tasks` | `tasks` | 顯示工作 ID、狀態、切換次數與執行 tick |
| `uptime` | `uptime` | 顯示 PIT tick 及估算的運行秒數 |
| `yay` | `yay` | 顯示 Fluttershy 風格的小聲歡呼 |

範例：

```text
hoof> friendship
hoof> friendship party
hoof> colors
hoof> party
hoof> apps
hoof> run hello
hoof> meminfo
```

`apps` 目前列出 `hello`、`counter`、`probe`、`privileged`、`kernelread`、`kernelwrite`、`badflags`、`badstack`。其中部分為權限或例外狀況測試程式，**不應視為可任意使用的一般應用程式**。此外，`help`／`clear` 並非保證可用的別名；目前註冊的指令是 `friendship`／`rainboom`。

## 主要目錄

```text
boot/                 Limine 設定及連結器腳本
include/kernseed/     沿用的核心、終端機與 Shell 介面
include/Pony/         小馬像素圖資源定義（包含 Evan）
kernel/               核心、驅動程式、中斷、記憶體及排程等
shell/commands/       透過註冊巨集加入的 Shell 指令
apps/                 內建 Ring 3 示範程式
scripts/              相依項目取得與 QEMU 啟動腳本
tests/                主機端與系統層級測試
Makefile              建置、ISO、執行、測試入口
```

Shell 利用 `REGISTER_COMMAND(...)` 註冊指令，而 Makefile 會收集 `shell/commands/*.c`。一般新增指令無須重寫指令分派器。

## 已知限制與注意事項

- **實驗性系統**：不保證正式環境所需的穩定性、安全性、硬體相容性或資料持久性。
- 文字顯示仍以 **ASCII 為主**，尚非完整的 UTF-8／Unicode 或中文終端機。
- 目前 16 色主要控制**前景文字色彩**；完整 ANSI 跳脫序列解析和任意背景色尚未確認完成。
- 色彩具有持續狀態，主題指令可能使下一個 `hoof>` 提示符號繼承顏色；目前視為實驗性行為。
- Evan 頭像直接繪製在 Framebuffer 上，執行 `rainboom` 或大量文字捲動後可能消失或被覆蓋。
- 沒有通用 ELF 載入器或成熟的軟體生態；內建應用程式名稱固定。
- `reboot` 依賴 i8042 裝置，在部分環境可能無法成功。
- `rainboom` 的實際實作不接受引數，但原始碼的用法字串可能仍顯示 `rainboom [arg]`。
- `include/kernseed/`、`KERNSEED_*`、`kernseed.elf`、`kernseed.iso` 等名稱保留作為內部相容識別，**不要只修改其中一處**。

## 未來方向（尚未承諾完成）

- 改善像素頭像定位、解析度適配與繪圖測試。
- 使顏色狀態可控，逐步研究背景顏色與 ANSI 支援。
- 增加原創小馬圖像和互動指令；如 `pony`，應等實際完成後才列入功能清單。
- 待終端機架構更完善，再研究 Unicode 和繁／簡中文顯示。

## 參與與回饋

歡迎透過儲存庫的 GitHub 功能（開放時）提供可重現的錯誤回報、QEMU 日誌、小範圍修補或文件建議。請附上版本、建置設定、觸發指令及重現步驟。本專案由個人在閒暇時間維護，不承諾固定更新或支援時程。

## 授權與同人聲明

本儲存庫自身原始碼使用 **[PolyForm Noncommercial 1.0.0](LICENSE)**，並受各檔案著作權聲明及繼承程式碼義務約束。**這是限制商業使用的原始碼可見授權，不是 OSI 認可的開放原始碼授權。** Limine 與其他第三方元件的通知請見 [THIRD_PARTY_LICENSES.md](THIRD_PARTY_LICENSES.md)。本專案授權不會自動授予第三方角色、美術、商標或媒體內容之使用權。

《My Little Pony》及相關著作權和商標歸各自權利人所有。HoofTTY 為非官方同人專案，Evan 是作者自行創作的角色頭像，不代表官方 MLP 作品。
