# HoofTTY GPL-3.0-or-later 迁移记录

本次仅处理 Evan-Windproof/HoofTTY，不修改或提交 Kernseed_OS 仓库。
基线为 `7bb92cc396dcfdfa77bc635bf43e990180cafab2`；开始时工作区干净，
本地分支为 `work`，远端 `main` 与该基线一致。迁移在独立分支
`chore/relicense-gpl-3-or-later` 上进行，不重写历史。

## 版权、来源与范围

依据维护者本次重新许可指令，检查了非浅克隆的完整 37 个提交、作者统计、
提交消息和当前源文件。记录的作者为 Evan Windproof / Evan-Windproof，
使用 `wangxikai2012@outlook.com` 与 `wangxikai2012@gmail.com`；未发现其他
贡献者署名或 Co-authored-by 声明。继承的 Kernseed 代码在本仓库历史中可追溯至
同一作者的 Phase 1–7 提交，而非仅凭旧 PolyForm 授权推定有重新许可权。
这项核查基于仓库内可见记录，不代表对仓库外权属资料的独立认证。

原本缺少 SPDX 的文件已逐项追溯：

| 文件 | 首次引入提交 | 可见来源证据 |
| --- | --- | --- |
| `boot/limine.conf`、`scripts/debug.gdb` | `b5a108d` | Evan Windproof，Kernseed Phase 1 的项目配置与调试脚本 |
| `apps/linker.ld` | `fb98c9d` | Evan Windproof，Phase 6 内置应用链接脚本 |
| `shell/commands/party.c`、`shell/commands/yay.c` | `8804b1e` | Evan-Windproof，HoofTTY 主题命令 |
| `include/Pony/evan.h`、`include/Pony/pony_types.h` | `a5e0e7c` | Evan-Windproof；三语 README 将 Evan 明确说明为作者原创头像 |

Framebuffer 字体源注释及第三方通知均说明为项目原创，无外部字体依赖。
上述文件在核查来源后才补充 GPL-3.0-or-later SPDX，不新增或覆盖 Copyright。
未发现需要停止重新许可的其他项目源码；第三方内容始终排除在重新许可范围外。
My Little Pony、Hasbro 等第三方角色、美术、商标及媒体权利没有通过本次迁移授予。

## 第三方保护与历史

`third_party/limine/` 全部文件与基线逐字节一致：
`LICENSE` 保持 BSD-2-Clause，`limine.h` 保持其 BSD Zero Clause（0BSD）许可，
`SHA256SUMS` 未变。构建脚本继续验证固定 Limine 提交和文件哈希。
`THIRD_PARTY_LICENSES.md` 区分本项目 GPL 授权、Limine 原许可与开发工具许可。

根目录 LICENSE 为 GNU GCC 官方 GitHub 镜像的完整 `COPYING3` 原文：
https://raw.githubusercontent.com/gcc-mirror/gcc/master/COPYING3

- 674 行，35147 字节。
- SHA-256：`8ceb4b9ee5adedde47b31e975c1d90c73ad27b6b165a1dcd80c7c545eb65b903`。
- GNU 官网下载在本环境返回 HTTP 403，因此使用上述官方镜像的正式文本。
- 与 Debian `/usr/share/common-licenses/GPL-3` 对比，差异仅为 FSF/GNU 链接的
  HTTP/HTTPS 和末尾 why-not-lgpl 链接路径；保留取得的原文，不编辑许可证。
- GPLv3 或后续版本的选择由项目 README 与 `GPL-3.0-or-later` SPDX 明确授予。

旧 LICENSE 原样保存在 `docs/licenses/PolyForm-Noncommercial-1.0.0.md`。
历史报告中 PolyForm 记载保留并标明其历史性质，原始测试日志、Tag、Release 和
Git 历史不修改；此次提交不撤销历史版本已经授予的许可。

## 验证结果

迁移前后均通过：

- `make -j4 iso check build/runtime-test build/framebuffer-test build/memory-span-test`。
- 三个宿主测试：runtime（12464 个 memmove 用例）、framebuffer（含 11 类无效布局）、memory-span。
- 迁移后 QEMU TCG 冷启动及真实 QMP 键盘输入：about、friendship、echo、apps、
  meminfo、uptime、run hello；Ring 3 输出 `Hello from HoofTTY userspace!`，无 PANIC。
  功能验证使用环境中保留的 `/workspace/.hooftty-tools/smoke.py`，不加入项目测试。
- 82 个项目源码、构建及脚本文件均为 GPL-3.0-or-later。逐文件去除 SPDX 注释后，
  与基线内容一致，唯一额外差异是 about 中的授权字符串；无内核或程序逻辑变化。
