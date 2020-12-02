#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  vector<int> expenses;

  for(string expense; cin >> expense; ) {
    expenses.push_back(stoi(expense));
  }

  size_t expenses_sz = expenses.size();

  for (size_t i = 0; i < expenses_sz; i++) {
    for (size_t j = i + 1; j < expenses_sz; j++) {
      int e1 = expenses[i];
      int e2 = expenses[j];
      int sum = e1 + e2;

      if (sum == 2020) {
        cout << (e1 * e2) << endl;
      }
    }
  }

  return 0;
}
