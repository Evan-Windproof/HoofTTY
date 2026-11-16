# HoofTTY

**Beta 0.3.0 · 受《My Little Pony》（小马宝莉）启发的 x86-64 纯文本优先业余操作系统。**

[English](README.md) · [简体中文](README.zh-CN.md) · [繁體中文](README.zh-TW.md)

> **开发状态：实验性 Beta。** HoofTTY 是基于 **Kernseed OS Phase 7** 演进的独立业余操作系统，并不是 Linux 发行版、现有 Shell 的主题或终端模拟器。请勿用于生产环境或存放重要数据。
>
> **许可提示：** 项目自有代码采用 **GNU GPL 第 3 版或后续版本（`GPL-3.0-or-later`）**。允许商业与非商业使用，但必须遵守 GPL；第三方组件保留原许可证，详情见文末。

## 项目介绍

HoofTTY 尝试在不依赖传统图形桌面的情况下，通过独立的 Shell、MLP 主题命令、彩色文字与像素艺术，让一个小型操作系统具有鲜明的“小马风格”。它不是单纯修改 Linux 终端的主题，而是在自己的内核与启动流程上进行开发。

项目继承了 **Kernseed OS Phase 7 的教学型 x86-64 宏内核基础**。为了避免破坏已经能够工作的构建路径，一部分内部标识仍保留为 `kernseed`，例如头文件目录、构建宏与 ISO/ELF 文件名；面向使用者的系统名称始终是 **HoofTTY**。

这是一项个人兴趣性质的同人项目，与 Hasbro 不存在隶属、赞助或官方认可关系。

## Beta 0.3.0 当前进度

| 组成 | 目前状况 |
| --- | --- |
| 启动 | 使用 Limine 引导；仓库提供 QEMU 运行脚本 |
| 内核 | 基于 Kernseed 的 x86-64 教学宏内核，保留中断、内存管理、调度和内置 Ring 3 示例 |
| 显示 | Framebuffer 终端，5×7 ASCII 位图字体经放大绘制，支持 **16 色前景文字** |
| 启动画面 | 彩色 HoofTTY 欢迎文字与实验性 Evan 像素头像（原始索引色尺寸 48×54） |
| Shell | `hoof>` 提示符、命令注册机制、有界参数解析及基础输入编辑 |
| MLP 主题 | 已加入 `friendship`、`party`、`rainboom`、`yay` 等命令 |
| 诊断信息 | 系统信息、内存页统计、任务状态、基于 PIT 的运行时间 |
| 程序 | 固定数量的内置 Ring 3 示例；**没有通用 ELF 程序加载器** |

**当前命令清单共有 13 条。** 早先讨论过的 `pony` 和隐藏命令 `Who's Evan?` 不在本版已实现命令列表中；启动时绘制 Evan 头像与实现这些命令是两回事。

## 构建与运行

### 环境要求

建议在 Linux 开发环境（包括装有所需软件的 WSL）中使用：

- 支持 x86-64 的 GCC、GNU binutils（`ld`、`objcopy`）、GNU Make、宿主机 C 编译器
- Python 3、Git、`sha256sum`、基础 POSIX Shell 工具以及 `xorriso`
- QEMU（`qemu-system-x86_64`），用于仓库自带的运行指令
- 首次获取依赖时需要网络：脚本会拉取固定提交版本的 Limine，并验证仓库记录的哈希

在**仓库根目录**执行：

```sh
git clone https://github.com/Evan-Windproof/HoofTTY.git
cd HoofTTY
make iso
make run
```

当前 Makefile 生成的 ISO 路径为 **`build/kernseed.iso`**。这是继承的内部文件名，**无需为了品牌统一而修改**。默认 QEMU 配置为 128 MiB 内存、单虚拟 CPU、标准 VGA。

开发者可用指令：

```sh
make test-host     # 宿主机单元测试
make check         # ELF 检查（必要时先构建）
make headless      # 无图形窗口，查看串口输出
make debug         # QEMU 暂停，GDB 监听 127.0.0.1:1234
make clean         # 删除构建产物
```

`make test` 会运行更完整的、多构建配置的测试流程，并可能改变当前构建配置，建议在发布前使用。此处说明的是仓库中的目标与脚本，并不意味着 Beta 0.3.0 的每个目标都已经实际测试。**开发期间已通过 QEMU 图形窗口验证；VMware 与实体机兼容性不作保证。**

## Shell 命令速查

进入系统后输入 `friendship` 可以列出命令；输入 `friendship colors` 等可以查看指定命令说明。命令名区分大小写。

