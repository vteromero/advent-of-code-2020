#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

void to_binary(string& bpass) {
  replace(bpass.begin(), bpass.end(), 'F', '0');
  replace(bpass.begin(), bpass.end(), 'B', '1');
  replace(bpass.begin(), bpass.end(), 'L', '0');
  replace(bpass.begin(), bpass.end(), 'R', '1');
}

int main() {
  int highest_id = 0;

  for (string bpass; getline(cin, bpass); ) {
    to_binary(bpass);

    int id = stoi(bpass, nullptr, 2);

    highest_id = max(highest_id, id);
  }

  cout << highest_id << endl;

  return 0;
}
