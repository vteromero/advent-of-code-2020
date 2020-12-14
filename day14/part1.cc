#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

uint64_t apply_mask(const string& mask, uint64_t value) {
  uint64_t new_value = value;

  for (size_t i = 0; i < 36; i++) {
    size_t j = 35 - i;
    switch (mask[i]) {
      case '0':
        new_value &= ~(1UL << j);
        break;
      case '1':
        new_value |= 1UL << j;
        break;
    }
  }

  return new_value;
}

int main() {
  string mask;
  unordered_map<uint64_t, uint64_t> mem;

  for (string line; getline(cin, line); ) {
    const string mask_del = "mask = ";
    uint64_t pos, val;

    if (line.substr(0, mask_del.size()) == mask_del) {
      mask = line.substr(mask_del.size());
    } else {
      sscanf(line.c_str(), "mem[%lu] = %lu", &pos, &val);
      mem[pos] = apply_mask(mask, val);
    }
  }

  uint64_t sum = 0;
  for (auto it = mem.begin(); it != mem.end(); it++) {
    sum += it->second;
  }

  cout << sum << endl;

  return 0;
}
