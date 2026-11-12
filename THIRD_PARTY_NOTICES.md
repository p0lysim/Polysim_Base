# Third-party notices

Polysim uses the following third-party components. Each one remains under its own license.

## Base firmware (`software/firmware/base`)

| Component | Author | License | Notes |
|---|---|---|---|
| [ArduinoJoystickLibrary](https://github.com/MHeironimus/ArduinoJoystickLibrary) 2.1.1 | Matthew Heironimus | LGPL-3.0 | Included unmodified in `lib/ArduinoJoystickLibrary/`, with its `LICENSE` file |
| Arduino AVR core, `Wire`, `EEPROM`, USB core | Arduino | LGPL-2.1 | Linked at build time (PlatformIO `atmelavr` platform) |

The Caterina bootloader burned in §6.2 of the manual comes with the Arduino IDE. It is not distributed in this repository.

## Grip firmware (`software/firmware/grip`)

| Component | Author | License |
|---|---|---|
| Arduino AVR core, `Wire` | Arduino | LGPL-2.1 |

## Configuration software (`software/installer/Polysim_0_1.exe`)

The installer bundles the following components:

| Component | License |
|---|---|
| .NET 8 runtime (self-contained) | MIT |
| [Avalonia UI](https://github.com/AvaloniaUI/Avalonia) 11.0.10 | MIT |
| Inter font (via Avalonia.Fonts.Inter) | SIL Open Font License 1.1 |
| [HidSharp](https://www.zer7.com/software/hidsharp) 2.1.0 | Apache-2.0 |
| [ArduinoUploader](https://github.com/twinearthsoftware/ArduinoSketchUploader) 3.2.0 | MIT |
| IntelHexFormatReader 2.2.3 | MIT |
| [Newtonsoft.Json](https://www.newtonsoft.com/json) 13.0.3 | MIT |
| System.IO.Ports, System.Management 8.0.0 | MIT |
| SharpDX.DirectInput 4.2.0 | MIT |

The installer itself was built with [Inno Setup](https://jrsoftware.org/isinfo.php).

The full license texts are available from each project's website or repository.
