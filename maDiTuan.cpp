#include <iostream>
#include <vector>

using namespace std;

// Kích thước bàn cờ
const int N = 8;

// Hàm kiểm tra vị trí hợp lệ
bool isValid(int x, int y, const vector<vector<bool>>& chessboard) {
  return (x >= 0 && x < N && y >= 0 && y < N && !chessboard[x][y]);
}

// Hàm di chuyển con mã
void moveKnight(vector<vector<bool>>& chessboard, int x, int y, int move, vector<pair<int, int>>& tour) {
  // Đánh dấu ô hiện tại là đã đi
  chessboard[x][y] = true;

  // Lưu vị trí hiện tại vào danh sách tour
  tour.push_back({x, y});

  // Liệt kê các nước đi hợp lệ
  vector<pair<int, int>> moves = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

  // Thử di chuyển đến mỗi ô hợp lệ
  for (const pair<int, int>& dir : moves) {
    int newX = x + dir.first;
    int newY = y + dir.second;

    if (isValid(newX, newY, chessboard)) {
      moveKnight(chessboard, newX, newY, move + 1, tour);

      // Quay lại ô hiện tại để thử di chuyển sang ô khác
      chessboard[newX][newY] = false;
      tour.pop_back();
    }
  }
}

int main() {
  // Khởi tạo bàn cờ
  vector<vector<bool>> chessboard(N, vector<bool>(N, false));

  // Nhập thông tin vị trí xuất phát
  int startX, startY;
  cout << "Nhập vị trí xuất phát của con mã (hàng, cột): ";
  cin >> startX >> startY;

  // Kiểm tra vị trí hợp lệ
  if (!isValid(startX, startY, chessboard)) {
    cout << "Vị trí xuất phát không hợp lệ!" << endl;
    return 1;
  }

  // Danh sách lưu trữ các nước đi
  vector<pair<int, int>> tour;

  // Di chuyển con mã và lưu trữ các nước đi
  moveKnight(chessboard, startX, startY, 1, tour);

  // Hiển thị kết quả
  if (tour.size() == N * N) {
    cout << "Danh sách các nước đi của con mã:" << endl;
    for (int i = 0; i < tour.size(); i++) {
      cout << i + 1 << ": (" << tour[i].first << ", " << tour[i].second << ")" << endl;
    }
  } else {
    cout << "Không tìm thấy đường đi cho con mã!" << endl;
  }

  return 0;
}