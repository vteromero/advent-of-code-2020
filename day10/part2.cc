#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  vector<uint64_t> adapters;

  adapters.push_back(0);

  for (string line; getline(cin, line); ) {
    adapters.push_back(stoull(line));
  }

  sort(adapters.begin(), adapters.end());

  adapters.push_back(adapters[adapters.size() - 1] + 3);

  vector<uint64_t> dp(adapters.size(), 0);
  dp[0] = 1;

  for (size_t i = 1; i < adapters.size(); i++) {
    uint64_t current = adapters[i];

    for (size_t j = i; j-- > 0; ) {
      uint64_t prev = adapters[j];
      uint64_t diff = current - prev;

      if (diff > 3) {
        break;
      }

      dp[i] += dp[j];
    }
  }

  cout << dp[adapters.size() - 1] << endl;

  return 0;
}
