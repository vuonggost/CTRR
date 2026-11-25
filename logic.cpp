#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>

using namespace std;

// ======================================================
// KICH THUOC BAI XE
// ======================================================

const int ROW = 5;
const int COL = 8;

// ======================================================
// MAP BAI XE
//
// 0 = DUONG DI
// 1 = VAT CAN
// 2 = O DO XE
// ======================================================

int parkingMap[ROW][COL] =
    {
        {0, 0, 0, 0, 2, 0, 2, 0},
        {0, 1, 1, 0, 2, 0, 2, 0},
        {2, 0, 0, 0, 2, 0, 2, 0},
        {2, 1, 1, 0, 2, 0, 2, 0},
        {2, 2, 2, 2, 2, 2, 2, 2}};

// ======================================================
// STRUCT TOA DO
// ======================================================

struct Position
{
    int x;
    int y;
};

// ======================================================
// NODE CHO A*
// ======================================================

struct Node
{
    Position pos;
    int g, h, f;
    Position parent;
    bool visited;
};

// ======================================================
// SLOT XE
// ======================================================

struct Slot
{
    char id[10];
    Position pos;
    bool occupied;
};

// ======================================================
// XE
// ======================================================

struct Car
{
    char plate[20];
    char slotID[10];
};

// ======================================================
// HISTORY ENTRY
// ======================================================

struct HistoryEntry
{
    char text[100];
};

// ======================================================
// QUEUE NODE CHO A*
// ======================================================

struct QueueNode
{
    Node *nodePtr;
    int priority;
};

// ======================================================
// PATHFINDER FUNCTIONS
// ======================================================

// Kiểm tra xem tọa độ (x,y) có hợp lệ không (trong phạm vi bản đồ và không là vật cản)
bool isValid(int x, int y)
{
    return x >= 0 && x < ROW && y >= 0 && y < COL && parkingMap[x][y] != 1;
}

// Tính khoảng cách Manhattan giữa hai điểm (được sử dụng trong thuật toán A*)
int heuristic(Position a, Position b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// Khôi phục toàn bộ node (đặt lại các giá trị ban đầu cho thuật toán A*)
void resetNodes(Node nodes[ROW][COL])
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            nodes[i][j].g = 999999;
            nodes[i][j].h = 0;
            nodes[i][j].f = 999999;
            nodes[i][j].visited = false;
            nodes[i][j].parent.x = -1;
            nodes[i][j].parent.y = -1;
        }
    }
}

// Chèn node vào hàng đợi theo thứ tự ưu tiên (dùng insertion sort)
void insertPriority(QueueNode queue[], int &size, Node *node, int priority)
{
    if (size >= ROW * COL)
        return;

    int pos = size;
    while (pos > 0 && queue[pos - 1].priority > priority)
    {
        queue[pos] = queue[pos - 1];
        pos--;
    }

    queue[pos].nodePtr = node;
    queue[pos].priority = priority;
    size++;
}

// Lấy node có độ ưu tiên nhỏ nhất từ hàng đợi
QueueNode extractMin(QueueNode queue[], int &size)
{
    QueueNode result = queue[0];
    for (int i = 0; i < size - 1; i++)
    {
        queue[i] = queue[i + 1];
    }
    size--;
    return result;
}

// In đường đi từ điểm bắt đầu đến điểm kết thúc (dùng đệ quy)
void printPath(Node nodes[ROW][COL], int x, int y)
{
    if (x == -1 || y == -1)
        return;

    printPath(nodes, nodes[x][y].parent.x, nodes[x][y].parent.y);

    cout << "(" << x << "," << y << ") ";
}

// Tính khoảng cách từ điểm bắt đầu đến điểm kết thúc bằng thuật toán A*
int getDistance(Node nodes[ROW][COL], Position start, Position goal)
{
    QueueNode openList[ROW * COL];
    int openSize = 0;

    resetNodes(nodes);

    Node *startNode = &nodes[start.x][start.y];
    startNode->pos = start;
    startNode->g = 0;
    startNode->h = heuristic(start, goal);
    startNode->f = startNode->g + startNode->h;

    insertPriority(openList, openSize, startNode, startNode->f);

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    while (openSize > 0)
    {
        QueueNode current = extractMin(openList, openSize);

        if (current.nodePtr->visited)
            continue;

        current.nodePtr->visited = true;

        if (current.nodePtr->pos.x == goal.x && current.nodePtr->pos.y == goal.y)
        {
            return current.nodePtr->g;
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = current.nodePtr->pos.x + dx[i];
            int ny = current.nodePtr->pos.y + dy[i];

            if (!isValid(nx, ny))
                continue;
            if (nodes[nx][ny].visited)
                continue;

            Node *neighbor = &nodes[nx][ny];
            int newG = current.nodePtr->g + 1;

            if (newG < neighbor->g)
            {
                neighbor->pos.x = nx;
                neighbor->pos.y = ny;
                neighbor->g = newG;
                neighbor->h = heuristic({nx, ny}, goal);
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->parent = current.nodePtr->pos;

                insertPriority(openList, openSize, neighbor, neighbor->f);
            }
        }
    }

    return 999999;
}

