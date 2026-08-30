# Question 3.d

## Setup

```
ARG seed              0
ARG address space size 16k
ARG phys mem size      32k
ARG page size          1k
ARG verbose            True
ARG addresses          -1
```

**Page table entry format:** the high-order (left-most) bit is the **VALID** bit.
- If that bit is `1`, the rest of the entry is the **PFN**.
- If that bit is `0`, the page is not valid (unmapped).

**Page table size:** `16 KB / 1 KB = 16` entries — indices `0` through `15`.
**Physical memory size:** `32 KB / 1 KB = 32` physical frames (PFN range 0&ndash;31).

**Page table contents:**

```
[       0]  0x80000018
[       1]  0x80000008
[       2]  0x8000000c
[       3]  0x80000009
[       4]  0x80000012
[       5]  0x80000010
[       6]  0x8000001f
[       7]  0x8000001c
[       8]  0x80000017
[       9]  0x80000015
[      10]  0x80000003
[      11]  0x80000013
[      12]  0x8000001e
[      13]  0x8000001b
[      14]  0x80000019
[      15]  0x80000000
```

**Every single entry is valid this time** — all 16 VPNs are mapped:

| VPN | PFN | | VPN | PFN |
|---|---|---|---|---|
| 0 | 24 | | 8 | 23 |
| 1 | 8 | | 9 | 21 |
| 2 | 12 | | 10 | 3 |
| 3 | 9 | | 11 | 19 |
| 4 | 18 | | 12 | 30 |
| 5 | 16 | | 13 | 27 |
| 6 | 31 | | 14 | 25 |
| 7 | 28 | | 15 | 0 |

## Answer: Virtual Address Trace

Page size is 1 KB, so for each address: `VPN = address / 1024`, `offset = address % 1024`. Physical address = `(PFN &times; 1024) + offset`. Since every entry is valid, **all five addresses translate successfully.**

| Virtual Address (hex) | Decimal | VPN | Offset | PFN | Physical Address |
|---|---|---|---|---|---|
| `0x00002e0f` | 11791 | 11 | 527 | 19 | **19983 (0x4E0F)** |
| `0x00001986` | 6534 | 6 | 390 | 31 | **32134 (0x7D86)** |
| `0x000034ca` | 13514 | 13 | 202 | 27 | **27850 (0x6CCA)** |
| `0x00002ac3` | 10947 | 10 | 707 | 3 | **3779 (0x0EC3)** |
| `0x00000012` | 18 | 0 | 18 | 24 | **24594 (0x6012)** |

Worked examples:
- `0x00002e0f` → VPN 11 → PFN 19 → `(19 &times; 1024) + 527 = 19456 + 527 = 19983` (`0x4C00 | 0x20F = 0x4E0F`)
- `0x00001986` → VPN 6 → PFN 31 → `(31 &times; 1024) + 390 = 31744 + 390 = 32134` (`0x7C00 | 0x186 = 0x7D86`)
- `0x00000012` → VPN 0, offset 18 (address is small enough that it's entirely within page 0) → PFN 24 → `(24 &times; 1024) + 18 = 24576 + 18 = 24594` (`0x6000 | 0x12 = 0x6012`)

**Note the sanity check:** the largest computed physical address here (32134) is still comfortably within the 32 KB physical memory (max valid PA = 32767), so none of these translations exceed physical memory bounds either — every failure mode from the earlier questions (3.a&ndash;3.c) is absent here since the table is fully populated.
