# 🚗 HƯỚNG DẪN NHANH - Smart Parking System

## ⚡ Bước 1: Biên Dịch

### Cách 1: Double-click file (Windows)

```
Nhấp đôi vào: compile.bat
```

### Cách 2: Command Line (Windows)

```cmd
cd c:\BTL ktllt
g++ -o smart_parking main.cpp -std=c++11
smart_parking
```

### Cách 3: Command Line (Linux/Mac)

```bash
cd ~/BTL\ ktllt
g++ -o smart_parking main.cpp -std=c++11
./smart_parking
```

---

## 📋 Menu Chính

```
[1] 🚗 Gửi xe vào bãi        → Nhập biển số, hệ thống tự tìm slot gần nhất
[2] 🚙 Lấy xe ra khỏi bãi    → Nhập biển số để lấy xe
[3] 📍 Xem bản đồ bãi xe     → Hiển thị bản đồ trực quan
[4] 📋 Xem trạng thái slot   → Danh sách tất cả slot
[5] 🚗 Xem danh sách xe      → Xe đang đậu tại bãi
[6] 📝 Xem lịch sử           → Tất cả giao dịch [IN]/[OUT]
[7] 🔄 Reset                  → Xóa tất cả dữ liệu (cần xác nhận "YES")
[0] ❌ Thoát                   → Thoát chương trình
```

---

## 🎮 Ví Dụ Thực Tế

### Sử Dụng 1: Gửi Xe

```
Menu chọn: 1
Nhập biển số xe (VD: ABC123): ABC123

✓ Kết quả:
  Slot được chọn: P1
  Vị trí: (0,4)
  Đường đi: (0,0) (0,1) (0,2) (0,3) (0,4)
  Khoảng cách: 4 bước
  ✓ Gửi xe thành công!
```

### Sử Dụng 2: Xem Bản Đồ

```
Menu chọn: 3

✓ Kết quả:
  ┌─────────────────────────────────────┐
  │ · · · · 🚙 · 🚙 ·                   │
  │ · █ █ · 🚙 · 🚙 ·                   │
  │ 🚙 · · · 🚙 · 🚙 ·                   │
  │ 🚙 █ █ · 🚙 · 🚙 ·                   │
  │ 🚙 🚙 □ 🚙 🚙 🚙 🚙 🚙                 │
  └─────────────────────────────────────┘

  CHÂN DUNG:
  · = Đường đi
  █ = Vật cản
  □ = Slot trống
  🚙 = Xe đang đậu
```

### Sử Dụng 3: Lấy Xe

```
Menu chọn: 2
Nhập biển số xe: ABC123

✓ Kết quả:
  ✓ Lấy xe thành công!
```

### Sử Dụng 4: Xem Lịch Sử

```
Menu chọn: 6

✓ Kết quả:
  ╔════════════════════════════════════════╗
  ║ ➖ [OUT] ABC123 <- P1                   ║
  ║ ➕ [IN ] ABC123 -> P1                   ║
  ║ ➕ [IN ] XYZ789 -> P3                   ║
  ╚════════════════════════════════════════╝
```

---

## 📁 Các File Dữ Liệu

### parking_data.txt

```
ABC123 P1
XYZ789 P3
DEF456 P5
```

→ Lưu biển số xe và slot đang đậu

### history.txt

```
[IN ] ABC123 -> P1
[OUT] ABC123 <- P1
[IN ] XYZ789 -> P3
```

→ Lưu tất cả giao dịch gửi/lấy xe

---

## 🔧 Xử Lý Sự Cố

### ❌ Lỗi: "Command 'g++' not found"

**Giải pháp**: Cài đặt MinGW GCC

- Windows: https://www.mingw-w64.org/
- Linux: `sudo apt-get install g++ build-essential`
- Mac: `brew install gcc`

### ❌ Lỗi: "File not found - parking_data.txt"

**Giải pháp**: Tự động tạo khi chạy lần đầu. Nếu vẫn lỗi:

- Tạo file trống: `parking_data.txt` và `history.txt`
- Hoặc chạy option [7] Reset

### ❌ Lỗi: "Compilation failed"

**Giải pháp**:

1. Kiểm tra file `main.cpp` và `ui.h` có trong thư mục không
2. Biên dịch lại: `g++ -o smart_parking main.cpp -std=c++11`
3. Nếu vẫn lỗi, copy cả `main.cpp` vào cùng thư mục

### ❌ Lỗi: "Bãi xe đã đầy!"

**Giải pháp**:

- Lấy một số xe ra bằng option [2]
- Hoặc reset hệ thống bằng option [7]

---

## 💡 Tips & Tricks

### 1. Kiểm Tra Xe Nhanh

Chọn [5] để xem tất cả xe đang đậu

### 2. Theo Dõi Hoạt Động

Chọn [6] để xem lịch sử (20 ghi nhận gần nhất)

### 3. Kiểm Tra Slot Còn Trống

Chọn [4] để xem trạng thái từng slot

### 4. Tìm Đường Tối Ưu

Hệ thống tự động dùng A\* để tìm slot gần nhất và đường đi ngắn nhất

### 5. Reset & Tái Khởi Động

Chọn [7] rồi nhập "YES" để xóa tất cả dữ liệu

---

## 📊 Thông Số Bãi Xe

- **Kích thước**: 5 hàng × 8 cột
- **Tổng slot**: ~16 slot
- **Max xe**: 100 chiếc
- **Max lịch sử**: 500 ghi nhận
- **Điểm vào**: Góc trên trái (0,0)

---

## 🎯 Quy Trình Gửi Xe Tự Động

```
1. Xe nhập biển số
   ↓
2. Hệ thống kiểm tra xe có tồn tại không
   ↓
3. Tìm tất cả slot trống
   ↓
4. Sắp xếp slot theo Manhattan distance
   ↓
5. Dùng A* tính đường đi ngắn nhất
   ↓
6. Chọn slot có đường đi hợp lệ gần nhất
   ↓
7. Lưu dữ liệu & cập nhật lịch sử
   ↓
✅ Hoàn thành!
```

---

## 🚀 Mở Rộng Tương Lai

- [ ] GUI đồ họa (Qt/SFML)
- [ ] Web API (REST)
- [ ] Mobile App
- [ ] Camera & OCR
- [ ] Database (SQLite)
- [ ] Thanh toán online
- [ ] Thông báo real-time

---

**Xin cảm ơn! Chúc bạn sử dụng dịch vụ Smart Parking thành công! 🚗✨**
