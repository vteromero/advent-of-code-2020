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

bool execute(const vector<Instruction>& instructions, int &acc) {
  size_t n = instructions.size();
  vector<bool> visited(n, false);

  acc = 0;

  for (size_t i = 0; i < n; ) {
    const Instruction &ins = instructions[i];

    if (visited[i]) {
      return false;
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

  return true;
}

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
  int acc = 0;

  for (size_t i = 0; i < n; i++) {
    Instruction &ins = instructions[i];

    if (ins.op == ACC) {
      continue;
    }

    vector<Instruction> copy_instructions = vector<Instruction>(instructions);

    if (ins.op == NOP) {
      copy_instructions[i].op = JMP;
    } else if (ins.op == JMP) {
      copy_instructions[i].op = NOP;
    }

    if (execute(copy_instructions, acc)) {
      cout << acc << endl;
      break;
    }
  }

  return 0;
}
