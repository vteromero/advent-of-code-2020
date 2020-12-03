#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  vector<string> map;

  for (string line; getline(cin, line); ) {
    map.push_back(line);
  }

  size_t tree_count = 0;
  size_t rows = map.size();
  size_t columns = map[0].size();
  size_t c = 0;

  for (size_t r = 1; r < rows; r++) {
    c = (c + 3) % columns;
    if (map[r][c] == '#') {
      tree_count++;
    }
  }

  cout << tree_count << endl;

  return 0;
}
