#include <iostream>
#include <string>
#include <vector>

using namespace std;

const size_t slopes_size = 5;
const size_t slopes[slopes_size][2] = {
  {1, 1},
  {3, 1},
  {5, 1},
  {7, 1},
  {1, 2}
};

bool next_pos(size_t right_step, size_t down_step, size_t rows, size_t columns, size_t &r, size_t &c) {
  c = (c + right_step) % columns;
  r = r + down_step;
  return r < rows;
}

uint64_t slope_count(const vector<string>& map, size_t right_step, size_t down_step) {
  size_t rows = map.size();
  size_t columns = map[0].size();
  size_t r = 0;
  size_t c = 0;
  uint64_t tree_count = 0;

  while (next_pos(right_step, down_step, rows, columns, r, c)) {
    if (map[r][c] == '#') {
      tree_count++;
    }
  }

  return tree_count;
}

int main() {
  vector<string> map;

  for (string line; getline(cin, line); ) {
    map.push_back(line);
  }

  uint64_t m = 1;

  for (size_t i = 0; i < slopes_size; i++) {
    m *= slope_count(map, slopes[i][0], slopes[i][1]);
  }

  cout << m << endl;

  return 0;
}
