#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum class Operation {
    addx,
    noop
};

struct Instruction {
    Operation operation;
    int value;
};

struct Registers {
    int x;
};

struct Cycle {
    Registers start;
    Registers end;
};

Cycle get_init() {
    Registers r;
    r.x = 1;

    Cycle c;
    c.start = r;
    c.end = r;
    return c;
}

int main(int argc, char *argv[]) {
    queue<Instruction> instructions;
    for (string line; getline(cin, line); ) {
        Instruction instruction;
        if (line.length() == 4) {
            instruction.operation = Operation::noop;
            instruction.value = 0;
        } else {
            instruction.operation = Operation::addx;
            instruction.value = stoi(line.substr(4));
        }
        instructions.push(instruction);
    }
    vector<Cycle> cycles;
    cycles.push_back(get_init());

    while (instructions.size() > 0) {
        Instruction instruction = instructions.front();
        instructions.pop();

        Cycle c;
        c.start = cycles[cycles.size()-1].end;
        if (instruction.operation == Operation::noop) {
            c.end = c.start;
            cycles.push_back(c);
            continue;
        } else if (instruction.operation == Operation::addx) {
            c.end = c.start;
            cycles.push_back(c);

            Cycle cc;
            cc.start = c.end;

            Registers r = cc.start;
            r.x += instruction.value;
            cc.end = r;
            cycles.push_back(cc);
        }
    }

    int strength = 0;
    int cycle_pos[] = {20, 60, 100, 140, 180, 220};
    for (size_t i = 0; i < sizeof(cycle_pos) / sizeof(cycle_pos[0]); i++) {
        Cycle c = cycles[cycle_pos[i]];
        strength += c.start.x * cycle_pos[i];
    }
    cout << strength << endl;
}
