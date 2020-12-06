#include <iostream>
#include <string>
#include <vector>

using namespace std;

size_t count_all_yes(const vector<string>& group) {
  size_t questions = 'z' - 'a' + 1;
  size_t people = group.size();
  vector<size_t> answers_count = vector<size_t>(questions, 0);

  for (size_t i = 0; i < people; i++) {
    const string &person = group[i];

    for (size_t j = 0; j < person.size(); j++) {
      size_t idx = person[j] - 'a';
      answers_count[idx]++;
    }
  }

  size_t count = 0;
  for (size_t i = 0; i < questions; i++) {
    count += (size_t)(answers_count[i] == people);
  }

  return count;
}

int main() {
  vector<string> group;
  size_t total = 0;

  for (string line; getline(cin, line); ) {
    if (line.empty()) {
      total += count_all_yes(group);
      group.clear();
    } else {
      group.push_back(line);
    }
  }

  total += count_all_yes(group);

  cout << total << endl;

  return 0;
}
