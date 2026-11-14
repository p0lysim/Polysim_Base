# Hardware

Mechanical files for the Polysim Base, grips G1/G2 and desk bracket. The [build manual](../doc/MANUAL.md) explains how to manufacture and assemble each part.

| Folder | Content | Used for |
|---|---|---|
| [`STL/`](STL/) | 3D-printable parts. `Base/STEP_1`…`STEP_9` are grouped by assembly stage. `Grip G1/` and `Grip G2/` hold the grip parts. `SLS printing for extra strength/` holds the parts to order in MJF/SLS. `assembly/` holds full assemblies for visualisation only. | FDM printing, SLS/MJF orders |
| [`DXF/`](DXF/) | `Base plates/` has the nine base plates (5 mm stainless steel, laser cutting). `Bracket/` has the two bracket plates (5 mm steel, plasma cutting and bending), with PNG previews of the bend lines. | Metal cutting services |
| [`STEP/`](STEP/) | `Base.step`, `Grip G1.step`, `Grip G2.step`, `Bracket.step` and `Solicon_mold.step` (silicone-boot mould). | Viewing, measuring, modifying in any CAD tool |
| [`3MF/`](3MF/) | `Bambulab P2S PLA.3mf`: print-ready Bambu Studio project with print settings for the Bambu Lab P2S in PLA (5 plates). | Direct printing |

The main shaft takes all the loads from the grip. Order it in **MJF/SLS (PA12)**, using `STL/SLS printing for extra strength/SLS_3DPrint - main axis  -0.2mm + 0.1mm mjf.stl`. Do not print it in FDM.
