# 📑 INDEX - Smart Parking System (Tìm Kiếm Nhanh)

## 🚀 Bắt Đầu Nhanh (5 Phút)

### 1️⃣ Biên Dịch & Chạy

```bash
compile.bat                          # Windows - Double-click
# hoặc
g++ -o smart_parking main.cpp -std=c++11 && smart_parking
```

### 2️⃣ Đọc Hướng Dẫn

- **5 phút**: [`QUICK_START.md`](QUICK_START.md)
- **15 phút**: [`INSTALL_AND_USAGE.md`](INSTALL_AND_USAGE.md)
- **30 phút**: [`ARCHITECTURE.md`](ARCHITECTURE.md)

### 3️⃣ Xem Kết Quả

Menu sẽ hiển thị. Chọn [1] để gửi xe hoặc [3] để xem bản đồ!

---

## 📚 Hướng Dẫn Chi Tiết

| File                     | Nội Dung            | Đọc Khi                 |
| ------------------------ | ------------------- | ----------------------- |
| **QUICK_START.md**       | Hướng dẫn 5-10 phút | Muốn chạy ngay          |
| **INSTALL_AND_USAGE.md** | Hướng dẫn đầy đủ    | Muốn hiểu kỹ            |
| **ARCHITECTURE.md**      | Kiến trúc hệ thống  | Muốn học thuật toán     |
| **PROJECT_SUMMARY.md**   | Tóm tắt dự án       | Muốn overview tổng quát |

---

## 💻 File Code

| File            | Kích Thước | Mục Đích         | Biên Dịch?                |
| --------------- | ---------- | ---------------- | ------------------------- |
| **main.cpp** ⭐ | ~600 lines | Logic + UI chính | **Dùng file này**         |
| **ui.h**        | ~300 lines | Header UI        | Include trong main        |
| **logic.cpp**   | Original   | Reference code   | Không cần (dùng main.cpp) |

---

## 📦 Tệp Dữ Liệu

| File                      | Loại | Mục Đích         | Tự Động Tạo? |
| ------------------------- | ---- | ---------------- | ------------ |
| `parking_data.txt`        | TEXT | Lưu xe đang đậu  | ✅ Có        |
| `history.txt`             | TEXT | Lưu lịch sử      | ✅ Có        |
| `sample_parking_data.txt` | TEXT | Dữ liệu test mẫu | Tham khảo    |

---

## 🎮 Menu Chính

```
[1] 🚗 Gửi xe vào bãi          → Tự động tìm slot gần nhất
[2] 🚙 Lấy xe ra khỏi bãi      → Xóa xe khỏi hệ thống
[3] 📍 Xem bản đồ bãi xe       → Hiển thị bản đồ ASCII
[4] 📋 Xem trạng thái slot     → Danh sách tất cả slot
[5] 🚗 Xem danh sách xe        → Xe đang đậu
[6] 📝 Xem lịch sử             → Ghi nhận giao dịch
[7] 🔄 Reset                   → Xóa tất cả dữ liệu
[0] ❌ Thoát                    → Thoát chương trình
```

---

## 🔍 Câu Hỏi Thường Gặp

### ❓ Làm sao để chạy?

👉 [`QUICK_START.md`](QUICK_START.md) - Mục "Bước 1: Biên Dịch"

### ❓ Thuật toán A\* là gì?

👉 [`ARCHITECTURE.md`](ARCHITECTURE.md) - Mục "A\* Algorithm Flow"

### ❓ Làm sao lưu dữ liệu?

👉 Tự động lưu vào `parking_data.txt` và `history.txt`

### ❓ Có lỗi gì thì sao?

👉 [`INSTALL_AND_USAGE.md`](INSTALL_AND_USAGE.md) - Mục "Xử Lý Sự Cố"

### ❓ Muốn mở rộng thêm tính năng?

👉 [`PROJECT_SUMMARY.md`](PROJECT_SUMMARY.md) - Mục "Gợi Ý Mở Rộng"

---

## 🏗️ Cấu Trúc Hệ Thống

```
USER INTERFACE (ui.h)
        ↓
CORE LOGIC (main.cpp)
   - A* Pathfinding
   - Parking Logic
   - Car Management
        ↓
DATA PERSISTENCE
   - parking_data.txt
   - history.txt
```

---

## ⚙️ Cài Đặt Yêu Cầu

- **Trình biên dịch**: G++ (MinGW trên Windows)
- **Phiên bản C++**: C++11 trở lên
- **Hệ điều hành**: Windows/Linux/Mac

### Cài G++:

- **Windows**: https://www.mingw-w64.org/
- **Linux**: `sudo apt-get install g++ build-essential`
- **Mac**: `brew install gcc`

---

## 📊 Tính Năng Chính

- ✅ **A\* Pathfinding** - Tìm đường tối ưu
- ✅ **Auto Slot Detection** - Tự động chọn slot gần nhất
- ✅ **Visual Map** - Bản đồ ASCII đẹp
- ✅ **History Logging** - Ghi lại tất cả hoạt động
- ✅ **Data Persistence** - Lưu dữ liệu tự động
- ✅ **Modern UI** - Menu tương tác

---

## 🎯 Bản Đồ Bãi Xe

