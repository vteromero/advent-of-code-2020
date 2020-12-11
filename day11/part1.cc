#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const vector<int> delta_r {-1, -1, -1, 0, 0, 1, 1, 1};
const vector<int> delta_c {-1, 0, 1, -1, 1, -1, 0, 1};

int adjacent_occupied(int r, int c, const vector<string>& layout) {
  int rows = layout.size();
  int columns = layout[0].size();
  int occupied = 0;

  for (size_t i = 0; i < delta_r.size(); i++) {
    int rr = r + delta_r[i];
    int cc = c + delta_c[i];

    if (rr < 0 || rr >= rows || cc < 0 || c >= columns) {
      continue;
    }

    occupied += layout[rr][cc] == '#';
  }

  return occupied;
}

int count_occupied(const vector<string>& layout) {
  int count = 0;
  for (size_t r = 0; r < layout.size(); r++) {
    for (size_t c = 0; c < layout[r].size(); c++) {
      count += layout[r][c] == '#';
    }
  }
  return count;
}

int main() {
  vector<string> layout;

  for (string line; getline(cin, line); ) {
    layout.push_back(line);
  }

  size_t rows = layout.size();
  size_t columns = layout[0].size();

  while (1) {
    vector<string> new_layout(rows, string(columns, '.'));

    for (size_t r = 0; r < rows; r++) {
      for (size_t c = 0; c < columns; c++) {
        char ch = layout[r][c];
        int adj = adjacent_occupied(r, c, layout);

        switch (ch) {
          case 'L':
            if (adj == 0) {
              new_layout[r][c] = '#';
            } else {
              new_layout[r][c] = 'L';
            }
            break;
          case '#':
            if (adj >= 4) {
              new_layout[r][c] = 'L';
            } else {
              new_layout[r][c] = '#';
            }
            break;
        }
      }
    }

    // for (size_t i = 0; i < rows; i++) {
    //   cout << new_layout[i] << endl;
    // }
    // cout << endl << endl;

    if (new_layout == layout) {
      cout << count_occupied(new_layout) << endl;
      break;
    } else {
      layout.assign(new_layout.begin(), new_layout.end());
    }
  }

  return 0;
}
