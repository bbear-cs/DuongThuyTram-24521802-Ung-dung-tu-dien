# Ứng dụng từ điển tiếng Anh bằng Radix-Trie

Thực hành **[CS523] Cấu trúc dữ liệu và giải thuật nâng cao**.

## Nội dung
Chương trình mô phỏng một ứng dụng từ điển tiếng Anh, hỗ trợ các thao tác:
- Thêm mục từ
- Xóa mục từ
- Tìm nghĩa của từ

## Cấu trúc chương trình
Chương trình được chia thành 3 file chính:
- `khaibao.cpp`: chứa cấu trúc dữ liệu và thuật toán Radix-Trie
- `giaodien.cpp`: chứa phần giao diện WinAPI và các thao tác từ người dùng
- `main.cpp`: chứa hàm `WinMain()` để khởi động ứng dụng và liên kết các phần của chương trình

## Giao diện
Giao diện được xây dựng bằng **WinAPI**, sử dụng các hàm có sẵn do Windows cung cấp để tạo cửa sổ, ô nhập liệu, nút bấm, vùng hiển thị dữ liệu và vùng hiển thị cây chỉ mục.

## Chức năng chính
- Quản lý các mục từ trong từ điển
- Hiển thị bảng dữ liệu gốc
- Xây dựng và hiển thị chỉ mục Radix-Trie
- Minh họa thao tác thêm, tìm kiếm và xóa trên cây Radix-Trie
