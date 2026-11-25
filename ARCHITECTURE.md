# 🏗️ Kiến Trúc Hệ Thống Smart Parking

## Cấu Trúc Phần Mềm

```
┌─────────────────────────────────────────────────────────┐
│                   USER INTERFACE (UI)                   │
│  ┌──────────────────────────────────────────────────┐   │
│  │  - Menu chính                                    │   │
│  │  - Visualization bản đồ bãi xe                   │   │
│  │  - Status display (slot, car, history)          │   │
│  │  - Input/Output console                         │   │
│  └──────────────────────────────────────────────────┘   │
│                     (ui.h)                              │
└──────────────────────┬──────────────────────────────────┘
                       │
┌──────────────────────▼──────────────────────────────────┐
│                  CORE LOGIC LAYER                       │
│  ┌──────────────────────────────────────────────────┐   │
│  │  Parking Lot Management:                         │   │
│  │  - initializeParkingLot()                        │   │
│  │  - parkCar() / removeCar()                       │   │
│  │  - findNearestSlot()                            │   │
│  │  - Slot/Car tracking                            │   │
│  │                                                  │   │
│  │  A* Pathfinding Algorithm:                       │   │
│  │  - findPath()                                    │   │
│  │  - getDistance()                                │   │
│  │  - heuristic() [Manhattan distance]             │   │
│  │  - Node management (g, h, f values)             │   │
│  └──────────────────────────────────────────────────┘   │
│                   (main.cpp)                            │
└──────────────────────┬──────────────────────────────────┘
                       │
┌──────────────────────▼──────────────────────────────────┐
│                   DATA LAYER                            │
│  ┌──────────────────────────────────────────────────┐   │
│  │  Structures:                                     │   │
│  │  - ParkingLot (main struct)                      │   │
│  │  - Slot[] (parking slots)                        │   │
│  │  - Car[] (vehicles)                              │   │
│  │  - Node[][] (A* graph)                           │   │
│  │  - HistoryEntry[] (transaction log)              │   │
│  │                                                  │   │
│  │  Parking Map: 5×8 grid                           │   │
│  │  - 0: Đường đi                                   │   │
│  │  - 1: Vật cản                                    │   │
│  │  - 2: Slot xe                                    │   │
│  └──────────────────────────────────────────────────┘   │
└──────────────────────┬──────────────────────────────────┘
                       │
┌──────────────────────▼──────────────────────────────────┐
│                  PERSISTENCE LAYER                      │
│  ┌──────────────────────────────────────────────────┐   │
│  │  Files:                                          │   │
│  │  - parking_data.txt (cars & slots)               │   │
│  │  - history.txt (transaction log)                 │   │
│  │                                                  │   │
│  │  Functions:                                      │   │
│  │  - loadData() / saveData()                       │   │
│  │  - loadHistory() / saveHistory()                 │   │
│  └──────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────┘
```

---

## Data Flow Diagram

### 1️⃣ Quy Trình Gửi Xe (Park Car)

```
┌─────────────────────┐
│  USER INPUT         │
│  Biển số xe: ABC123 │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────────────────────┐
│  CHECK CAR EXISTS?                  │
│  findCar(plate)                     │
└──────────┬──────────────────────────┘
           │
      NO  ◄─┘
           │
           ▼
┌─────────────────────────────────────┐
│  FIND NEAREST SLOT                  │
│  1. Get all empty slots             │
│  2. Sort by distance (Manhattan)    │
│  3. Use A* to check path validity   │
│  4. Select best slot                │
└──────────┬──────────────────────────┘
           │
           ▼
┌─────────────────────────────────────┐
│  CALCULATE OPTIMAL PATH (A*)        │
│  - Start: (0,0)                     │
│  - Goal: Slot position              │
│  - Output: Path + Distance          │
└──────────┬──────────────────────────┘
           │
           ▼
┌─────────────────────────────────────┐
│  UPDATE DATA STRUCTURES             │
│  - Mark slot as occupied            │
│  - Add car to cars[]                │
│  - Increment carCount               │
└──────────┬──────────────────────────┘
           │
           ▼
┌─────────────────────────────────────┐
│  SAVE TO FILE                       │
│  - parking_data.txt (cars)          │
│  - history.txt (log entry)          │
└──────────┬──────────────────────────┘
           │
           ▼
┌─────────────────────────────────────┐
│  SUCCESS MESSAGE                    │
│  - Display path                     │
│  - Show distance                    │
│  - Confirm operation                │
└─────────────────────────────────────┘
```

### 2️⃣ Quy Trình Lấy Xe (Remove Car)

```
┌──────────────────────┐
│  USER INPUT          │
│  Biển số xe: ABC123  │
└──────────┬───────────┘
           │
           ▼
┌──────────────────────────────────────┐
│  FIND CAR IN SYSTEM                  │
│  findCar(plate)                      │
└──────────┬──────────┬────────────────┘
      FOUND│        NOT FOUND
           │         │
           ▼         ▼
    ┌──────────┐  ┌──────────────┐
    │ CONTINUE │  │ ERROR: Not   │
    └────┬─────┘  │ Found in DB  │
         │         └──────────────┘
         ▼
┌──────────────────────────────────────┐
│  GET SLOT ID & FREE SLOT             │
│  slotID = cars[index].slotID         │
│  Mark slot as NOT occupied           │
└──────────┬──────────────────────────┘
           │
           ▼
┌──────────────────────────────────────┐
│  REMOVE CAR FROM ARRAY               │
│  Shift remaining cars up             │
│  Decrement carCount                  │
└──────────┬──────────────────────────┘
           │
           ▼
┌──────────────────────────────────────┐
│  UPDATE FILES                        │
│  - parking_data.txt (rewrite)        │
│  - history.txt (append [OUT] log)    │
└──────────┬──────────────────────────┘
           │
           ▼
┌──────────────────────────────────────┐
│  SUCCESS: CAR REMOVED                │
└──────────────────────────────────────┘
```

