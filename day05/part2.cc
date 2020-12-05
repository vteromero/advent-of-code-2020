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
  vector<bool> available_seats(1024, true);

  for (string bpass; getline(cin, bpass); ) {
    string row_str = bpass.substr(0, 7);
    string column_str = bpass.substr(7);

    int r = row(row_str);
    int c = column(column_str);
    int id = r * 8 + c;

    available_seats[id] = false;
  }

  size_t i, j;

  for (i = 0; (i < available_seats.size() && available_seats[i]); i++) {}
  for (j = available_seats.size(); (j-- > 0 && available_seats[j]); ) {}

  for (size_t k = i; k <= j; k++) {
    if (available_seats[k]) {
      cout << k << endl;
    }
  }

  return 0;
}
