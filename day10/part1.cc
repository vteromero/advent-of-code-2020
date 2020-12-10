#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  vector<uint64_t> adapters;

  for (string line; getline(cin, line); ) {
    adapters.push_back(stoull(line));
  }

  sort(adapters.begin(), adapters.end());

  uint64_t diff_1_count = 0;
  uint64_t diff_3_count = 1;
  uint64_t last = 0;

  for (size_t i = 0; i < adapters.size(); i++) {
    uint64_t diff = adapters[i] - last;

    if (diff == 1) {
      diff_1_count++;
    } else if (diff == 3) {
      diff_3_count++;
    }

    last = adapters[i];
  }

  cout << (diff_1_count * diff_3_count) << endl;

  return 0;
}