```
  0  1  2  3  4  5  6  7
0 ·  ·  ·  ·  □  ·  □  ·
1 ·  █  █  ·  □  ·  □  ·
2 □  ·  ·  ·  □  ·  □  ·
3 □  █  █  ·  □  ·  □  ·
4 □  □  □  □  □  □  □  □

Ký hiệu:
· = Đường đi
█ = Vật cản
□ = Slot trống
🚙 = Có xe (khi xem trực tiếp)
```

---

## 🎓 Học từ Dự Án Này

### Thuật Toán:

- [x] A\* Pathfinding
- [x] Manhattan Distance
- [x] Graph Traversal
- [x] Priority Queue

### Kỹ Năng Lập Trình:

- [x] Dynamic Memory (new/delete)
- [x] Data Structures (Struct, Array)
- [x] File I/O
- [x] Algorithm Design
- [x] UI/UX Console

---

## 📋 Danh Sách File Cần Biên Dịch

```
✅ main.cpp        (file chính)
✅ ui.h            (auto-include)
───────────────────────────────────
❌ logic.cpp       (không cần - đã merged vào main.cpp)
❌ sample_parking_data.txt (chỉ để tham khảo)
```

---

## 🚀 Bước Chạy Đầu Tiên

### Bước 1: Biên Dịch

```bash
g++ -o smart_parking main.cpp -std=c++11
```

### Bước 2: Chạy

```bash
smart_parking
```

### Bước 3: Thử Chức Năng

```
Chọn: 1 (gửi xe)
Nhập biển số: ABC123
✓ Hoàn thành!
```

---

## 💾 Dữ Liệu Test

File `sample_parking_data.txt` chứa:

```
ABC123 P1
XYZ789 P3
DEF456 P5
GHI234 P2
JKL567 P4
```

Để load dữ liệu test:

```bash
cp sample_parking_data.txt parking_data.txt
```

---

## 🔧 Lệnh Útil

```bash
# Biên dịch
g++ -o smart_parking main.cpp -std=c++11

# Chạy
./smart_parking          # Linux/Mac
smart_parking.exe        # Windows

# Xem dữ liệu
type parking_data.txt    # Windows
cat parking_data.txt     # Linux/Mac

# Reset dữ liệu
del parking_data.txt history.txt  # Windows
rm parking_data.txt history.txt   # Linux/Mac

# Load dữ liệu test
copy sample_parking_data.txt parking_data.txt  # Windows
cp sample_parking_data.txt parking_data.txt    # Linux/Mac
```

---

## 📞 Liên Hệ Hỗ Trợ

### Problem → Solution

| Vấn Đề                   | Giải Pháp                              |
| ------------------------ | -------------------------------------- |
| "g++: command not found" | Cài MinGW / GCC                        |
| "Compilation error"      | Kiểm tra file main.cpp & ui.h          |
| "Bãi xe đã đầy"          | Lấy xe ra (menu 2) hoặc reset (menu 7) |
| "Không tìm thấy xe"      | Chắc chắn xe đã gửi vào (menu 1)       |
| "File not found"         | Chạy từ folder chứa main.cpp           |

---

## 📈 Thống Kê

| Thông Số             | Giá Trị   |
| -------------------- | --------- |
| Dòng code (main.cpp) | ~600      |
| Dòng code (ui.h)     | ~300      |
| Tài liệu             | 5 file MD |
| Tính năng            | 8 chính   |
| Structs              | 7 cái     |
| Functions            | 30+ hàm   |

---

## ✅ Danh Sách Kiểm Tra

- [x] Code logic hoàn thiện
- [x] UI integrated
- [x] File I/O working
- [x] A\* algorithm tested
- [x] Documentation complete
- [x] Sample data provided
- [x] Build script ready
- [x] Error handling done
- [x] Ready for production! 🎉

---

## 🎉 Kết Luận

Bạn có một hệ thống quản lý bãi xe **hoàn chỉnh**, **chuyên nghiệp**, và **sẵn sàng sử dụng**!

### 3 Tệp Chính:

1. ⭐ **main.cpp** - Biên dịch file này!
2. **ui.h** - Header visualization
3. **compile.bat** - Build script

### 5 Hướng Dẫn:

1. **QUICK_START.md** - 5 phút
2. **INSTALL_AND_USAGE.md** - Chi tiết
3. **ARCHITECTURE.md** - Kỹ thuật
4. **PROJECT_SUMMARY.md** - Tóm tắt
5. **INDEX.md** - File này (navigator)

---

## 📞 Đâu Là Bước Tiếp Theo?

1. ✅ **Biên dịch**: `g++ -o smart_parking main.cpp -std=c++11`
2. ✅ **Chạy**: `./smart_parking`
3. ✅ **Test**: Menu [1] - Gửi xe, Menu [3] - Xem bản đồ
4. ✅ **Đọc**: `ARCHITECTURE.md` - Hiểu thuật toán
5. ✅ **Mở rộng**: Xem "Gợi ý Mở Rộng" trong `PROJECT_SUMMARY.md`

---

**Chúc bạn thành công! 🚗✨**

_Smart Parking System - Hệ Thống Quản Lý Bãi Xe Thông Minh_  
_Created: 2026 | Language: C++11 | Status: ✅ READY_
