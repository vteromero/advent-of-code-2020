#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  int x = 0;
  int y = 0;
  int degrees = 0;

  for (string line; getline(cin, line); ) {
    char action = line[0];
    int value = stoi(line.substr(1));

    switch (action) {
      case 'N':
        y += value;
        break;
      case 'S':
        y -= value;
        break;
      case 'E':
        x += value;
        break;
      case 'W':
        x -= value;
        break;
      case 'L':
        degrees = (degrees + value) % 360;
        break;
      case 'R':
        degrees = (degrees - value + 360) % 360;
        break;
      case 'F':
        switch (degrees) {
          case 0:
          case 360:
            x += value;
            break;
          case 90:
            y += value;
            break;
          case 180:
            x -= value;
            break;
          case 270:
            y -= value;
            break;
        }
        break;
    }
  }

  cout << (abs(x) + abs(y)) << endl;

  return 0;
}
