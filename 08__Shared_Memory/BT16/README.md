**BT16**: So sánh giữa hai phương thức mapping memory sử dụng hàm `mmap()` (POSIX api). Triển khai code để chứng minh.

**In brief**: The two types of memory mapping discussed here are:
- **Private file mapping**: Memory is initialized from the contents of a file (e.g., `sharedlib.so`).
- **Shared file mapping**: Used for memory-mapped I/O, enabling memory to be shared between processes (IPC).

<br>

There are also **private anonymous mapping** and **shared anonymous mapping**, but we won't be using these.

<br>

Check shared memory object:

    ls -l /dev/shm/viet_mmap