- LICENSE 与下载原文一致；旧 LICENSE 存档与基线一致；所有第三方文件、`.gitignore` 未变。
- 英文、简体、繁体 README 的版本选择、商业使用、第三方和历史授权说明一致。
- 当前授权中不再使用 PolyForm，剩余引用仅为历史记录与迁移说明。
- `git diff --check` 通过；`build/`、`.cache/`、`config.local.mk` 继续被忽略。

已存在的失败：迁移前 `make test-host` 因 Makefile 引用不存在的
`shell/commands/help.c` 失败；迁移后 `make test` 在相同依赖处停止，
因此完整系统回归没有执行。tests/shell.c 仍期待旧 help 命令，部分系统测试
仍期待 `ks>`。本任务未为修复这些问题而改变逻辑或测试断言。
UEFI、图形界面、实机以及其余发布级回归未执行。

## 修改文件清单

以下包含许可证、三语文档、开发文档示例、历史说明及 SPDX 注释变更。

- `LICENSE`
- `Makefile`
- `README.md`
- `README.zh-CN.md`
- `README.zh-TW.md`
- `THIRD_PARTY_LICENSES.md`
- `apps/abi.h`
- `apps/badflags.c`
- `apps/badstack.c`
- `apps/counter.c`
- `apps/hello.c`
- `apps/kernelread.c`
- `apps/kernelwrite.c`
- `apps/linker.ld`
- `apps/privileged.c`
- `apps/probe.c`
- `boot/limine.conf`
- `boot/linker.ld`
- `docs/app-development.md`
- `docs/en/app-development.md`
- `docs/known-limitations.md`
- `docs/license-migration.md`
- `docs/licenses/PolyForm-Noncommercial-1.0.0.md`
- `docs/release-readiness.md`
- `docs/reports/phase-1.md`
- `docs/reports/phase-2.md`
- `docs/shell-development.md`
- `docs/zh-CN/app-development.md`
- `include/Pony/evan.h`
- `include/Pony/pony_types.h`
- `include/kernseed/api.h`
- `include/kernseed/boot.h`
- `include/kernseed/console.h`
- `include/kernseed/interrupts.h`
- `include/kernseed/io.h`
- `include/kernseed/keyboard.h`
- `include/kernseed/memory.h`
- `include/kernseed/runtime.h`
- `include/kernseed/scheduler.h`
- `include/kernseed/shell.h`
- `include/kernseed/terminal.h`
- `include/kernseed/user.h`
- `kernel/arch/x86_64/counter-tasks.S`
- `kernel/arch/x86_64/entry.S`
- `kernel/arch/x86_64/gdt-load.S`
- `kernel/arch/x86_64/gdt.c`
- `kernel/arch/x86_64/interrupt-probe.S`
- `kernel/arch/x86_64/isr-common.S`
- `kernel/arch/x86_64/user-enter.S`
- `kernel/core/api.c`
- `kernel/core/console.c`
- `kernel/core/main.c`
- `kernel/core/runtime.c`
- `kernel/core/terminal.c`
- `kernel/drivers/framebuffer.c`
- `kernel/drivers/keyboard.c`
- `kernel/drivers/serial.c`
- `kernel/interrupts/interrupts.c`
- `kernel/memory/memory.c`
- `kernel/memory/span.c`
- `kernel/scheduler/scheduler.c`
- `kernel/syscall/user.c`
- `scripts/check-reproducible.sh`
- `scripts/debug.gdb`
- `scripts/fetch-limine.sh`
- `scripts/gen-isr.py`
- `scripts/run.sh`
- `scripts/setup-host.sh`
- `shell/commands/about.c`
- `shell/commands/apps.c`
- `shell/commands/colors.c`
- `shell/commands/echo.c`
- `shell/commands/friendship.c`
- `shell/commands/meminfo.c`
- `shell/commands/party.c`
- `shell/commands/rainboom.c`
- `shell/commands/reboot.c`
- `shell/commands/run.c`
- `shell/commands/tasks.c`
- `shell/commands/uptime.c`
- `shell/commands/yay.c`
- `shell/dispatch.c`
- `shell/parser.c`
- `shell/registry.c`
- `shell/shell.c`
- `tests/boot.py`
- `tests/check_elf.py`
- `tests/framebuffer.c`
- `tests/memory-span.c`
- `tests/phase2.py`
- `tests/phase3.py`
- `tests/phase4.py`
- `tests/phase5.py`
- `tests/phase6.py`
- `tests/phase7.py`
- `tests/runtime.c`
- `tests/shell.c`
