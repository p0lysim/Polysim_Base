# Polysim Base firmware

Firmware for the base controller (ATmega32U4). It reads the two AS5600 magnetic sensors and the grip over I²C, through a PCA9548A multiplexer, and presents itself to the PC as a USB HID joystick named **Polysim Base**. It also answers the configuration software over a USB virtual serial port.

| | |
|---|---|
| Version | 0.0.4 (`src/Version.h`) |
| Platform | PlatformIO, `atmelavr`, Arduino framework |
| Board definition | `boards/polysim_base.json` (Arduino Micro variant, custom USB identity) |
| Dependencies | `Wire`, and [ArduinoJoystickLibrary](https://github.com/MHeironimus/ArduinoJoystickLibrary), already included in `lib/` (LGPL-3.0) |
| Prebuilt binary | `prebuilt/polysim_base_v0.0.4.hex` |

## Build and flash

```bash
pio run                # build → .pio/build/micro/firmware.hex
pio run -t upload      # flash over USB (requires the Caterina bootloader)
```

The prebuilt hex can also be flashed with avrdude. Press reset first to enter the bootloader:

```bash
avrdude -p atmega32u4 -c avr109 -P COM5 -b 57600 -D -U flash:w:prebuilt/polysim_base_v0.0.4.hex:i
```

A blank ATmega32U4 needs the bootloader burned once over ICSP first. See the [manual, §6.2](../../../doc/MANUAL.md#62-base-board-atmega32u4).

## Source layout

| File | Role |
|---|---|
| `src/main.cpp` | Setup, main loop and HID joystick declaration (X, Y, Rx, Ry, 32 buttons) |
| `src/AS5600.*` | Magnetic sensor driver: angles, ZPOS/MPOS calibration, EEPROM save and restore |
| `src/Grip.*` | Grip driver (I²C master): buttons, mini-stick, calibration |
| `src/I2C_Manager.*` | Multiplexer channel selection and register access |
| `src/SerialPortComManager.*` | Serial command interpreter used by the configuration software |

The serial protocol, I²C registers and EEPROM map are documented in the [manual, §12](../../../doc/MANUAL.md#12-technical-reference).
