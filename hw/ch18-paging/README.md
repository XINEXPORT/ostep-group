# Chapter 18: Paging: Introduction

# Question 1
### Page Tabe Size Growing Linearly
- q1a.
    - When creating a page size table of 1 megabyte, the system created
    up to 1024 entries because 1 MB / 1 KB = 1024 page table entries (PTEs)
- q1b.
    - When creating a page size table of 2 megabytes, the system created
    up to 2048 PTEs.
- q1c.
    - When creating a page size table of 4 megabytes, the system created
    up to 4096 PTEs.
- What was learned?
    - It appears the size of the page table is doubling which means the size is growing linearly. We shouldn't use really big page sizes because internal fragmentation would frequently occur.
### Page Table Size Changes as Page Size Grows
- q1d.
    - With the address space fixed at 1 MB and a 1 KB page size, the system created 1024 PTEs, same as q1a.
- q1e.
    - With the address space still fixed at 1 MB but page size doubled to 2 KB, the system created 512 PTEs.
- q1f.
    - With the address space still fixed at 1 MB and page size doubled again to 4 KB, the system created 256 PTEs.
- What was learned?
    - Keeping the address space size fixed and doubling the page size halves the page table size.
    - So page table size scales with `address space size / page size`: growing the address space grows the table, but growing the page size shrinks it.

# Question 2
### Address Translation with a Linear Page Table
- q2a.
    - Every one of the 16 PTEs is `0x00000000` (valid bit 0), so no page is mapped at all. All 5 traced addresses segfault, even though every VPN (4, 12, 14, 15) is within the 16-entry table.
- q2b.
    - Only 6 of 16 PTEs are valid (VPNs 0, 5, 8, 10, 12, 13). Of the 5 traced addresses, only the one landing on VPN 10 (→ PFN 19) translates successfully (PA 0x4FC6); the other 4 hit unmapped VPNs and segfault.
- q2c.
    - 9 of 16 PTEs are valid. 3 of 5 addresses succeed (VPNs 12, 0, 6 → PFNs 15, 24, 29); the other 2 fall on unmapped VPNs (8, 11) and segfault.
- q2d.
    - All 16 PTEs are valid this time, so every traced address translates successfully. Largest resulting PA (32134) still fits comfortably within the 32 KB physical memory, so no bounds issues either.
- q2e.
    - Same seed and parameters as q2d, so the page table and address trace came out identical, meaning the answers are the same as q2d.
- What was learned?
    - The valid bit and the VPN-in-range check are independent: a VPN can be perfectly within the page table's size and still fault if that specific entry was never mapped (valid bit 0).
    - As more PTEs become valid across a-d, more addresses in the trace successfully translate with a fully populated table (q2d), every address succeeds.# Chapter 18: Paging: Introduction

