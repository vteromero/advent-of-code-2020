#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  int ship_x = 0;
  int ship_y = 0;
  int wp_x = 10;
  int wp_y = 1;

  for (string line; getline(cin, line); ) {
    char action = line[0];
    int value = stoll(line.substr(1));
    int temp = 0;

    switch (action) {
      case 'N':
        wp_y += value;
        break;
      case 'S':
        wp_y -= value;
        break;
      case 'E':
        wp_x += value;
        break;
      case 'W':
        wp_x -= value;
        break;
      case 'L':
        switch (value) {
          case 0:
          case 360:
            break;
          case 90:
            temp = wp_x;
            wp_x = - wp_y;
            wp_y = temp;
            break;
          case 180:
            wp_x = - wp_x;
            wp_y = - wp_y;
            break;
          case 270:
            temp = wp_x;
            wp_x = wp_y;
            wp_y = - temp;
            break;
        }
        break;
      case 'R':
        switch (value) {
          case 0:
          case 360:
            break;
          case 90:
            temp = wp_x;
            wp_x = wp_y;
            wp_y = - temp;
            break;
          case 180:
            wp_x = - wp_x;
            wp_y = - wp_y;
            break;
          case 270:
            temp = wp_x;
            wp_x = - wp_y;
            wp_y = temp;
            break;
        }
        break;
      case 'F':
        ship_x += wp_x * value;
        ship_y += wp_y * value;
        break;
    }

    // cout << "ship: (" << ship_x << ", " << ship_y << ")" << endl;
    // cout << "wp: (" << wp_x << ", " << wp_y << ")" << endl;
    // cout << endl;
  }

  cout << (abs(ship_x) + abs(ship_y)) << endl;

  return 0;
}