// Tìm và in đường đi từ điểm bắt đầu đến điểm kết thúc bằng thuật toán A*
void findPath(Node nodes[ROW][COL], Position start, Position goal)
{
    QueueNode openList[ROW * COL];
    int openSize = 0;

    resetNodes(nodes);

    Node *startNode = &nodes[start.x][start.y];
    startNode->pos = start;
    startNode->g = 0;
    startNode->h = heuristic(start, goal);
    startNode->f = startNode->g + startNode->h;

    insertPriority(openList, openSize, startNode, startNode->f);

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    while (openSize > 0)
    {
        QueueNode current = extractMin(openList, openSize);

        if (current.nodePtr->visited)
            continue;

        current.nodePtr->visited = true;

        if (current.nodePtr->pos.x == goal.x && current.nodePtr->pos.y == goal.y)
        {
            cout << "\nDuong di:\n";
            printPath(nodes, goal.x, goal.y);
            cout << endl;
            return;
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = current.nodePtr->pos.x + dx[i];
            int ny = current.nodePtr->pos.y + dy[i];

            if (!isValid(nx, ny))
                continue;
            if (nodes[nx][ny].visited)
                continue;

            Node *neighbor = &nodes[nx][ny];
            int newG = current.nodePtr->g + 1;

            if (newG < neighbor->g)
            {
                neighbor->pos.x = nx;
                neighbor->pos.y = ny;
                neighbor->g = newG;
                neighbor->h = heuristic({nx, ny}, goal);
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->parent = current.nodePtr->pos;

                insertPriority(openList, openSize, neighbor, neighbor->f);
            }
        }
    }

    cout << "Khong tim thay duong di\n";
}

// ======================================================
// STRUCT BAI GIU XE
// ======================================================

struct ParkingLot
{
    Slot *slots;
    Car *cars;
    HistoryEntry *history;

    int slotCount;
    int carCount;
    int historyCount;
    int maxSlots;
    int maxCars;
    int maxHistory;

    Node nodes[ROW][COL];
};

// ======================================================
// PARKING LOT FUNCTIONS
// ======================================================

// Khởi tạo bãi xe: cấp phát bộ nhớ động và tạo các slot xe
void initializeParkingLot(ParkingLot &lot, int maxSlots, int maxCars, int maxHistory)
{
    lot.slots = new Slot[maxSlots];
    lot.cars = new Car[maxCars];
    lot.history = new HistoryEntry[maxHistory];

    lot.maxSlots = maxSlots;
    lot.maxCars = maxCars;
    lot.maxHistory = maxHistory;

    lot.slotCount = 0;
    lot.carCount = 0;
    lot.historyCount = 0;

    int number = 1;
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (parkingMap[i][j] == 2 && lot.slotCount < maxSlots)
            {
                sprintf(lot.slots[lot.slotCount].id, "P%d", number);
                lot.slots[lot.slotCount].pos.x = i;
                lot.slots[lot.slotCount].pos.y = j;
                lot.slots[lot.slotCount].occupied = false;

                lot.slotCount++;
                number++;
            }
        }
    }
}

// Giải phóng bộ nhớ động của bãi xe
void destroyParkingLot(ParkingLot &lot)
{
    delete[] lot.slots;
    delete[] lot.cars;
    delete[] lot.history;
}

// Tìm xe theo biển số, trả về index nếu tìm thấy, -1 nếu không
int findCar(ParkingLot &lot, const char *plate)
{
    for (int i = 0; i < lot.carCount; i++)
    {
        if (strcmp(lot.cars[i].plate, plate) == 0)
            return i;
    }
    return -1;
}

