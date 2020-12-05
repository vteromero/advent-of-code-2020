#include <iostream>
#include <string>
#include <vector>

using namespace std;

int row(const string& row_str) {
  size_t len = row_str.length();
  int low = 0;
  int sz = 128;

  for (size_t i = 0; i < len; i++) {
    char c = row_str[i];
    sz /= 2;
    if (c == 'B') {
      low += sz;
    }
  }

  return low;
}

int column(const string& column_str) {
  size_t len = column_str.length();
  int low = 0;
  int sz = 8;

  for (size_t i = 0; i < len; i++) {
    char c = column_str[i];
    sz /= 2;
    if (c == 'R') {
      low += sz;
    }
  }

  return low;
}

int main() {
  int highest_id = 0;

  for (string bpass; getline(cin, bpass); ) {
    string row_str = bpass.substr(0, 7);
    string column_str = bpass.substr(7);

    int r = row(row_str);
    int c = column(column_str);
    int id = r * 8 + c;

    highest_id = max(highest_id, id);
  }

  cout << highest_id << endl;

  return 0;
}
