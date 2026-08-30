# Question 3.a

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

**Page table size:** `16 KB / 1 KB = 16` entries — indices `0` through `15`, matching the dump below.

**Page table contents:**

```
[       0]  0x00000000
[       1]  0x00000000
[       2]  0x00000000
[       3]  0x00000000
[       4]  0x00000000
[       5]  0x00000000
[       6]  0x00000000
[       7]  0x00000000
[       8]  0x00000000
[       9]  0x00000000
[      10]  0x00000000
[      11]  0x00000000
[      12]  0x00000000
[      13]  0x00000000
[      14]  0x00000000
[      15]  0x00000000
```

**Key observation:** every single entry is `0x00000000` — the valid bit is `0` for all 16 pages. **No page in this address space is mapped**, regardless of VPN. That means every translation below fails, no matter what the address is.

## Answer: Virtual Address Trace

Page size is 1 KB, so for each address: `VPN = address / 1024`, `offset = address % 1024`.

| Virtual Address (hex) | Decimal | VPN | Offset | PTE valid? | Result |
|---|---|---|---|---|---|
| `0x00003a39` | 14905 | 14 | 569 | No (entry 14 = `0x00000000`) | **Invalid / segfault** |
| `0x00003ee5` | 16101 | 15 | 741 | No (entry 15 = `0x00000000`) | **Invalid / segfault** |
| `0x000033da` | 13274 | 12 | 986 | No (entry 12 = `0x00000000`) | **Invalid / segfault** |
| `0x000039bd` | 14781 | 14 | 445 | No (entry 14 = `0x00000000`) | **Invalid / segfault** |
| `0x000013d9` | 5081 | 4 | 985 | No (entry 4 = `0x00000000`) | **Invalid / segfault** |

**Every address in this trace faults.** Note this isn't because any address falls outside the 16 KB address space (all five VPNs — 14, 15, 12, 14, 4 — are perfectly in-range, 0–15) — it's because **no page has ever been allocated/mapped** in this address space at all. This is a useful reminder that "in bounds" and "valid" are two separate checks: the hardware first checks the VPN is within the table, then separately checks the valid bit of that specific entry. An address can pass the first check and still fail the second.
