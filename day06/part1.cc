#include <iostream>
#include <string>
#include <vector>

using namespace std;

size_t count_any_yes(const vector<string>& group) {
  size_t n = 'z' - 'a' + 1;
  vector<bool> answers = vector<bool>(n, false);

  for (size_t i = 0; i < group.size(); i++) {
    const string &person = group[i];

    for (size_t j = 0; j < person.size(); j++) {
      size_t idx = person[j] - 'a';
      answers[idx] = true;
    }
  }

  size_t count = 0;
  for (size_t i = 0; i < n; i++) {
    count += answers[i];
  }

  return count;
}

int main() {
  vector<string> group;
  size_t total = 0;

  for (string line; getline(cin, line); ) {
    if (line.empty()) {
      total += count_any_yes(group);
      group.clear();
    } else {
      group.push_back(line);
    }
  }

  total += count_any_yes(group);

  cout << total << endl;

  return 0;
}