| 命令 | 用法 | 功能 |
| --- | --- | --- |
| `about` | `about` | 显示系统信息、许可及部分实现限制 |
| `apps` | `apps` | 列出内置原生示例程序 |
| `colors` | `colors` | 演示终端 **16 色前景** 调色板 |
| `echo` | `echo [text ...]` | 输出解析后的参数，最多七个文本参数 |
| `friendship` | `friendship [command]` | 列出命令或查看某条命令的说明 |
| `meminfo` | `meminfo` | 查看物理内存页、页表等统计信息 |
| `party` | `party` | 输出 Pinkie Pie 风格的彩色派对信息 |
| `rainboom` | `rainboom` | 清空终端屏幕 |
| `reboot` | `reboot` | 通过 i8042 控制器请求重启电脑 |
| `run` | `run name` | 执行指定内置 Ring 3 原生示例程序 |
| `tasks` | `tasks` | 查看任务 ID、状态、切换次数与运行 tick |
| `uptime` | `uptime` | 查看 PIT tick 和估算的运行秒数 |
| `yay` | `yay` | 显示 Fluttershy 风格的小声欢呼 |

示例：

```text
hoof> friendship
hoof> friendship party
hoof> colors
hoof> party
hoof> apps
hoof> run hello
hoof> meminfo
```

`apps` 当前列出的程序包括 `hello`、`counter`、`probe`、`privileged`、`kernelread`、`kernelwrite`、`badflags`、`badstack`。其中部分属于权限或异常测试程序，**不要把它们当作可随意使用的通用应用**。另外，`help` / `clear` 不应被默认视为 `friendship` / `rainboom` 的可用别名：当前命令注册表使用的是后两者。

## 主要目录结构

```text
boot/                 Limine 配置和链接脚本
include/kernseed/     继承的内核、终端、Shell 接口
include/Pony/         小马像素资源定义（包含 Evan）
kernel/               内核核心、驱动、中断、内存、调度等
shell/commands/       通过注册宏加入的 Shell 命令
apps/                 内置 Ring 3 示例程序
scripts/              依赖下载及 QEMU 启动脚本
tests/                宿主机单测和系统级测试
Makefile              构建、ISO、运行、测试入口
```

Shell 使用 `REGISTER_COMMAND(...)` 注册命令，Makefile 会收集 `shell/commands/*.c`。一般新增命令无需重写命令分发器。

## 已知限制与注意事项

- **实验性系统**：不提供生产级稳定性、安全性、硬件兼容或数据持久化保证。
- 文字显示仍以 **ASCII 为主**，尚不是完整的 UTF-8/Unicode 或中文终端。
- 当前 16 色主要是**前景文字颜色**，完整 ANSI 转义解析与任意背景色尚未被确认为实现完成。
- 颜色具有持续状态，主题命令可能使下一次 `hoof>` 提示符继承颜色；目前将其视为实验性行为。
- Evan 头像直接绘制于 Framebuffer，`rainboom` 清屏或大量输出滚屏时可能消失或被覆盖。
- 不支持通用 ELF 加载及成熟软件生态；内置程序名称固定。
- `reboot` 依赖 i8042 设备，在部分环境下可能失败。
- `rainboom` 实际不接受参数，但其源码中的用法字符串可能仍写作 `rainboom [arg]`。
- `include/kernseed/`、`KERNSEED_*`、`kernseed.elf` 和 `kernseed.iso` 等名称保留作为内部兼容标识，**不要只改其中一处**。

## 后续方向（尚未承诺实现）

- 改善像素头像的布局、分辨率适配与绘图测试。
- 让颜色继承行为可控，逐步研究背景颜色与 ANSI 支持。
- 丰富原创小马资源和互动指令；`pony` 等需实际实现后再列入功能。
- 在终端基础完善之后，再考虑 Unicode 与简繁中文显示。

## 反馈与参与

欢迎在仓库对应的 GitHub 页面（功能开放时）提交能够复现的错误报告、QEMU 日志、小范围补丁或文档建议。提交问题时请注明版本、构建配置、触发命令及复现步骤。本项目由个人在兴趣时间维护，不承诺固定更新或支持周期。

## 许可证与同人声明

本仓库自有代码（包括继承的 Kernseed 代码）采用 **GNU GPL 第 3 版或由您选择的任何后续版本（`GPL-3.0-or-later`）**。允许商业与非商业使用、修改和再分发，但必须遵守 GPL；正式 GPLv3 全文见 [LICENSE](LICENSE)。HoofTTY 是基于 [Kernseed OS](https://github.com/Evan-Windproof/Kernseed_OS) 的派生项目。第三方组件保留原许可证，详情见 [THIRD_PARTY_LICENSES.md](THIRD_PARTY_LICENSES.md)。本次变更不会撤销历史 Release 已授予的许可，历史版本仍应按其原有声明和条款使用；旧 PolyForm 文本保留为[历史记录](docs/licenses/PolyForm-Noncommercial-1.0.0.md)。仓库许可不自动授权第三方角色、美术、商标和媒体素材。

《My Little Pony》及相关知识产权归各自权利人所有。HoofTTY 是非官方同人项目，Evan 是项目作者的原创角色头像，不代表官方 MLP 作品。
