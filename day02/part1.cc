#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  size_t valid_passwords = 0;

  for (string line; getline(cin, line); ) {
    char buf[100];
    size_t min, max;
    char letter;

    sscanf(line.c_str(), "%lu-%lu %c: %s", &min, &max, &letter, buf);

    string password(buf);
    size_t password_len = password.length();
    size_t count = 0;

    for (size_t i = 0; i < password_len; i++) {
      if (password[i] == letter) {
        count++;
      }
    }

    if (count >= min && count <= max) {
      valid_passwords++;
    }
  }

  cout << valid_passwords << endl;

  return 0;
}
