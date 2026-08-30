# Question 3.b

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
[       3]  0x00000000
[       4]  0x00000000
[       5]  0x80000009
[       6]  0x00000000
[       7]  0x00000000
[       8]  0x80000010
[       9]  0x00000000
[      10]  0x80000013
[      11]  0x00000000
[      12]  0x8000001f
[      13]  0x8000001c
[      14]  0x00000000
[      15]  0x00000000
```

Decoding just the **valid** entries (top bit set):

| VPN | Entry | Valid? | PFN |
|---|---|---|---|
| 0 | `0x80000018` | Yes | 24 |
| 5 | `0x80000009` | Yes | 9 |
| 8 | `0x80000010` | Yes | 16 |
| 10 | `0x80000013` | Yes | 19 |
| 12 | `0x8000001f` | Yes | 31 |
| 13 | `0x8000001c` | Yes | 28 |

All other VPNs (1, 2, 3, 4, 6, 7, 9, 11, 14, 15) are invalid.

## Answer: Virtual Address Trace

Page size is 1 KB, so for each address: `VPN = address / 1024`, `offset = address % 1024`. Physical address (when valid) = `(PFN &times; 1024) + offset`.

| Virtual Address (hex) | Decimal | VPN | Offset | PTE valid? | Result |
|---|---|---|---|---|---|
| `0x00003986` | 14726 | 14 | 390 | No | **Invalid / segfault** |
| `0x00002bc6` | 11206 | 10 | 966 | Yes (PFN 19) | **PA = 20422 (0x4FC6)** |
| `0x00001e37` | 7735 | 7 | 567 | No | **Invalid / segfault** |
| `0x00000671` | 1649 | 1 | 625 | No | **Invalid / segfault** |
| `0x00001bc9` | 7113 | 6 | 969 | No | **Invalid / segfault** |

**Only one of the five addresses succeeds.** `0x00002bc6` lands on VPN 10, which is mapped to PFN 19 &mdash; so the physical address is `(19 &times; 1024) + 966 = 19456 + 966 = 20422` (`0x4C00 | 0x3C6 = 0x4FC6`). All the other four addresses fall on VPNs that were never marked valid in the table, so each one faults &mdash; even though every VPN here is well within the 16-entry table (no out-of-bounds VPNs in this trace, unlike some other traces where the VPN itself exceeds the table size).