// Tìm slot xe theo ID, trả về index nếu tìm thấy, -1 nếu không
int findSlot(ParkingLot &lot, const char *id)
{
    for (int i = 0; i < lot.slotCount; i++)
    {
        if (strcmp(lot.slots[i].id, id) == 0)
            return i;
    }
    return -1;
}

// Sắp xếp các slot trống theo khoảng cách từ điểm vào (0,0) sử dụng bubble sort
void sortSlotsByDistance(Slot temp[], int count)
{
    Position start = {0, 0};

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            int d1 = heuristic(start, temp[i].pos);
            int d2 = heuristic(start, temp[j].pos);

            if (d2 < d1)
            {
                Slot tmp = temp[i];
                temp[i] = temp[j];
                temp[j] = tmp;
            }
        }
    }
}

// Tìm slot trống gần nhất bằng cách sắp xếp theo heuristic rồi kiểm tra đường đi
/*int findNearestSlot(ParkingLot &lot)
{
    Slot *temp = new Slot[lot.slotCount];
    int count = 0;

    for (int i = 0; i < lot.slotCount; i++)
    {
        if (!lot.slots[i].occupied)
        {
            temp[count] = lot.slots[i];
            count++;
        }
    }

    if (count == 0)
    {
        delete[] temp;
        return -1;
    }

    sortSlotsByDistance(temp, count);

    Position start = {0, 0};
    for (int i = 0; i < count; i++)
    {
        int distance = getDistance(lot.nodes, start, temp[i].pos);
        if (distance != 999999)
        {
            int result = findSlot(lot, temp[i].id);
            delete[] temp;
            return result;
        }
    }

    delete[] temp;
    return -1;
}*/
int findNearestSlot(ParkingLot &lot)
{
    Position start = {0, 0};

    int bestSlot = -1;
    int minDistance = 999999;

    // Duyet qua tat ca slot trong bai xe
    for (int i = 0; i < lot.slotCount; i++)
    {
        // Bo qua slot da co xe
        if (lot.slots[i].occupied)
        {
            continue;
        }

        // Lay vi tri slot hien tai
        Position goal = lot.slots[i].pos;

        // Kiem tra khoang cach duong di bang A*
        int distance = getDistance(lot.nodes, start, goal);

        // Neu khong tim thay duong di thi bo qua
        if (distance == 999999)
        {
            continue;
        }

        // Neu slot nay gan hon slot truoc do
        if (distance < minDistance)
        {
            minDistance = distance;
            bestSlot = i;
        }
    }

    // Tra ve index slot gan nhat
    // Neu khong co slot thi tra ve -1
    return bestSlot;
}


// Lưu thông tin xe vào file
void saveData(ParkingLot &lot, const char *filename)
{
    ofstream file(filename);

    for (int i = 0; i < lot.carCount; i++)
    {
        file << lot.cars[i].plate << " " << lot.cars[i].slotID << "\n";
    }

    file.close();
}

// Tải thông tin xe từ file vào bộ nhớ
void loadData(ParkingLot &lot, const char *filename)
{
    ifstream file(filename);

    char plate[20];
    char slotID[10];

    while (file >> plate >> slotID)
    {
        if (lot.carCount < lot.maxCars)
        {
            strcpy(lot.cars[lot.carCount].plate, plate);
            strcpy(lot.cars[lot.carCount].slotID, slotID);

            int slotIndex = findSlot(lot, slotID);
            if (slotIndex != -1)
            {
                lot.slots[slotIndex].occupied = true;
            }

            lot.carCount++;
        }
    }

    file.close();
}

// Lưu một bản ghi lịch sử vào file và mảng lịch sử
void saveHistory(ParkingLot &lot, const char *filename, const char *text)
{
    ofstream file(filename, ios::app);
    file << text << "\n";
    file.close();

    if (lot.historyCount < lot.maxHistory)
    {
        strcpy(lot.history[lot.historyCount].text, text);
        lot.historyCount++;
    }
}

// Tải toàn bộ lịch sử từ file vào bộ nhớ
void loadHistory(ParkingLot &lot, const char *filename)
{
    ifstream file(filename);
    char line[100];

    while (file.getline(line, sizeof(line)))
    {
        if (lot.historyCount < lot.maxHistory)
        {
            strcpy(lot.history[lot.historyCount].text, line);
            lot.historyCount++;
        }
    }

    file.close();
}

// Hiển thị danh sách tất cả các slot và trạng thái của chúng
void showSlots(ParkingLot &lot)
{
    cout << "\n===== SLOT =====\n";

    for (int i = 0; i < lot.slotCount; i++)
    {
        cout << lot.slots[i].id << " -> ";
        cout << (lot.slots[i].occupied ? "OCCUPIED" : "EMPTY") << "\n";
    }
}

