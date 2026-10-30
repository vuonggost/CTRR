# 🚗 Smart Parking Management System

## Hệ Thống Quản Lý Bãi Xe Thông Minh

### Giới Thiệu

Một ứng dụng quản lý bãi xe hiện đại xây dựng bằng **C++**, sử dụng thuật toán **A\*** để tìm kiếm đường đi tối ưu cho các xe vào bãi.

---

## Tính Năng Chính

### ✨ Các Tính Năng:

- 🚗 **Gửi xe vào bãi** - Tự động tìm slot gần nhất bằng A\*
- 🚙 **Lấy xe ra khỏi bãi** - Cập nhật trạng thái slot
- 📍 **Xem bản đồ bãi xe** - Hiển thị trực quan toàn bộ bãi
- 📋 **Xem trạng thái slot** - Danh sách tất cả slot và trạng thái
- 🚗 **Xem danh sách xe** - Xe đang đậu tại bãi
- 📝 **Xem lịch sử** - Ghi nhận tất cả hoạt động
- 🔄 **Reset hệ thống** - Xóa tất cả dữ liệu
- 💾 **Lưu/Load dữ liệu** - Tự động lưu vào file

---

## Cấu Trúc Dự Án

```
BTL ktllt/
├── logic.cpp              # Logic hệ thống gốc (có thể bỏ)
├── main.cpp               # Chương trình chính (UI + Logic)
├── ui.h                   # Header file UI (trực quan hóa)
├── compile.bat            # Script biên dịch (Windows)
├── parking_data.txt       # Dữ liệu xe đậu (auto-save)
├── history.txt            # Lịch sử hoạt động (auto-save)
└── README.md              # Tài liệu này
```

---

## Cài Đặt & Biên Dịch

### Yêu Cầu:

- **Trình biên dịch C++**: MinGW GCC (hoặc MSVC)
- **C++ Standard**: C++11 trở lên
- **Hệ điều hành**: Windows/Linux/Mac

### Cách Biên Dịch:

#### **Phương pháp 1: Sử dụng Batch (Windows)**

```bash
compile.bat
```

#### **Phương pháp 2: Biên dịch thủ công**

```bash
g++ -o smart_parking main.cpp -std=c++11
smart_parking
```

#### **Phương pháp 3: Linux/Mac**

```bash
g++ -o smart_parking main.cpp -std=c++11
./smart_parking
```

---

## Cách Sử Dụng

### Menu Chính:

```
===== SMART PARKING =====
[1] 🚗 Gửi xe vào bãi
[2] 🚙 Lấy xe ra khỏi bãi
[3] 📍 Xem bản đồ bãi xe
[4] 📋 Xem trạng thái các slot
[5] 🚗 Xem danh sách xe đậu
[6] 📝 Xem lịch sử hoạt động
[7] 🔄 Reset (xóa toàn bộ dữ liệu)
[0] ❌ Thoát chương trình
```

### Ví Dụ Sử Dụng:

#### **1. Gửi xe vào bãi:**

```
Nhập biển số xe (VD: ABC123): ABC123
Slot được chọn: P1
Vị trí: (0,4)
Đường đi: (0,0) (1,0) ... (0,4)
Khoảng cách: 5 bước
✓ Gửi xe thành công!
```

#### **2. Xem bản đồ bãi:**

```
  ┌─────────────────────────────────────┐
  │ · · · · 🚙 · 🚙 ·                   │
  │ · █ █ · 🚙 · 🚙 ·                   │
  │ 🚙 · · · 🚙 · 🚙 ·                   │
  │ 🚙 █ █ · 🚙 · 🚙 ·                   │
  │ 🚙 🚙 □ 🚙 🚙 🚙 🚙 🚙                 │
  └─────────────────────────────────────┘

CHÂN DUNG: ·(đường) █(vật cản) □(slot) 🚙(xe)
```

#### **3. Lấy xe ra khỏi bãi:**

```
Nhập biển số xe: ABC123
✓ Lấy xe thành công!
```

---

## Bản Đồ Bãi Xe

### Kích Thước:

- **Hàng (Rows)**: 5
- **Cột (Columns)**: 8
- **Tổng Slot**: ~16 slot

### Loại Ô:

- **0**: Đường đi (·)
- **1**: Vật cản/Tường (█)
- **2**: Slot xe (□ trống, 🚙 có xe)

