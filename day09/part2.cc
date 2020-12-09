#include <algorithm>
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

uint64_t sum_min_max(size_t i, size_t j, const vector<uint64_t>& numbers) {
  uint64_t smallest = numeric_limits<uint64_t>::max();
  uint64_t largest = 0;

  for (size_t k = i; k <= j; k++) {
    smallest = min(smallest, numbers[k]);
    largest = max(largest, numbers[k]);
  }

  return smallest + largest;
}

uint64_t encryption_weakness(uint64_t n, const vector<uint64_t>& numbers) {
  for (size_t i = 0; i < numbers.size(); i++) {
    uint64_t sum = 0;

    for (size_t j = i + 1; j < numbers.size(); j++) {
      sum += numbers[j];

      if (sum == n) {
        return sum_min_max(i, j, numbers);
      }
    }
  }

  return 0;
}

int main() {
  vector<uint64_t> numbers;

  for (string line; getline(cin, line); ) {
    numbers.push_back(stoull(line));
  }

  const size_t preamble = 25;

  for (size_t i = preamble; i < numbers.size(); i++) {
    if (!valid_number(i, preamble, numbers)) {
      cout << encryption_weakness(numbers[i], numbers) << endl;
    }
  }

  return 0;
}
