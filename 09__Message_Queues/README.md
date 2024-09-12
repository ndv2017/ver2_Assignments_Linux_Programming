**BT17**. (Haven't done) Tạo ra một danh sách sinh viên mới message queues. Định dạng dữ liệu lưu trữ trong queues như sau:

```c
struct Message {
    long student_ID <priority>;
    struct Student {
        char name;
        int age;
        char hometown;
        char contact;
    };
}
```

<br>

Menu hiển thị chức năng.

Nhập thông tin sinh viên từ bàn phím và lưu trữ vào trong queue.

Hiển thị thông tin sinh viên thông qua id.

Hiển thị toàn bộ danh sách của sinh viên.

Xóa một sinh viên khỏi danh sách thông qua id.

*Lưu ý*: giá trị id của mỗi sinh viên là duy nhất và lớn hơn 0.

***

*Update*:
- The problem BT17 **haven't been solved** yet.
- All directories here (POSIX_message_queues & SystemV_message_queues) contain basic send/receive message projects for study purposes. 
