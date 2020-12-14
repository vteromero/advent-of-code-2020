#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Bus {
  uint64_t id;
  uint64_t next_time;
};

bool cmp(const Bus& b1, const Bus& b2) {
  const uint64_t t1 = b1.next_time;
  const uint64_t t2 = b2.next_time;
  return (t1 < t2);
}

int main() {
  uint64_t t0;
  string line;
  vector<Bus> buses;

  getline(cin, line);
  t0 = stoull(line);

  getline(cin, line);
  istringstream ss(line);
  for (string id; getline(ss, id, ','); ) {
    if (id != "x") {
      buses.push_back({stoull(id), 0});
    }
  }

  for (size_t i = 0; i < buses.size(); i++) {
    uint64_t m = t0 % buses[i].id;

    if (m == 0) {
      buses[i].next_time = t0;
    } else {
      buses[i].next_time = t0 + buses[i].id - m;
    }
  }

  sort(buses.begin(), buses.end(), cmp);

  Bus earliest_bus = buses[0];
  uint64_t wait_time = earliest_bus.next_time - t0;

  cout << (wait_time * earliest_bus.id) << endl;

  return 0;
}
