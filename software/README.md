# Software

| Folder | Content |
|---|---|
| [`installer/`](installer/) | `Polysim_0_1.exe`: Windows x64 installer for the Polysim configuration software (calibration, live view, firmware update) |
| [`firmware/base/`](firmware/base/) | Base firmware for the ATmega32U4: a PlatformIO project, plus a prebuilt `polysim_base_v0.0.4.hex` |
| [`firmware/grip/`](firmware/grip/) | Grip firmware for the ATmega328P: an Arduino sketch |

## Configuration software

1. Run `installer/Polysim_0_1.exe` on Windows 10 or 11 (64-bit). The installer is not code-signed, so Windows SmartScreen may ask for confirmation (**More info → Run anyway**).
2. Plug in the base. Its tile turns green.
3. Open **Configure** under **Base** or **Grip** and follow the calibration wizard.

Full instructions are in the [manual, §8](../doc/MANUAL.md#8-configuration-software).

## Firmware

A new board must first be programmed through its ICSP header with an ISP programmer. After that, the base can be updated over USB, either from the configuration software or from PlatformIO. The step-by-step procedure is in the [manual, §6](../doc/MANUAL.md#6-programming-the-boards).

| Firmware | MCU | Tool | Version |
|---|---|---|---|
| Base | ATmega32U4, 16 MHz, Caterina bootloader | PlatformIO (`board = polysim_base`) | 0.0.4 |
| Grip | ATmega328P, 16 MHz | Arduino IDE (board *Arduino Nano*), *Upload Using Programmer* | — |
