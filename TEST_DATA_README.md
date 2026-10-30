╔════════════════════════════════════════════════════════════════╗
║ HƯ HƯỚNG DẪN DỮ LIỆU TEST CHO HỆ THỐNG BÃI GIỮ XE ║
╚════════════════════════════════════════════════════════════════╝

📋 CẤU TRÚC DỮ LIỆU TEST
════════════════════════════════════════════════════════════════

1️⃣ FILE: parking_data.txt
├─ Định dạng: [BIỂN SỐ] [SLOT ID]
├─ Mỗi dòng là một xe đang đỗ trong bãi
├─ Ví dụ:
│ ABC123 P1
│ XYZ789 P3
│ DEF456 P5
└─ Giải thích:
• ABC123 - Biển số xe
• P1 - ID slot (P = Parking, 1-20)

2️⃣ FILE: history.txt
├─ Định dạng: [IN/OUT] [BIỂN SỐ] [-> hoặc <-] [SLOT ID]
├─ Mỗi dòng là một sự kiện (vào/ra bãi)
├─ Ví dụ:
│ [IN ] ABC123 -> P1 (xe vào bãi, gửi vào slot P1)
│ [OUT] ABC123 <- P1 (xe ra khỏi bãi từ slot P1)
└─ Giải thích:
• [IN] - Xe vừa vào
• [OUT] - Xe vừa ra
• -> : Vào bãi
• <- : Ra khỏi bãi

════════════════════════════════════════════════════════════════

🎯 DỮ LIỆU TEST HIỆN CÓ
════════════════════════════════════════════════════════════════

📊 parking_data.txt:
• 15 xe đang đỗ
• Biển số: ABC123 -> NOP680
• Slot: P1 -> P15
• Mô phỏng trạng thái bãi xe đầy (~75%)

📊 history.txt:
• 20 sự kiện
• Ghi nhận quá trình xe vào/ra bãi
• Thứ tự thời gian từ cũ nhất đến mới nhất

════════════════════════════════════════════════════════════════

🔧 CÁCH SỬ DỤNG
════════════════════════════════════════════════════════════════

1. Chạy chương trình:
   $ logic.exe

2. Chương trình sẽ TỰ ĐỘNG:
   ✓ Tải dữ liệu từ parking_data.txt
   ✓ Tải lịch sử từ history.txt
   ✓ Hiển thị trạng thái hiện tại

3. Thực hiện các tác vụ:
   1. Gửi xe (sẽ tìm slot gần nhất)
   2. Lấy xe
   3. Xem danh sách slot
   4. Xem lịch sử
   5. Reset toàn bộ

════════════════════════════════════════════════════════════════

📝 VÍ DỤ CÀI ĐẶT THÊM DỮ LIỆU
════════════════════════════════════════════════════════════════

Để tạo bộ test khác:

parking_data.txt:
─────────────────────────────────────────────────────────────────
ABC111 P1
ABC222 P5
ABC333 P9
ABC444 P12
ABC555 P18
─────────────────────────────────────────────────────────────────
(Chỉ 5 xe, tạo trường hợp bãi xe còn trống)

history.txt:
─────────────────────────────────────────────────────────────────
[IN ] ABC111 -> P1
[IN ] ABC222 -> P5
[OUT] ABC111 <- P1
[IN ] ABC666 -> P1
[IN ] ABC333 -> P9
─────────────────────────────────────────────────────────────────
(Ghi nhận các sự kiện quá khứ)

════════════════════════════════════════════════════════════════

🗺️ BẢN ĐỒ BÃI XE (5×8 = 40 ô)
════════════════════════════════════════════════════════════════

         0 1 2 3 4 5 6 7
     0:  . . . . S . S .
     1:  . X X . S . S .
     2:  S . . . S . S .
     3:  S X X . S . S .
     4:  S S S S S S S S

Ký hiệu:
. = Đường đi
X = Vật cản
S = Slot xe (O để ghép = Parking space)

Tổng: 20 slot (được đánh P1 -> P20)

════════════════════════════════════════════════════════════════

✨ TÍNH NĂNG TEST
════════════════════════════════════════════════════════════════

1. Kiểm tra loading dữ liệu ✓
2. Kiểm tra tìm kiếm xe ✓
3. Kiểm tra sắp xếp slot ✓
4. Kiểm tra A\* pathfinding ✓
5. Kiểm tra lưu/tải lịch sử ✓

════════════════════════════════════════════════════════════════
