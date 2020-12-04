#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

bool valid_passport(const string& passport) {
  istringstream ss(passport);
  unordered_set<string> fields_set {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};

  for (string field; ss >> field; ) {
    string key = field.substr(0, field.find(':'));
    fields_set.erase(key);
  }

  switch (fields_set.size()) {
    case 0:
      return true;
    case 1: {
      string key(*fields_set.begin());
      if (key == "cid") {
        return true;
      } else {
        return false;
      }
    }
    default:
      return false;
  }
}

int main() {
  string passport;
  int valid_count = 0;

  for (string line; getline(cin, line); ) {
    if (line.empty()) {
      valid_count += valid_passport(passport);
      passport.clear();
    } else {
      passport.append(" ").append(line);
    }
  }

  if (!passport.empty()) {
    valid_count += valid_passport(passport);
  }

  cout << valid_count << endl;

  return 0;
}
