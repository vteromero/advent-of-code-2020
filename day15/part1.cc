#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
  unordered_map<int, int> prev_spoken;
  int turn = 1, last_spoken;

  for(string line; getline(cin, line, ','); ) {
    last_spoken = stoi(line);
    prev_spoken[last_spoken] = turn++;
  }

  for (; turn <= 2020; turn++) {
    auto found = prev_spoken.find(last_spoken);

    int last_turn = turn - 1;
    int prev_spoken_turn = (found == prev_spoken.end()) ? last_turn : found->second;
    int diff = last_turn - prev_spoken_turn;

    prev_spoken[last_spoken] = last_turn;

    last_spoken = diff;
  }

  cout << last_spoken << endl;

  return 0;
}
