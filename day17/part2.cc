#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int delta_w[] = {
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
const int delta_z[] = {
  -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

const int delta_y[] = {
  -1, -1, -1, 0, 0, 0, 1, 1, 1, -1, -1, -1, 0, 0, 0, 1, 1, 1, -1, -1, -1, 0, 0, 0, 1, 1, 1,
  -1, -1, -1, 0, 0, 0, 1, 1, 1, -1, -1, -1, 0, 0, 1, 1, 1, -1, -1, -1, 0, 0, 0, 1, 1, 1,
  -1, -1, -1, 0, 0, 0, 1, 1, 1, -1, -1, -1, 0, 0, 0, 1, 1, 1, -1, -1, -1, 0, 0, 0, 1, 1, 1
};

const int delta_x[] = {
  -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1,
  -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1,
  -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1
};

void print_state(const vector<vector<vector<string> > >& state) {
  for (size_t w = 0; w < state.size(); w++) {
    for (size_t z = 0; z < state[w].size(); z++) {
      cout << endl << "w=" << w << ", z=" << z << endl;
      for (size_t y = 0; y < state[w][z].size(); y++) {
        cout << state[w][z][y] << endl;
      }
    }
  }
}

vector<vector<vector<string> > > initial_state(const vector<string>& slice) {
  vector<vector<vector<string> > > state;
  vector<vector<string> > cube;

  cube.push_back(slice);
  state.push_back(cube);

  return state;
}

vector<vector<vector<string> > > extend_state(const vector<vector<vector<string> > >& state) {
  size_t n_w = state.size();
  size_t n_z = state[0].size();
  size_t n_y = state[0][0].size();
  size_t n_x = state[0][0][0].size();
  vector<vector<vector<string> > > new_state(n_w + 2, vector<vector<string> >(n_z + 2, vector<string>(n_y + 2, string(n_x + 2, '.'))));

  for (size_t w = 0; w < n_w; w++) {
    for (size_t z = 0; z < n_z; z++) {
      for (size_t y = 0; y < n_y; y++) {
        for (size_t x = 0; x < n_x; x++) {
          new_state[w + 1][z + 1][y + 1][x + 1] = state[w][z][y][x];
        }
      }
    }
  }

  return new_state;
}

size_t count_neighbours(
  const vector<vector<vector<string> > >& state,
  int w,
  int z,
  int y,
  int x)
{
  int n_w = state.size();
  int n_z = state[0].size();
  int n_y = state[0][0].size();
  int n_x = state[0][0][0].size();
  size_t count = 0;

  for (size_t i = 0; i < 80; i++) {
    int ww = w + delta_w[i];
    int zz = z + delta_z[i];
    int yy = y + delta_y[i];
    int xx = x + delta_x[i];

    if (ww >= 0 && ww < n_w &&
        zz >= 0 && zz < n_z &&
        yy >= 0 && yy < n_y &&
        xx >= 0 && xx < n_x) {
      count += state[ww][zz][yy][xx] == '#';
    }
  }

  return count;
}

vector<vector<vector<string> > > next_state(const vector<vector<vector<string> > >& state) {
  vector<vector<vector<string> > > extended_state =  extend_state(state);
  size_t n_w = extended_state.size();
  size_t n_z = extended_state[0].size();
  size_t n_y = extended_state[0][0].size();
  size_t n_x = extended_state[0][0][0].size();
  vector<vector<vector<string> > > new_state(n_w, vector<vector<string> >(n_z, vector<string>(n_y, string(n_x, '.'))));

  for (size_t w = 0; w < n_w; w++) {
    for (size_t z = 0; z < n_z; z++) {
      for (size_t y = 0; y < n_y; y++) {
        for (size_t x = 0; x < n_x; x++) {
          size_t active_neighbours = count_neighbours(extended_state, w, z, y, x);

          switch (extended_state[w][z][y][x]) {
            case '#':
              if (active_neighbours == 2 || active_neighbours == 3) {
                new_state[w][z][y][x] = '#';
              }
              break;
            case '.':
              if (active_neighbours == 3) {
                new_state[w][z][y][x] = '#';
              }
              break;
          }
        }
      }
    }
  }

  return new_state;
}

size_t count_active(const vector<vector<vector<string> > >& state) {
  size_t n_w = state.size();
  size_t n_z = state[0].size();
  size_t n_y = state[0][0].size();
  size_t n_x = state[0][0][0].size();
  size_t count = 0;

  for (size_t w = 0; w < n_w; w++) {
    for (size_t z = 0; z < n_z; z++) {
      for (size_t y = 0; y < n_y; y++) {
        for (size_t x = 0; x < n_x; x++) {
          count += state[w][z][y][x] == '#';
        }
      }
    }
  }

  return count;
}

int main() {
  vector<string> slice;

  for (string line; getline(cin, line); ) {
    slice.push_back(line);
  }

  vector<vector<vector<string> > > state = initial_state(slice);

  // cout << "Before any cycle:" << endl;
  // print_state(state);

  for (size_t i = 0; i < 6; i++) {
    state = next_state(state);
    // cout << "Cycle " << i << ":" << endl;
    // print_state(state);
  }

  cout << count_active(state) << endl;

  return 0;
}
