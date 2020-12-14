#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

string calculate_mem_mask(const string& mask, uint64_t value) {
  string new_mask(mask.size(), 'X');

  for (size_t i = 0; i < 36; i++) {
    size_t j = 35 - i;

    switch (mask[i]) {
      case '0':
        new_mask[i] = (value & (1UL << j)) ? '1' : '0';
        break;
      case '1':
        new_mask[i] = '1';
        break;
      case 'X':
        new_mask[i] = 'X';
        break;
    }
  }

  return new_mask;
}

void write_values(
  string& mem_mask,
  uint64_t value,
  unordered_map<uint64_t, uint64_t>& mem,
  size_t pos)
{
  for (size_t i = pos; i < 36; i++) {
    if (mem_mask[i] == 'X') {
      string mem_mask_for_zero = string(mem_mask);
      mem_mask_for_zero[i] = '0';
      write_values(mem_mask_for_zero, value, mem, i + 1);

      string mem_mask_for_one = string(mem_mask);
      mem_mask_for_one[i] = '1';
      write_values(mem_mask_for_one, value, mem, i + 1);

      return;
    }
  }

  uint64_t address = stoull(mem_mask, nullptr, 2);

  mem[address] = value;
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
      string mem_mask = calculate_mem_mask(mask, pos);
      write_values(mem_mask, val, mem, 0);
    }
  }

  uint64_t sum = 0;
  for (auto it = mem.begin(); it != mem.end(); it++) {
    sum += it->second;
  }

  cout << sum << endl;

  return 0;
}
