# HoofTTY 🐴

**An open-source, My Little Pony–inspired, text-based hobby operating system.**

> **Status: Early development** — HoofTTY is an experimental project. Its features, interfaces, and build instructions may change as development continues.
>
> **Language:** [English](#english) · [简体中文](#简体中文)

---

## English

### Overview

**HoofTTY** is an independent, text-based hobby operating system inspired by *My Little Pony*. Instead of relying on a conventional graphical desktop, the project explores how a recognizable theme and personality can be expressed through a terminal-style interface, shell commands, text, and ASCII art.

HoofTTY is being developed from **Kernseed OS Phase 7**, an earlier educational operating-system project. It is **not a Linux distribution, a terminal emulator, or simply a theme for an existing shell**. The goal is to evolve the existing OS codebase into a distinct, usable text-based system, while keeping the development process approachable and educational.

This is a fan-made, non-commercial project and is not affiliated with or endorsed by Hasbro.

### Project goals

- **Text-first experience:** Make the system's identity visible without requiring a graphical user interface.
- **Distinctive shell:** Gradually develop HoofTTY-specific commands, messages, and text-based interactions.
- **Original visual identity:** Explore ASCII art and other original terminal-friendly artwork inspired by the atmosphere of Equestria.
- **Learn by building:** Use real operating-system source code to study and improve low-level mechanisms.
- **Open development:** Share source code and document changes as the project grows.

These are **goals, not a list of completed features**.

### Current development status

HoofTTY development has begun with modifications to the existing Kernseed OS codebase, including early shell and welcome-text customization. It remains at a very early stage; many planned HoofTTY-specific features are not yet implemented.

| Area | Status |
| --- | --- |
| Starting codebase | Kernseed OS Phase 7 |
| HoofTTY branding / shell customization | In progress |
| HoofTTY-specific commands and interactions | Planned / evolving |
| Text-based themed presentation | Planned / evolving |
| Stable public release | Not yet available |

*This table is a high-level roadmap, not a claim of verified functionality. Check the source and commit history for the latest implementation details.*

### Building and running

HoofTTY is currently a source-first development project. The exact build requirements and commands depend on the checked-in code and toolchain.

If the repository retains the Kernseed-style Makefile target for creating a bootable image, the usual entry point is:

```sh
make iso
```

The command above is **conditional**: verify the available targets, prerequisites, and output location in the repository's `Makefile` before using it. An ISO image does not necessarily imply compatibility with every emulator or real machine. Any release-specific QEMU or VMware instructions should be documented and tested before publication.

For now, consult the repository's source files, build scripts, and commit history. Tested configurations and detailed steps will be added as they are confirmed.

### Relationship to Kernseed OS

HoofTTY is derived from the educational **Kernseed OS Phase 7** codebase. Kernseed serves as the technical foundation; HoofTTY is intended to become a separate project with its own identity and direction.

The original Kernseed copyright and licensing obligations continue to apply to any reused code. See the repository's license and source-file notices for the applicable terms.

### Contributions and feedback

The project is in an experimental stage. Technical feedback, bug reports, and thoughtful suggestions are welcome through GitHub Issues when they are enabled.

Please do not assume a particular feature is supported unless it appears in the source code or accompanying documentation.

### License and fan-project notice

**Code license:** See the repository's `LICENSE` file for the definitive licensing terms. **Before publishing the repository, confirm that this file exists and that the terms permit the intended use and redistribution of all inherited code.**

*My Little Pony* and related names and characters belong to their respective rights holders. HoofTTY is an unofficial fan project; it is not associated with, sponsored by, or endorsed by Hasbro. This notice does not grant rights to use third-party trademarks or copyrighted assets. The project aims to use original assets and avoid bundling unlicensed official media.

---

## 简体中文

### 项目简介

**HoofTTY** 是一款受《My Little Pony》（《小马宝莉》）启发的、以纯文本交互为核心的开源业余操作系统。

它不依赖传统图形桌面，而是尝试通过终端风格的界面、Shell 命令、文字以及 ASCII 艺术，让用户在纯文本环境中感受到鲜明的主题风格。

HoofTTY 基于此前的教学操作系统 **Kernseed OS Phase 7** 开发。它**不是 Linux 发行版、终端模拟器，也不是给现有 Shell 换一个主题**。项目希望逐步将现有的操作系统代码发展为具有独立特色、能够实际使用的纯文本系统，同时保留学习和研究底层技术的价值。

本项目是非商业的非官方同人创作，与 Hasbro 没有隶属、赞助或认可关系。

### 项目目标

- **纯文本优先：** 不依赖图形界面，也能展现系统的独特风格。
- **独立的 Shell 体验：** 逐步设计属于 HoofTTY 的命令、提示信息及文本交互。
- **原创视觉风格：** 探索 ASCII 艺术及其他适合纯文本环境的原创设计。
- **在实践中学习：** 通过阅读与修改真实操作系统源码，理解并改进底层机制。
- **开放开发：** 公开源码，持续记录系统的成长过程。

以上内容是**开发目标，并非已经完成的功能清单**。

### 当前开发状态

HoofTTY 已经开始在 Kernseed OS 的现有代码基础上进行修改，包括早期的 Shell 和欢迎文字定制。但项目仍处于初期阶段，大部分 HoofTTY 专属功能尚未完成。

| 项目 | 状态 |
| --- | --- |
| 起始代码基础 | Kernseed OS Phase 7 |
| HoofTTY 品牌与 Shell 定制 | 开发中 |
| 专属命令与交互 | 规划 / 逐步实现 |
| 纯文本主题展示 | 规划 / 逐步实现 |
| 稳定公开版本 | 尚未发布 |

*本表只展示整体方向，不代表功能已经通过验证。最新实现情况以仓库源码及提交记录为准。*

### 构建与运行

HoofTTY 当前以源码开发为主。具体构建依赖和命令需以仓库中的实际工具链及构建脚本为准。

如果项目仍保留 Kernseed 风格的 Makefile ISO 构建目标，通常可以使用：

```sh
make iso
```

**注意：** 上述命令以仓库实际存在对应目标为前提。执行前请查看 `Makefile`，确认依赖、输出路径及构建目标。生成 ISO 不代表它一定能在所有模拟器或实体设备上运行。待实际验证后，再补充 QEMU / VMware 的具体运行教程。

目前可先通过源码、构建脚本和 Git 提交记录了解项目。经过验证的环境与运行步骤会逐步补充。

### 与 Kernseed OS 的关系

HoofTTY 以教学项目 **Kernseed OS Phase 7** 为基础进行后续开发。Kernseed 提供技术起点，而 HoofTTY 将逐步形成独立的项目身份和开发方向。

对于继承的代码，仍需遵守 Kernseed 原有的版权及许可证要求。具体条款以仓库中的许可证文件及源代码版权声明为准。

### 参与与反馈

项目尚处于实验阶段。开放 GitHub Issues 后，欢迎提交技术建议、Bug 反馈与合理的功能构想。

对于某项功能是否已可使用，请以实际代码和文档为准。

### 许可证与同人声明

**代码许可证：** 请以仓库的 `LICENSE` 文件为准。**公开仓库前，务必确认该文件存在，并核实继承代码的许可证是否允许计划中的使用和分发方式。**

《My Little Pony》相关名称、角色及其他知识产权归各自权利人所有。HoofTTY 是非官方同人项目，不隶属于 Hasbro，也未获得其赞助或认可。本声明不代表自动取得使用第三方商标及版权素材的许可。项目将尽量采用原创素材，避免未经许可直接打包官方媒体资源。
