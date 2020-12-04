#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

bool valid_byr(const string& value) {
  int year = stoi(value);
  return year >= 1920 && year <= 2002;
}

bool valid_iyr(const string& value) {
  int year = stoi(value);
  return year >= 2010 && year <= 2020;
}

bool valid_eyr(const string& value) {
  int year = stoi(value);
  return year >= 2020 && year <= 2030;
}

bool valid_hgt(const string& value) {
  size_t value_len = value.length();

  if (value_len <= 2) return false;

  int quantity = stoi(value.substr(0, value_len - 2));
  string unit = value.substr(value_len - 2);

  if (unit == "cm") {
    return quantity >= 150 && quantity <= 193;
  } else if (unit == "in") {
    return quantity >= 59 && quantity <= 76;
  }

  return false;
}

bool valid_hcl(const string& value) {
  size_t value_len = value.length();

  if (value_len != 7) {
    return false;
  }

  for (size_t i = 1; i < value_len; i++) {
    char c = value[i];

    if (!(c >= 'a' && c <= 'f') && !(c >= '0' && c <= '9')) {
      return false;
    }
  }

  return true;
}

bool valid_ecl(const string& value) {
  unordered_set<string> valid_colors{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

  if (valid_colors.find(value) == valid_colors.end()) {
    return false;
  } else {
    return true;
  }
}

bool valid_pid(const string& value) {
  size_t value_len = value.length();

  if (value_len != 9) {
    return false;
  }

  for (size_t i = 0; i < value_len; i++) {
    char c = value[i];
    if ((c < '0') || (c > '9')) {
      return false;
    }
  }

  return true;
}

bool valid_passport(const string& passport) {
  istringstream ss(passport);
  unordered_map<string, bool> field_valid_map {
    {"byr", false},
    {"iyr", false},
    {"eyr", false},
    {"hgt", false},
    {"hcl", false},
    {"ecl", false},
    {"pid", false}
  };

  for (string field; ss >> field; ) {
    size_t separator_pos = field.find(':');
    string key = field.substr(0, separator_pos);
    string value = field.substr(separator_pos + 1);

    if (key == "byr") {
      field_valid_map["byr"] = valid_byr(value);
    } else if (key == "iyr") {
      field_valid_map["iyr"] = valid_iyr(value);
    } else if (key == "eyr") {
      field_valid_map["eyr"] = valid_eyr(value);
    } else if (key == "hgt") {
      field_valid_map["hgt"] = valid_hgt(value);
    } else if (key == "hcl") {
      field_valid_map["hcl"] = valid_hcl(value);
    } else if (key == "ecl") {
      field_valid_map["ecl"] = valid_ecl(value);
    } else if (key == "pid") {
      field_valid_map["pid"] = valid_pid(value);
    }
  }

  bool all_valid = true;
  for (auto it = field_valid_map.begin(); it != field_valid_map.end(); it++) {
    all_valid = all_valid && it->second;
  }

  return all_valid;
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
