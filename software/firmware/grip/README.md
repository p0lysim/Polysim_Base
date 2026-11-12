# Polysim Grip firmware

Firmware for the grip board (ATmega328P, 16 MHz, Arduino Nano compatible). The grip is an **I²C slave at address `0x55`**. It reads the push button, the mini-stick click and the two mini-stick axes, and returns them to the base on request.

| Pin | Function |
|---|---|
| A0 | Main push button (input with pull-up) |
| A1 | Mini-stick click (input with pull-up) |
| A2 / A3 | Mini-stick X / Y |
| A4 / A5 | SDA / SCL |
| D2 | LED |

## Flash

The grip board has no USB port, so it is programmed through its ICSP header:

1. Open `polysim_grip/polysim_grip.ino` in the Arduino IDE.
2. Select **Board → Arduino Nano**, **Processor → ATmega328P**, and your ISP programmer.
3. On a new chip, run **Tools → Burn Bootloader** once to set the fuses.
4. Run **Sketch → Upload Using Programmer**.

The register map, which is useful for designing your own grip, is in the [manual, §12.3](../../../doc/MANUAL.md#123-grip-protocol-build-your-own-grip).