```
MAP:
{0, 0, 0, 0, 2, 0, 2, 0},
{0, 1, 1, 0, 2, 0, 2, 0},
{2, 0, 0, 0, 2, 0, 2, 0},
{2, 1, 1, 0, 2, 0, 2, 0},
{2, 2, 2, 2, 2, 2, 2, 2}
```

---

## Thuật Toán A\*

### Khái Niệm:

Thuật toán A\* là một thuật toán tìm kiếm đường đi tối ưu trên đồ thị. Nó kết hợp:

- **G**: Khoảng cách từ điểm bắt đầu
- **H**: Ước tính khoảng cách đến đích (Heuristic - Manhattan)
- **F = G + H**: Chi phí toàn bộ

### Đặc Điểm:

✓ Tìm được đường đi tối ưu  
✓ Nhanh và hiệu quả  
✓ Tránh vật cản thông minh  
✓ Trả về khoảng cách chính xác

### Ứng Dụng Trong Dự Án:

- Tìm slot parking **gần nhất**
- Tính toán **đường đi ngắn nhất** từ lối vào (0,0) đến slot
- Hiển thị **toàn bộ đường đi** cho tài xế

---

## Cấu Trúc Dữ Liệu

### Struct Position:

```cpp
struct Position {
    int x;  // Hàng
    int y;  // Cột
};
```

### Struct Slot:

```cpp
struct Slot {
    char id[10];       // ID slot (P1, P2, ...)
    Position pos;      // Vị trí trên bản đồ
    bool occupied;     // Có xe hay không
};
```

### Struct Car:

```cpp
struct Car {
    char plate[20];    // Biển số xe
    char slotID[10];   // ID slot đang đậu
};
```

### Struct Node (A\* Graph):

```cpp
struct Node {
    Position pos;
    int g, h, f;       // Chi phí G, H, F
    Position parent;   // Node cha (để tracking đường đi)
    bool visited;      // Đã duyệt hay chưa
};
```

---

## Lưu & Tải Dữ Liệu

### Tệp Dữ Liệu:

#### **parking_data.txt**

Lưu thông tin xe đang đậu:

```
ABC123 P1
XYZ789 P3
DEF456 P5
```

#### **history.txt**

Lưu lịch sử tất cả giao dịch:

```
[IN ] ABC123 -> P1
[OUT] XYZ789 <- P3
[IN ] DEF456 -> P5
```

---

## Các Hàm Chính

### Logic Core:

- `isValid()` - Kiểm tra ô có hợp lệ
- `heuristic()` - Tính Manhattan distance
- `findPath()` - Tìm và in đường đi A\*
- `getDistance()` - Tính khoảng cách bằng A\*
- `findNearestSlot()` - Tìm slot gần nhất

### Quản Lý Bãi:

- `initializeParkingLot()` - Khởi tạo bãi
- `parkCar()` - Gửi xe vào
- `removeCar()` - Lấy xe ra
- `loadData()` / `saveData()` - Load/Save dữ liệu

### UI/UX:

- `displayParkingMap()` - Vẽ bản đồ
- `displaySlotStatus()` - Hiển thị slot
- `displayHistory()` - Hiển thị lịch sử
- `parkCarUI()` - UI gửi xe
- `removeCarUI()` - UI lấy xe

---

## Mở Rộng & Cải Thiện

### 💡 Ý Tưởng Cải Thiện:

1. **GUI Đồ Họa** - Dùng Qt hoặc SFML thay console
2. **Database** - Thay thế file txt bằng SQLite
3. **API Web** - Kết nối với ứng dụng mobile
4. **Camera/QR Code** - Tự động nhận diện biển số
5. **Thanh toán** - Tích hợp hệ thống thanh toán
6. **Notifikation** - Thông báo khi slot sắp đầy
7. **Analytics** - Thống kê và báo cáo

---

## Tác Giả & Ghi Chú

**Dự Án**: Smart Parking Management System  
**Ngôn Ngữ**: C++11  
**Được Xây Dựng**: 2026  
**Trạng Thái**: ✅ Hoàn thành

---

## Hỗ Trợ

Nếu gặp vấn đề:

1. Kiểm tra trình biên dịch C++ có cài chưa
2. Kiểm tra file `parking_data.txt` và `history.txt` có tồn tại
3. Chạy lại `compile.bat` hoặc biên dịch thủ công
4. Xóa `parking_data.txt` và `history.txt` để reset về trạng thái ban đầu

---

## 📝 License

Dự án này được cấp phép theo MIT License.

---

**Cảm ơn bạn đã sử dụng Smart Parking System! 🚗✨**
