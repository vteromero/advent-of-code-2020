#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  size_t valid_passwords = 0;

  for (string line; getline(cin, line); ) {
    char buf[100];
    size_t pos1, pos2;
    char letter;

    sscanf(line.c_str(), "%lu-%lu %c: %s", &pos1, &pos2, &letter, buf);

    string password(buf);
    size_t password_len = password.length();

    bool pos1_valid = (pos1 >= 1 && pos1 <= password_len) && (password[pos1 - 1] == letter);
    bool pos2_valid = (pos2 >= 1 && pos2 <= password_len) && (password[pos2 - 1] == letter);

    if (pos1_valid != pos2_valid) {
      valid_passwords++;
    }
  }

  cout << valid_passwords << endl;

  return 0;
}
