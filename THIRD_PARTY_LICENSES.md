# Third-party notices

HoofTTY 是基于 Kernseed OS 的派生项目。本仓库的项目自有代码（包括继承的 Kernseed
代码）采用 GNU GPL 第 3 版或由您选择的任何后续版本（`GPL-3.0-or-later`）。
允许商业与非商业使用、修改和再分发，但必须遵守 GPL。以下第三方组件保留原许可，
本次迁移不重新许可这些组件，也不改变其版权通知。工具只用于构建或测试，不链接进内核。

## Limine bootloader

- 来源：https://github.com/limine-bootloader/limine
- 固定提交：`aad3edd370955449717a334f0289dee10e2c5f01`（`v8.x-binary`）
- BIOS/UEFI 引导二进制、安装工具：BSD 2-Clause，完整通知见
  [third_party/limine/LICENSE](third_party/limine/LICENSE)。
- `limine.h`：BSD Zero Clause，完整通知保留在该头文件开头。
- 镜像带有 `LIMINE-LICENSE`；不修改第三方二进制。
- BSD 许可允许商业与非商业使用和再分发；再分发仍须保留原通知。
- 构建前核对固定 Git 提交与 `third_party/limine/SHA256SUMS`。
  哈希记录从 HTTPS 官方仓库获取的文件身份，不代表独立代码审计或上游签名。

## GPL license text and historical licenses

根目录 [LICENSE](LICENSE) 是 GNU GPLv3 正式完整文本，未改写正文。
项目选择 GPLv3 **或后续版本**，由源码 SPDX 和 README 的授权声明确定；
GPLv3 正文中的示例不是对项目的单独版本限制。

- GNU 正式页面：https://www.gnu.org/licenses/gpl-3.0.html
- 本次取得的原样文本：https://raw.githubusercontent.com/gcc-mirror/gcc/master/COPYING3
  （GNU GCC 的官方 GitHub 镜像；保留该正式文本的原有 HTTP 链接）。
- 本次迁移不撤销历史 Release 已授予的许可，也不删除历史 Release、Tag 或 Git 记录。
- [旧 PolyForm 正文](docs/licenses/PolyForm-Noncommercial-1.0.0.md) 仅为历史存档，
  不作为当前项目自有代码的授权声明。其原始来源为
  https://github.com/polyformproject/polyform-licenses/blob/76a278c402bc43b8d2b561da140b0f3e17263015/PolyForm-Noncommercial-1.0.0.md 。
- 版权、来源核查与迁移范围见 [迁移记录](docs/license-migration.md)。

## Development tools (not included in the boot image)

- GCC / GNU Binutils / Make / GDB：GNU 工具，各自保留其 GPL 等许可。
- QEMU / SeaBIOS：仅作为模拟器与固件运行，不作为内核实现使用。
- xorriso / libisoburn：创建 ISO，不链接进内核。
- Python 3：执行宿主测试。

工作区内安装的 Debian 软件包含各自 `/usr/share/doc/*/copyright`；
它们不随本仓库源码或 HoofTTY ISO 再分发。内核字体由本项目自行绘制，无外部字体依赖。
