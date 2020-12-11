#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
  * Directions:
  * 0: diagonal top left
  * 1: top
  * 2: diagonal top right
  * 3: left
  * 4: right
  * 5: diagonal bottom left
  * 6: bottom
  * 7: diagonal bottom right
  */

const vector<int> delta1_r {-1, -1, -1, 0};
const vector<int> delta1_c {-1, 0, 1, -1};
const vector<int> delta2_r {0, 1, 1, 1};
const vector<int> delta2_c {1, -1, 0, 1};

void calculate_dir_layouts(
  const vector<string>& layout,
  vector< vector<string> >& dir_layouts)
{
  int rows = layout.size();
  int columns = layout[0].size();

  for (int i = 0; i < 4; i++) {
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < columns; c++) {
        int rr = r + delta1_r[i];
        int cc = c + delta1_c[i];

        if (rr < 0 || rr >= rows || cc < 0 || c >= columns) {
          continue;
        }

        if (layout[rr][cc] == '.') {
          dir_layouts[i][r][c] = dir_layouts[i][rr][cc];
        } else {
          dir_layouts[i][r][c] = layout[rr][cc];
        }
      }
    }
  }

  for (int i = 0, j = 4; i < 4; i++, j++) {
    for (int r = rows; r-- > 0; ) {
      for (int c = columns; c-- > 0; ) {
        int rr = r + delta2_r[i];
        int cc = c + delta2_c[i];

        if (rr < 0 || rr >= rows || cc < 0 || c >= columns) {
          continue;
        }

        if (layout[rr][cc] == '.') {
          dir_layouts[j][r][c] = dir_layouts[j][rr][cc];
        } else {
          dir_layouts[j][r][c] = layout[rr][cc];
        }
      }
    }
  }
}

int adjacent_occupied(int r, int c, const vector< vector<string> >& dir_layouts) {
  int count = 0;
  for (size_t i = 0; i < 8; i++) {
    count += dir_layouts[i][r][c] == '#';
  }
  return count;
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
    vector< vector<string> > dir_layouts(8, vector<string>(rows, string(columns, '.')));
    vector<string> new_layout(rows, string(columns, '.'));

    calculate_dir_layouts(layout, dir_layouts);

    // for (size_t i = 0; i < 8; i++) {
    //   cout << i << ":" << endl;
    //   for (size_t j = 0; j < rows; j++) {
    //     cout << dir_layouts[i][j] << endl;
    //   }
    //   cout << endl;
    // }

    for (size_t r = 0; r < rows; r++) {
      for (size_t c = 0; c < columns; c++) {
        char ch = layout[r][c];
        int adj = adjacent_occupied(r, c, dir_layouts);

        switch (ch) {
          case 'L':
            if (adj == 0) {
              new_layout[r][c] = '#';
            } else {
              new_layout[r][c] = 'L';
            }
            break;
          case '#':
            if (adj >= 5) {
              new_layout[r][c] = 'L';
            } else {
              new_layout[r][c] = '#';
            }
            break;
        }
      }
    }

    // cout << "new layout:" << endl;
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
