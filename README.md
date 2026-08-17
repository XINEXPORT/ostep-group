# ostep-group

## About OSTEP

These are the assignments for the [OSTEP](https://pages.cs.wisc.edu/~remzi/OSTEP/) (Operating Systems: Three Easy Pieces) book club.

Each directory corresponds to a chapter of the book and holds the code, notes, answers, and exercises worked through by the group.

## Structure

| Directory | Chapter |
| --- | --- |
| [ch4-abstraction](ch4-abstraction) | The Abstraction: The Process |
| [ch5-process-api](ch5-process-api) | Process API (fork, exec, wait) |
| [ch6-limited-direct](ch6-limited-direct) | Limited Direct Execution |
| [ch7-scheduling](ch7-scheduling) | Scheduling: Introduction (FIFO, SJF, STCF, RR) |
| [ch8-mlfq](ch8-mlfq) | Multi-Level Feedback Queue |
| [ch9-proportional-share](ch9-proportional-share) | Lottery & Proportional-Share Scheduling |
| [ch10-sqms-mqms](ch10-sqms-mqms) | Multiprocessor Scheduling (Advanced) |
| [ch13-address-spaces](ch13-address-spaces) | The Abstraction: Address Spaces |
| [ch14-memory-api](ch14-memory-api) | Memory API (malloc/free) |
| [ch15-address-translation](ch15-address-translation) | Address Translation (base & bounds) |
| [ch16-segmentation](ch16-segmentation) | Segmentation |
| [ch17-free-space-management](ch17-free-space-management) | Free-Space Management |
| [ch18-paging](ch18-paging) | Paging: Introduction |
| [ch19-translation-lookaside](ch19-translation-lookaside) | Translation Lookaside Buffers |
| [ch20-small-tables](ch20-small-tables) | Paging: Smaller Tables (multi-level page tables) |
| [ch21-swap-mechanisms](ch21-swap-mechanisms) | Swapping: Mechanisms |
| [ch22-swap-policies](ch22-swap-policies) | Swapping: Policies (FIFO, LRU, clock) |
| [ch23-vms](ch23-vms) | Complete Virtual Memory Systems (VAX & Linux) |
| [ch26-concurrency](ch26-concurrency) | Concurrency: An Introduction |
| [ch27-thread-api](ch27-thread-api) | Thread API |
| [ch28-locks](ch28-locks) | Locks |
| [ch29-locking-data-structures](ch29-locking-data-structures) | Lock-based Concurrent Data Structures |
| [ch30-condition-variables](ch30-condition-variables) | Condition Variables |
| [ch31-semaphores](ch31-semaphores) | Semaphores |
| [ch32-concurrency-problems](ch32-concurrency-problems) | Common Concurrency Problems (atomicity/ordering bugs, deadlock) |
| [ch33-event-based-concurrency](ch33-event-based-concurrency) | Event-based Concurrency (Advanced) |
| [ch37-hard-disk-drives](ch37-hard-disk-drives) | Hard Disk Drives |
| [ch38-raid](ch38-raid) | Redundant Arrays of Inexpensive Disks (RAID) |
| [ch39-interlude-files](ch39-interlude-files) | Interlude: Files and Directories |
| [ch40-vsfs](ch40-vsfs) | File System Implementation (vsfs) |
| [ch41-locality-ffs](ch41-locality-ffs) | Locality and The Fast File System |
| [ch42-fsck-journaling](ch42-fsck-journaling) | Crash Consistency: FSCK and Journaling |
| [ch43-log-file-system](ch43-log-file-system) | Log-structured File Systems |
| [ch44-flash-ssd](ch44-flash-ssd) | Flash-based SSDs |
| [ch45-data-integrity](ch45-data-integrity) | Data Integrity and Protection |
| [ch48-distributed-systems](ch48-distributed-systems) | Distributed Systems (RPC) |
| [ch49-sun-nfs](ch49-sun-nfs) | Sun's Network File System (NFS) |
| [ch50-andrew-file-system](ch50-andrew-file-system) | The Andrew File System (AFS) |

## Instructions

### Prerequisites

- A C compiler (`gcc` or `clang`)
- Python 3

### Running the code

C files compile standalone from within their chapter directory:

```
gcc file.c -o file -pthread
```

The `-pthread` flag is required for the concurrency chapters (ch26-33).

Python files run directly with the system interpreter:

```
python file.py
```
