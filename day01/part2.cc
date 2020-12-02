#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  vector<uint64_t> expenses;

  for(string expense; cin >> expense; ) {
    expenses.push_back(stoull(expense));
  }

  size_t expenses_sz = expenses.size();

  for (size_t i = 0; i < expenses_sz; i++) {
    for (size_t j = i + 1; j < expenses_sz; j++) {
      for (size_t k = j + 1; k < expenses_sz; k++) {
        uint64_t e1 = expenses[i];
        uint64_t e2 = expenses[j];
        uint64_t e3 = expenses[k];
        uint64_t sum = e1 + e2 + e3;

        if (sum == 2020ULL) {
          cout << (e1 * e2 * e3) << endl;
        }
      }
    }
  }

  return 0;
}
