#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

struct BagCount {
  string name;
  size_t count;
};

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

size_t count_recursive(
  const string& bag,
  size_t n,
  unordered_map<string, vector<BagCount> >& bag_to_other_bags)
{
  vector<BagCount> &other_bags = bag_to_other_bags[bag];
  size_t other_bags_sz = other_bags.size();
  size_t total_count = 0;

  for (size_t i = 0; i < other_bags_sz; i++) {
    BagCount &bag_count = other_bags[i];
    total_count += bag_count.count + count_recursive(bag_count.name, bag_count.count, bag_to_other_bags);
  }

  return n * total_count;
}

int main() {
  unordered_map<string, vector<BagCount> > bag_to_other_bags;

  for (string line; getline(cin, line); ) {
    const string sep = " bags contain ";
    size_t sep_len = sep.length();
    size_t sep_pos = line.find(sep);
    string bag = line.substr(0, sep_pos);
    string content = line.substr(sep_pos + sep_len);
    string cleaned_bag_name = clean_name(bag);

    bag_to_other_bags[cleaned_bag_name] = vector<BagCount>();

    istringstream ss1(content);
    for (string item; getline(ss1, item, ','); ) {
      if (item == "no other bags" || item == "no other bags.") {
        continue;
      }

      string cleaned_item = item.substr(0, item.find(" bag"));
      istringstream ss2(cleaned_item);
      BagCount bag_count;

      ss2 >> bag_count.count;
      getline(ss2, bag_count.name);
      bag_count.name = clean_name(bag_count.name);

      bag_to_other_bags[cleaned_bag_name].push_back(bag_count);
    }
  }

  cout << count_recursive("shiny-gold", 1, bag_to_other_bags) << endl;

  return 0;
}
