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
    string original;
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

void log_cycle(string message, vector<Registers> *cycle) {
    cout << cycle->size() << " " << message << " x=" << cycle->at(cycle->size()-1).x << endl;
}

void show(vector<string> *crt, Cycle *c, int *crt_char) {
    if (*crt_char >= c->start.x-1 && *crt_char <= c->start.x+1) {
        crt->push_back("#");
    } else {
        crt->push_back(".");
    }
    (*crt_char)++;
    if (*crt_char > 39) *crt_char = 0;
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
        instruction.original = line;
        instructions.push(instruction);
    }

    int crt_char = 0;
    vector<string> crt;
    vector<Cycle> cycles;
    cycles.push_back(get_init());

    while (instructions.size() > 0) {
        Instruction instruction = instructions.front();
        instructions.pop();

        Cycle c;
        c.start = cycles[cycles.size()-1].end;
        show(&crt, &c, &crt_char);

        if (instruction.operation == Operation::noop) {
            c.end = c.start;
            cycles.push_back(c);
            continue;
        } else if (instruction.operation == Operation::addx) {
            c.end = c.start;
            cycles.push_back(c);

            Cycle cc;
            cc.start = c.end;

            show(&crt, &cc, &crt_char);

            Registers r = cc.start;
            r.x += instruction.value;
            cc.end = r;
            cycles.push_back(cc);
        }
    }

    int x = 0;
    for (size_t i = 0; i < crt.size(); i++) {
        cout << crt[i];
        if (x++ == 39) {
            x = 0;
            cout << endl;
        }
    }
}
