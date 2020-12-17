#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int delta_z[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const int delta_y[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1, -1, -1, -1, 0, 0, 1, 1, 1, -1, -1, -1, 0, 0, 0, 1, 1, 1};
const int delta_x[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1};

void print_cube(const vector<vector<string> >& cube) {
  for (size_t i = 0; i < cube.size(); i++) {
    cout << "z=" << i << endl;
    for (size_t j = 0; j < cube[i].size(); j++) {
      cout << cube[i][j] << endl;
    }
    cout << endl;
  }
}

vector<vector<string> > extend_state(const vector<vector<string> >& state) {
  size_t n_z = state.size();
  size_t n_y = state[0].size();
  size_t n_x = state[0][0].size();
  vector<vector<string> > new_state(n_z + 2, vector<string>(n_y + 2, string(n_x + 2, '.')));

  for (size_t z = 0; z < n_z; z++) {
    for (size_t y = 0; y < n_y; y++) {
      for (size_t x = 0; x < n_x; x++) {
        new_state[z + 1][y + 1][x + 1] = state[z][y][x];
      }
    }
  }

  return new_state;
}

size_t count_neighbours(
  const vector<vector<string> >& state,
  int z,
  int y,
  int x)
{
  int n_z = state.size();
  int n_y = state[0].size();
  int n_x = state[0][0].size();
  size_t count = 0;

  for (size_t i = 0; i < 26; i++) {
    int zz = z + delta_z[i];
    int yy = y + delta_y[i];
    int xx = x + delta_x[i];

    if (zz >= 0 && zz < n_z &&
        yy >= 0 && yy < n_y &&
        xx >= 0 && xx < n_x) {
      count += state[zz][yy][xx] == '#';
    }
  }

  return count;
}

vector<vector<string> > calculate_next_state(vector<vector<string> >& state) {
  vector<vector<string> > extended_state = extend_state(state);
  size_t n_z = extended_state.size();
  size_t n_y = extended_state[0].size();
  size_t n_x = extended_state[0][0].size();
  vector<vector<string> > new_state(n_z, vector<string>(n_y, string(n_x, '.')));

  for (size_t z = 0; z < n_z; z++) {
    for (size_t y = 0; y < n_y; y++) {
      for (size_t x = 0; x < n_x; x++) {
        size_t active_neighbours = count_neighbours(extended_state, z, y, x);

        switch (extended_state[z][y][x]) {
          case '#':
            if (active_neighbours == 2 || active_neighbours == 3) {
              new_state[z][y][x] = '#';
            }
            break;
          case '.':
            if (active_neighbours == 3) {
              new_state[z][y][x] = '#';
            }
            break;
        }
      }
    }
  }

  return new_state;
}

size_t count_active(const vector<vector<string> >& state) {
  size_t n_z = state.size();
  size_t n_y = state[0].size();
  size_t n_x = state[0][0].size();
  size_t count = 0;

  for (size_t z = 0; z < n_z; z++) {
    for (size_t y = 0; y < n_y; y++) {
      for (size_t x = 0; x < n_x; x++) {
        count += state[z][y][x] == '#';
      }
    }
  }

  return count;
}

int main() {
  vector<string> initial_slice;
  vector<vector<string> > cube;

  for (string line; getline(cin, line); ) {
    initial_slice.push_back(line);
  }
  cube.push_back(initial_slice);

  // cout << "Before any cycle:" << endl;
  // print_cube(cube);

  for (size_t i = 0; i < 6; i++) {
    cube = calculate_next_state(cube);
    // cout << "Cycle " << i << ":" << endl;
    // print_cube(cube);
  }

  cout << count_active(cube) << endl;

  return 0;
}
