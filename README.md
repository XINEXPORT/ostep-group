# ostep-group

## About OSTEP

These are the assignments for the [OSTEP](hw/https://pages.cs.wisc.edu/~remzi/OSTEP/) (Operating Systems: Three Easy Pieces) book club.

Each directory corresponds to a chapter of the book and holds the code, notes, answers, and exercises worked through by the group.

## Structure

| Directory                                                       | Chapter                                                         |
| --------------------------------------------------------------- | --------------------------------------------------------------- |
| [ch4-abstraction](hw/ch4-abstraction)                           | The Abstraction: The Process                                    |
| [ch5-process-api](hw/ch5-process-api)                           | Process API (fork, exec, wait)                                  |
| [ch6-limited-direct](hw/ch6-limited-direct)                     | Limited Direct Execution                                        |
| [ch7-scheduling](hw/ch7-scheduling)                             | Scheduling: Introduction (FIFO, SJF, STCF, RR)                  |
| [ch8-mlfq](hw/ch8-mlfq)                                         | Multi-Level Feedback Queue                                      |
| [ch9-proportional-share](hw/ch9-proportional-share)             | Lottery & Proportional-Share Scheduling                         |
| [ch10-sqms-mqms](hw/ch10-sqms-mqms)                             | Multiprocessor Scheduling (Advanced)                            |
| [ch13-address-spaces](hw/ch13-address-spaces)                   | The Abstraction: Address Spaces                                 |
| [ch14-memory-api](hw/ch14-memory-api)                           | Memory API (malloc/free)                                        |
| [ch15-address-translation](hw/ch15-address-translation)         | Address Translation (base & bounds)                             |
| [ch16-segmentation](hw/ch16-segmentation)                       | Segmentation                                                    |
| [ch17-free-space-management](hw/ch17-free-space-management)     | Free-Space Management                                           |
| [ch18-paging](hw/ch18-paging)                                   | Paging: Introduction                                            |
| [ch19-translation-lookaside](hw/ch19-translation-lookaside)     | Translation Lookaside Buffers                                   |
| [ch20-small-tables](hw/ch20-small-tables)                       | Paging: Smaller Tables (multi-level page tables)                |
| [ch21-swap-mechanisms](hw/ch21-swap-mechanisms)                 | Swapping: Mechanisms                                            |
| [ch22-swap-policies](hw/ch22-swap-policies)                     | Swapping: Policies (FIFO, LRU, clock)                           |
| [ch23-vms](hw/ch23-vms)                                         | Complete Virtual Memory Systems (VAX & Linux)                   |
| [ch26-concurrency](hw/ch26-concurrency)                         | Concurrency: An Introduction                                    |
| [ch27-thread-api](hw/ch27-thread-api)                           | Thread API                                                      |
| [ch28-locks](hw/ch28-locks)                                     | Locks                                                           |
| [ch29-locking-data-structures](hw/ch29-locking-data-structures) | Lock-based Concurrent Data Structures                           |
| [ch30-condition-variables](hw/ch30-condition-variables)         | Condition Variables                                             |
| [ch31-semaphores](hw/ch31-semaphores)                           | Semaphores                                                      |
| [ch32-concurrency-problems](hw/ch32-concurrency-problems)       | Common Concurrency Problems (atomicity/ordering bugs, deadlock) |
| [ch33-event-based-concurrency](hw/ch33-event-based-concurrency) | Event-based Concurrency (Advanced)                              |
| [ch37-hard-disk-drives](hw/ch37-hard-disk-drives)               | Hard Disk Drives                                                |
| [ch38-raid](hw/ch38-raid)                                       | Redundant Arrays of Inexpensive Disks (RAID)                    |
| [ch39-interlude-files](hw/ch39-interlude-files)                 | Interlude: Files and Directories                                |
| [ch40-vsfs](hw/ch40-vsfs)                                       | File System Implementation (vsfs)                               |
| [ch41-locality-ffs](hw/ch41-locality-ffs)                       | Locality and The Fast File System                               |
| [ch42-fsck-journaling](hw/ch42-fsck-journaling)                 | Crash Consistency: FSCK and Journaling                          |
| [ch43-log-file-system](hw/ch43-log-file-system)                 | Log-structured File Systems                                     |
| [ch44-flash-ssd](hw/ch44-flash-ssd)                             | Flash-based SSDs                                                |
| [ch45-data-integrity](hw/ch45-data-integrity)                   | Data Integrity and Protection                                   |
| [ch48-distributed-systems](hw/ch48-distributed-systems)         | Distributed Systems (RPC)                                       |
| [ch49-sun-nfs](hw/ch49-sun-nfs)                                 | Sun's Network File System (NFS)                                 |
| [ch50-andrew-file-system](hw/ch50-andrew-file-system)           | The Andrew File System (AFS)                                    |

## Instructions

### Prerequisites

- A C compiler (`gcc` or `clang`)
- Python 3

### Running the code

C files compile standalone from within their chapter directory:

```
gcc file.c -o file -pthread
```

The `-pthread` flag is required for the concurrency chapters (hw/ch26-33).

Python files run directly with the system interpreter:

```
python file.py
```