---

## A\* Algorithm Flow

```
START: (0, 0) → GOAL: Slot Position

┌─────────────────────────────────────┐
│  Initialize:                        │
│  - startNode.g = 0                  │
│  - startNode.h = heuristic()        │
│  - startNode.f = g + h              │
│  - Add to openList                  │
└────────────┬────────────────────────┘
             │
             ▼
    ┌────────────────────┐
    │ openList empty?    │
    └────┬────────────┬──┘
    YES  │         NO │
         │            ▼
         │  ┌─────────────────────────┐
         │  │ Extract node with       │
         │  │ minimum f value         │
         │  └────────┬────────────────┘
         │           │
         │           ▼
         │  ┌─────────────────────────┐
         │  │ Is it the GOAL?         │
         │  └────┬────────────────┬───┘
         │       │ YES       NO │
         │       ▼            ▼
         │    ┌──────────┐  ┌──────────────────┐
         │    │ Return  │  │ Check 4 neighbors│
         │    │ Path    │  │ (up,down,L,R)    │
         │    └──────────┘  └────────┬─────────┘
         │                           │
         │                    ┌──────▼────────┐
         │                    │ For each valid│
         │                    │ neighbor:     │
         │                    │ - Calculate   │
         │                    │   newG        │
         │                    │ - If newG <   │
         │                    │   neighbor.g: │
         │                    │   Update & add│
         │                    │   to openList │
         │                    └────────┬──────┘
         │                            │
         └────────────────────────────┘

OUTPUT: Complete path from start to goal
```

---

## File Structure trong Memory

### parkingMap[5][8]

```
       0  1  2  3  4  5  6  7
    ┌─────────────────────────┐
  0 │ 0  0  0  0  1  2  1  0  │  (0=đường, 1=vật, 2=slot)
  1 │ 0  1  1  0  2  1  2  0  │
  2 │ 0  0  1  0  0  0  0  0  │
  3 │ 1  0  1  0  2  0  1  1  │
  4 │ 2  0  2  1  1  0  2  1  │
    └─────────────────────────┘

Ví dụ:
- parkingMap[0][0] = 0 → Đường đi
- parkingMap[0][4] = 2 → Slot P1
- parkingMap[1][1] = 1 → Vật cản
```

---

## Node[][] Graph (5×8)

```
Mỗi Node chứa:
┌────────────────────────────┐
│ struct Node {              │
│   Position pos;  ← (x, y)  │
│   int g;         ← từ start│
│   int h;         ← đến goal│
│   int f;         ← g + h   │
│   Position parent;         │
│   bool visited;            │
│ }                          │
└────────────────────────────┘

A* sử dụng:
- g: Chi phí thực từ điểm start
- h: Ước tính chi phí đến goal (Manhattan)
- f: Chi phí dự kiến toàn bộ (g + h)

Chọn node có f nhỏ nhất → Đường đi tối ưu!
```

---

## Memory Allocation

```
┌────────────────────────────────────┐
│     ParkingLot struct              │
├────────────────────────────────────┤
│ Slot* slots;      ────────┐        │
│ Car* cars;        ────┐   │        │
│ HistoryEntry*    ─┐  │   │        │
│                   │  │   │        │
│ int slotCount     │  │   │        │
│ int carCount      │  │   │        │
│ int historyCount  │  │   │        │
│                   │  │   │        │
│ Node nodes[5][8]  │  │   │        │
└────────────────────────┼───────────┘
                       │   │   │
    ┌──────────────────┘   │   │
    │        ┌──────────────┘   │
    │        │       ┌──────────┘
    │        │       │
    ▼        ▼       ▼
  Slot[]  Car[]  HistoryEntry[]
    │        │       │
    │        │       └─→ "text[100]"
    │        │
    │        └─→ plate[20], slotID[10]
    │
    └─→ id[10], pos, occupied
```

---

## Luồng Hoạt Động Menu

```
┌──────────────────────────────────────┐
│         MAIN MENU                    │
│  Nhập lựa chọn 0-7                  │
└──────────────┬───────────────────────┘
               │
       ┌───────┴────────┬─────────┬──────┬──────┬──────┬─────┐
       │                │         │      │      │      │     │
      ▼1              ▼2        ▼3     ▼4     ▼5     ▼6    ▼7  0
┌────────────┐ ┌────────────┐ ┌───┐ ┌──────┐ ┌───┐ ┌──┐ ┌──┐ │
│  parkCar   │ │ removeCar  │ │Map│ │Slot  │ │Car│ │His│ │Rst│ EXIT
│   UI()     │ │    UI()    │ │   │ │      │ │   │ │   │ │tem│
└────────────┘ └────────────┘ └───┘ └──────┘ └───┘ └──┘ └──┘ │
    │              │            │      │       │     │    │  │
    └──┬───────────┴────────────┴──────┴───────┴────┴────┴──┘
       │
       └─→ LOOP back to MENU or EXIT
```

---

## Summary

**Hệ thống được thiết kế theo kiến trúc 3-tier:**

1. **Presentation Layer (UI)** - Giao diện người dùng
2. **Business Logic Layer** - Xử lý nghiệp vụ + A\* Algorithm
3. **Data Layer** - Quản lý dữ liệu và persistence

**Tính năng chính:**

- ✅ A\* pathfinding optimization
- ✅ Automatic nearest slot detection
- ✅ Real-time visualization
- ✅ Persistent data storage
- ✅ Complete transaction logging

---