// Gửi xe vào bãi: kiểm tra biển số, tìm slot trống gần nhất, lưu thông tin
void parkCar(ParkingLot &lot)
{
    char plate[20];

    cout << "\nNhap bien so: ";
    cin >> plate;

    if (findCar(lot, plate) != -1)
    {
        cout << "Xe da ton tai\n";
        return;
    }

    int slotIndex = findNearestSlot(lot);

    if (slotIndex == -1)
    {
        cout << "Bai xe da full\n";
        return;
    }

    if (lot.carCount >= lot.maxCars)
    {
        cout << "Bai xe day!\n";
        return;
    }

    lot.slots[slotIndex].occupied = true;
    strcpy(lot.cars[lot.carCount].plate, plate);
    strcpy(lot.cars[lot.carCount].slotID, lot.slots[slotIndex].id);
    lot.carCount++;

    Position start = {0, 0};
    Position goal = lot.slots[slotIndex].pos;

    cout << "\nSlot duoc chon: " << lot.slots[slotIndex].id << "\n";

    findPath(lot.nodes, start, goal);

    char historyText[100];
    sprintf(historyText, "[IN ] %s -> %s", plate, lot.slots[slotIndex].id);

    saveHistory(lot, "history.txt", historyText);
    saveData(lot, "parking_data.txt");

    cout << "Gui xe thanh cong\n";
}

// Lấy xe ra khỏi bãi: tìm xe, giải phóng slot, cập nhật dữ liệu
void removeCar(ParkingLot &lot)
{
    char plate[20];

    cout << "\nNhap bien so: ";
    cin >> plate;

    int index = findCar(lot, plate);

    if (index == -1)
    {
        cout << "Khong tim thay xe\n";
        return;
    }

    char slotID[10];
    strcpy(slotID, lot.cars[index].slotID);

    int slotIndex = findSlot(lot, slotID);
    if (slotIndex != -1)
    {
        lot.slots[slotIndex].occupied = false;
    }

    for (int i = index; i < lot.carCount - 1; i++)
    {
        lot.cars[i] = lot.cars[i + 1];
    }
    lot.carCount--;

    char historyText[100];
    sprintf(historyText, "[OUT] %s <- %s", plate, slotID);

    saveHistory(lot, "history.txt", historyText);
    saveData(lot, "parking_data.txt");

    cout << "Lay xe thanh cong\n";
}

// Hiển thị lịch sử hoạt động (theo thứ tự từ mới nhất đến cũ nhất)
void showHistory(ParkingLot &lot)
{
    cout << "\n===== HISTORY =====\n";

    for (int i = lot.historyCount - 1; i >= 0; i--)
    {
        cout << lot.history[i].text << "\n";
    }
}

// Khôi phục lại bãi xe: xóa tất cả xe, lịch sử, đặt lại trạng thái slot
void resetParkingLot(ParkingLot &lot)
{
    lot.carCount = 0;
    lot.historyCount = 0;

    for (int i = 0; i < lot.slotCount; i++)
    {
        lot.slots[i].occupied = false;
    }

    ofstream file1("parking_data.txt");
    file1.close();

    ofstream file2("history.txt");
    file2.close();

    cout << "\nReset thanh cong\n";
}

// Chạy menu chính của hệ thống quản lý bãi xe
void runParkingSystem(ParkingLot &lot)
{
    int choice;

    do
    {
        cout << "\n===== SMART PARKING =====\n";
        cout << "1. Gui xe\n";
        cout << "2. Lay xe\n";
        cout << "3. Xem slot\n";
        cout << "4. Xem history\n";
        cout << "5. Reset\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            parkCar(lot);
            break;
        case 2:
            removeCar(lot);
            break;
        case 3:
            showSlots(lot);
            break;
        case 4:
            showHistory(lot);
            break;
        case 5:
            resetParkingLot(lot);
            break;
        case 0:
            cout << "Thoat...\n";
            break;
        default:
            cout << "Lua chon khong hop le\n";
        }

    } while (choice != 0);
}


int main()
{
    ParkingLot lot;

    initializeParkingLot(lot, 20, 100, 500);

    loadData(lot, "parking_data.txt");
    loadHistory(lot, "history.txt");

    runParkingSystem(lot);

    destroyParkingLot(lot);

    return 0;
}