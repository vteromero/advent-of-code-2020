#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

enum Operation {NOP, ACC, JMP};

struct Instruction {
  Operation op;
  int arg;
};

int main() {
  vector<Instruction> instructions;

  for (string line; getline(cin, line); ) {
    istringstream ss(line);
    string temp;
    Instruction ins;

    ss >> temp >> ins.arg;

    if (temp == "nop") {
      ins.op = NOP;
    } else if (temp == "acc") {
      ins.op = ACC;
    } else if (temp == "jmp") {
      ins.op = JMP;
    }

    instructions.push_back(ins);
  }

  size_t n = instructions.size();
  vector<bool> visited(n, false);
  int acc = 0;

  for (size_t i = 0; i < n; ) {
    Instruction &ins = instructions[i];

    if (visited[i]) {
      cout << acc << endl;
      break;
    }

    visited[i] = true;

    switch (ins.op) {
      case NOP:
        i++;
        break;
      case ACC:
        acc += ins.arg;
        i++;
        break;
      case JMP:
        i += ins.arg;
        break;
    }
  }

  return 0;
}
