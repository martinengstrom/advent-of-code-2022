#include <iostream>
#include <vector>
#include <stack>

// https://adventofcode.com/2022/day/5

/*
Each column is 3 letters wide, with a white space separator
Height is undefined
Each column ends with a id number. Id is single digit
--- --- ---
    [D]    
[N] [C]    
[Z] [M] [P]
 1   2   3 

move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2
*/

using namespace std;

stack<string> invert_stack(stack<string> input) {
    stack<string> result;

    while(!input.empty()) {
        result.push(input.top());
        input.pop();
    }

    return result;
}

vector<stack<string>> get_stacks(vector<string> data) {
    vector<stack<string>> invertedStacks;

    for (string line : data) {
        long unsigned int column = 0;
        long unsigned int cpos = 1;

        while(cpos < line.length()) {
            string letter = line.substr(cpos, 1);

            // Increase vector if needed
            if (invertedStacks.size() < (column + 1)) {
                stack<string> emptyStack;
                invertedStacks.push_back(emptyStack);
            }

            if (letter.compare(" ") != 0) {
                invertedStacks[column].push(letter);
            }

            cpos += 4;
            column++;
        }
    }

    // All the stacks are inverted.
    // We need to flip them around
    for (long unsigned int i = 0; i < invertedStacks.size() - 1; i++) {
        stack<string> s = invertedStacks[i];
        invertedStacks[i] = invert_stack(s);
    }

    return invertedStacks;
}

vector<string> split(string line, string delim) {
    vector<string> result;
    auto start = 0U;
    auto end = line.find(delim);

    while (end != std::string::npos)
    {
        result.push_back(line.substr(start, end - start));
        start = end + delim.length();
        end = line.find(delim, start);
    }

    result.push_back(line.substr(start, end));
    return result;
}

struct move_order {
    int qty;
    int from;
    int to;
};

void execute_move(vector<stack<string>> *stacks, move_order order) {
    for (int i = 0; i < order.qty; i++) {
        string crate = stacks->at(order.from - 1).top();
        stacks->at(order.from - 1).pop();
        stacks->at(order.to - 1).push(crate);
    }
}

int main(int argc, char *argv[]) {
    vector<string> stackrows;
    vector<move_order> moves;

    // Collect data from stdin
     bool stackrows_finished = false;
    for (string line; getline(cin, line); ) {
        if (line.substr(0, 3).compare(" 1 ") == 0) {
            stackrows_finished = true;
        }

        if (!stackrows_finished) {
            stackrows.push_back(line);
        }

        if (line.substr(0, 5).compare("move ") == 0) {
            vector<string> splits = split(line, " ");
            move_order move;
            move.qty = stoi(splits[1]);
            move.from = stoi(splits[3]);
            move.to = stoi(splits[5]);
            moves.push_back(move);
        } 
    }

    vector<stack<string>> stacks = get_stacks(stackrows);
    for (move_order order : moves) {
        execute_move(&stacks, order);
    }

    for (stack<string> stack : stacks) {
        cout << stack.top();
    }

    cout << endl;

    return 0;
}
