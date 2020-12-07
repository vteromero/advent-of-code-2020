#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

string clean_name(const string& bag_name) {
  istringstream ss(bag_name);
  string piece, result;

  while (ss >> piece) {
    if (result.empty()) {
      result = piece;
    } else {
      result += "-" + piece;
    }
  }

  return result;
}

int main() {
  unordered_map<string, vector<string> > contain_bag;

  for (string line; getline(cin, line); ) {
    const string sep = " bags contain ";
    size_t sep_len = sep.length();
    size_t sep_pos = line.find(sep);
    string bag = line.substr(0, sep_pos);
    string content = line.substr(sep_pos + sep_len);
    string cleaned_bag_name = clean_name(bag);

    istringstream ss1(content);
    for (string item; getline(ss1, item, ','); ) {
      if (item == "no other bags" || item == "no other bags.") {
        continue;
      }

      string cleaned_item = item.substr(0, item.find(" bag"));
      size_t n;
      string bag_name;
      istringstream ss2(cleaned_item);

      ss2 >> n;
      getline(ss2, bag_name);

      string other_bag = clean_name(bag_name);
      if (contain_bag.find(other_bag) == contain_bag.end()) {
        contain_bag[other_bag] = vector<string>{cleaned_bag_name};
      } else {
        contain_bag[other_bag].push_back(cleaned_bag_name);
      }
    }
  }

  unordered_set<string> visited;
  queue<string> q;

  q.push("shiny-gold");

  while (!q.empty()) {
    string bag = q.front();
    q.pop();

    if (visited.find(bag) != visited.end()) {
      continue;
    }

    visited.insert(bag);

    auto it = contain_bag.find(bag);
    if (it == contain_bag.end()) {
      continue;
    }

    vector<string> &list = it->second;
    for (size_t i = 0; i < list.size(); i++) {
      q.push(list[i]);
    }
  }

  cout << (visited.size() - 1) << endl;

  return 0;
}
