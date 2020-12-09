#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

bool valid_number(size_t pos, size_t preamble, const vector<uint64_t>& numbers) {
  uint64_t n = numbers[pos];
  unordered_set<uint64_t> sums;

  for (size_t i = pos - preamble; i < pos; i++) {
    for (size_t j = i + 1; j < pos; j++) {
      sums.insert(numbers[i] + numbers[j]);
    }
  }

  return sums.find(n) != sums.end();
}

int main() {
  vector<uint64_t> numbers;

  for (string line; getline(cin, line); ) {
    numbers.push_back(stoull(line));
  }

  const size_t preamble = 25;

  for (size_t i = preamble; i < numbers.size(); i++) {
    if (!valid_number(i, preamble, numbers)) {
      cout << numbers[i] << endl;
    }
  }

  return 0;
}
