# Question 3.c

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
[       1]  0x00000000
[       2]  0x00000000
[       3]  0x8000000c
[       4]  0x80000009
[       5]  0x00000000
[       6]  0x8000001d
[       7]  0x80000013
[       8]  0x00000000
[       9]  0x8000001f
[      10]  0x8000001c
[      11]  0x00000000
[      12]  0x8000000f
[      13]  0x00000000
[      14]  0x00000000
[      15]  0x80000008
```

Decoding just the **valid** entries (top bit set):

| VPN | Entry | Valid? | PFN |
|---|---|---|---|
| 0 | `0x80000018` | Yes | 24 |
| 3 | `0x8000000c` | Yes | 12 |
| 4 | `0x80000009` | Yes | 9 |
| 6 | `0x8000001d` | Yes | 29 |
| 7 | `0x80000013` | Yes | 19 |
| 9 | `0x8000001f` | Yes | 31 |
| 10 | `0x8000001c` | Yes | 28 |
| 12 | `0x8000000f` | Yes | 15 |
| 15 | `0x80000008` | Yes | 8 |

All other VPNs (1, 2, 5, 8, 11, 13, 14) are invalid.

## Answer: Virtual Address Trace

Page size is 1 KB, so for each address: `VPN = address / 1024`, `offset = address % 1024`. Physical address (when valid) = `(PFN &times; 1024) + offset`.

| Virtual Address (hex) | Decimal | VPN | Offset | PTE valid? | Result |
|---|---|---|---|---|---|
| `0x00003385` | 13189 | 12 | 901 | Yes (PFN 15) | **PA = 16261 (0x3F85)** |
| `0x0000231d` | 8989 | 8 | 797 | No | **Invalid / segfault** |
| `0x000000e6` | 230 | 0 | 230 | Yes (PFN 24) | **PA = 24806 (0x60E6)** |
| `0x00002e0f` | 11791 | 11 | 527 | No | **Invalid / segfault** |
| `0x00001986` | 6534 | 6 | 390 | Yes (PFN 29) | **PA = 30086 (0x7586)** |

**Three of the five addresses succeed this time.** Worked examples:
- `0x00003385` → VPN 12 → PFN 15 → `(15 &times; 1024) + 901 = 15360 + 901 = 16261` (`0x3C00 | 0x385 = 0x3F85`)
- `0x000000e6` → VPN 0, offset 230 (small enough that VPN is 0 and the whole address *is* the offset) → PFN 24 → `(24 &times; 1024) + 230 = 24576 + 230 = 24806` (`0x6000 | 0xE6 = 0x60E6`)
- `0x00001986` → VPN 6 → PFN 29 → `(29 &times; 1024) + 390 = 29696 + 390 = 30086` (`0x7400 | 0x186 = 0x7586`)

The two failures (VPN 8 and VPN 11) both fall on entries whose valid bit is `0`, same failure mode as the earlier traces — again, not because the VPN was out of range, but because that specific page was never mapped.
