# Bill of materials — source it yourself

Everything you need to build the Polysim Base, grip and bracket without the kit. Back to the [manual](MANUAL.md).

> 📦 **Rather skip the sourcing?** The kit contains every part except the FDM prints. The boards come already programmed and the silicone boot is included.
>
> <a href="https://polysim.fr/products/polysim-base"><img src="images/buy-kit.svg" alt="Buy the Polysim Base kit on polysim.fr" width="236"></a>

## 1. Manufactured parts

| Part | Qty | Process | Source file |
|---|---|---|---|
| Base plates (left and right side plates, 2× cam plate, large, small, top, bottom and dummy plates) | 9 | Laser cutting, **5 mm stainless steel** | `hardware/DXF/Base plates/LASER - Export INOX 5mm.dxf` |
| Main shaft (grip mount) | 1 | **MJF / SLS** (PA12) | `hardware/STL/SLS printing for extra strength/SLS_3DPrint - main axis  -0.2mm + 0.1mm mjf.stl` |
| Support (PDF step 0) | 1 | SLS / MJF | `hardware/STL/Base/Others/SLS/fixation_pics.stl` |
| Grip top plate | 1 per grip | SLS / MJF (recommended) or FDM | `hardware/STL/SLS printing for extra strength/plate grip.stl` (FDM version: `Grip G1/plate.stl`) |
| Base printed parts (housing, supports, brakes, spacers, covers…) | see [manual §4.1](MANUAL.md#41-fdm-printed-parts) | FDM | `hardware/STL/Base/STEP_1` … `STEP_9` |
| Grip printed parts (body, linker, junction, PCB spacer) | see [manual §4.1](MANUAL.md#41-fdm-printed-parts) | FDM | `hardware/STL/Grip G1/` or `Grip G2/` |
| Silicone boot | 1 | Cast silicone (≈ 30 g) in a printed mould | Mould: `hardware/STEP/Solicon_mold.step` · boot shape: `hardware/STL/Base/Others/Silicon/rubber.stl` |
| Bracket plates P1 and P2 | 2 | Plasma or laser cutting, **5 mm steel**, then bending | `hardware/DXF/Bracket/PLASMA Export dxf P1 5mm.dxf`, `P2` |
| Steel tube Ø10 mm and steel rod Ø8 mm | 2 + 2 | Cut to length (take the lengths from `Base.step`) | — |
| Electronic boards: base controller, encoder X, encoder Y, grip | 4 | PCB with SMT assembly | Not included in this repository (see [manual §5](MANUAL.md#5-electronics)) |

## 2. Base hardware

These totals are summed from the per-step lists of the assembly guide (PDF steps 0–9). Screws are DIN 912 socket head cap screws, A2 stainless, unless noted. The visible top-cover and boot screws are black steel (12.9) in the original build. Fasteners are cheap and usually sold in packs of 50–200, so buy a few spares.

| Item | Qty |
|---|---|
| M3×4 | 2 |
| M3×8 | 11 |
| M3×10 | 1 |
| M3×14 | 8 |
| M4×6 (or M4×8), black | 5 |
| M4×10 | 3 |
| M4×12 | 1 |
| M4×18 (two of them may be M4×20) | 3 |
| M4×25 (black for the top cover) | 12 |
| M4×30 | 11 |
| M4×60 | 2 |
| M8×90 button head screw (ISO 7380, class 10.9) | 4 |
| Heat-set insert M3 (Ruthex M3 "short", 4 mm) | 13 |
| Heat-set insert M4 (Ruthex M4 "short", 4 mm) | 4 |
| Square nut M3 | 1 |
| Square nut M4 (7×7×2.2 mm) | 6 |
| Barrel nut M4 | 2 |
| Nylon washer M3 | 11 |
| Nylon washer M4 | 4 |
| Shaft retaining ring Ø8 mm (2 used as circlips in PDF step 1, 2 as brake rings in PDF steps 3–4) | 4 |
| Ball bearing 604ZZ (4×12×4 mm) | 6 |
| Ball bearing 685-2RS (5×11×5 mm) | 2 |
| Ball bearing 688ZZ, thin (8×16×4 mm) | 4 |
| Ball bearing 61803-2RS (17×26×5 mm) | 3 |
| Compression spring, Ø12 mm outer diameter (yellow die-spring type) | 2 |
| Felt pad (brakes) | 2 |
| Neodymium disc magnet **5×2 mm, diametrically magnetised** | 2 |
| 4-pole jack socket, female (grip connector) | 1 |
| JST PH 4-pin cable (encoder cables) | 3 |
| USB-C to USB-A data cable, 2 m | 1 |

> The original purchasing spreadsheet lists slightly different quantities for a few items (for example four 61803 bearings). If a count looks wrong during assembly, check `Base.step`.

## 3. Grip hardware (per grip)

| Item | Qty |
|---|---|
| M1.6×4 | 2 |
| M3×6 | 4 |
| M3×8 | 2 |
| M3×10 (PCB mounting) | 2 |
| M3×20 | 4 |
| Heat-set insert M3 (short) | 12 |
| Nylon washer M3 | 2 |
| 16 mm round momentary push button with LED (NO/NC contacts) | 1 |
| Analog mini-stick, console-controller type, 5-pin FPC (0.5 mm pitch) | 1 |
| 4-pole jack plug, male | 1 |
| JST PH 4-pin cable | 1 |
| Grip PCB | 1 |

## 4. Bracket hardware

| Item | Qty |
|---|---|
| Toggle clamp (Bessey STC-IHH25 or equivalent) | 1 |
| M6×8, black | 4 |
| M6×12, black (14 mm maximum) | 2 |
| Bracket plates P1 and P2 | 2 |

## 5. Extra tools when sourcing yourself

- **Programming:** an ISP programmer (USBasp, or an Arduino Uno as *Arduino as ISP*) with a 6-pin cable, plus the Arduino IDE or PlatformIO. See [manual §6](MANUAL.md#6-programming-the-boards).
- **Silicone boot:** two-part casting silicone, mixing cups and the printed mould. See [manual §4.5](MANUAL.md#45-silicone-boot).

## 6. Indicative cost

At the author's 2024–2025 bulk purchase prices, the material cost was about **€111 for the base** (including the stainless plates, SLS shaft, bearings and electronic components), **€16 for a grip** (excluding filament) and **€27 for the bracket** (mostly the toggle clamp, excluding the steel plates). A one-off build costs more because of minimum order quantities, shipping and PCB assembly fees.
