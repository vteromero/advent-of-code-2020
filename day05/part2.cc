#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void to_binary(string& bpass) {
  replace(bpass.begin(), bpass.end(), 'F', '0');
  replace(bpass.begin(), bpass.end(), 'B', '1');
  replace(bpass.begin(), bpass.end(), 'L', '0');
  replace(bpass.begin(), bpass.end(), 'R', '1');
}

int main() {
  vector<bool> available_seats(1024, true);
  int min_id = 1024, max_id = 0;

  for (string bpass; getline(cin, bpass); ) {
    to_binary(bpass);

    int id = stoi(bpass, nullptr, 2);

    min_id = min(min_id, id);
    max_id = max(max_id, id);

    available_seats[id] = false;
  }

  for (int i = min_id; i <= max_id; i++) {
    if (available_seats[i]) {
      cout << i << endl;
    }
  }

  return 0;
}
