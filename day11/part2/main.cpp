#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <numeric>
#include "split.h"

using namespace std;
typedef signed long long worry_t;

class Monkey {
    public:
        void receive(worry_t item) {
            this->items.push(item);
        };

        long total_inspects = 0;
        int divisible;
        int lcd;

        void execute_turn() {
            while (!this->items.empty()) {
                worry_t new_level = this->inspect_item(this->items.front());
                new_level = new_level % this->lcd;

                int receiving_monkey_idx = ((new_level % this->divisible) == 0) ?
                    receiving_monkey_idx = this->throw_success_idx :
                    receiving_monkey_idx = this->throw_fail_idx;

                this->monkeys->at(receiving_monkey_idx)->receive(new_level);
                this->items.pop();
            }
        };

        Monkey(vector<string> *lines, vector<Monkey*> *monkeys) {
            this->parse(lines);
            this->monkeys = monkeys;
        };

        ~Monkey() {
            if (this->modifier != NULL) {
                delete this->modifier;
            }
        };
    private:
        worry_t (Monkey::*fncptr)(worry_t);
        int *modifier;
        int throw_success_idx;
        int throw_fail_idx;
        queue<worry_t> items;
        vector<Monkey*> *monkeys;

        worry_t add(worry_t old) {
            if (this->modifier != NULL) return old + (*modifier);
            else return old + old;
        };

        worry_t multiply(worry_t old) {
            if (this->modifier != NULL) return old * (*modifier);
            else return old * old;
        };

        bool starts_with(string *str, string *prefix) {
            return str->substr(0, prefix->length()).compare(*prefix) == 0;
        };

        worry_t inspect_item(worry_t item) {
            this->total_inspects++;
            return (this->*fncptr)(item);
        };

        void parse(vector<string> *lines) {
            string STARTING_ITEMS_PREFIX = "  Starting items: ";
            string TEST_DIVISIBLE_PREFIX = "  Test: divisible by ";
            string OPERATION_PREFIX = "  Operation: new = ";
            string IF_TRUE_PREFIX = "    If true: throw to monkey ";
            string IF_FALSE_PREFIX = "    If false: throw to monkey ";

            for(auto& line: *lines) {
                if (this->starts_with(&line, &STARTING_ITEMS_PREFIX)) {
                    vector<string> splits = split(line.substr(17), ", ");
                    for (auto& split : splits) {
                        items.push(stoi(split));
                    }
                } else if (this->starts_with(&line, &TEST_DIVISIBLE_PREFIX)) {
                    this->divisible = stoi(line.substr(TEST_DIVISIBLE_PREFIX.length()));
                } else if (this->starts_with(&line, &OPERATION_PREFIX)) {
                    string substr = line.substr(OPERATION_PREFIX.length());
                    vector<string> splits = split(substr, " ");

                    if (splits[1].compare("*") == 0) {
                        this->fncptr = &Monkey::multiply;
                    } else if (splits[1].compare("+") == 0) {
                        this->fncptr = &Monkey::add;
                    }

                    if (splits[2].compare("old") == 0) {
                        this->modifier = NULL;
                    } else {
                        this->modifier = new int;
                        *(this->modifier) = stoi(splits[2]);
                    }
                } else if (this->starts_with(&line, &IF_TRUE_PREFIX)) {
                    int receiving_idx = stoi(line.substr(IF_TRUE_PREFIX.length()));
                    this->throw_success_idx = receiving_idx;
                } else if (this->starts_with(&line, &IF_FALSE_PREFIX)) {
                    int receiving_idx = stoi(line.substr(IF_FALSE_PREFIX.length()));
                    this->throw_fail_idx = receiving_idx;
                }
            }
        };
};

int main(int argc, char *argv[]) {
    vector<Monkey*> monkeys;
    vector<string> *buffer = new vector<string>();

    for (string line; getline(cin, line); ) {
        if (line.substr(0, 7).compare("Monkey ") == 0) {
            buffer->clear();
        } else if (line.compare("") == 0) {
            Monkey *monkey = new Monkey(buffer, &monkeys);
            monkeys.push_back(monkey);
        } else {
            buffer->push_back(line);
        }
    }
    if (buffer->size() > 0) {
        Monkey *monkey = new Monkey(buffer, &monkeys);
        monkeys.push_back(monkey);
    }
    delete buffer;


    // Find the LCD
    int lcd_t = 1;
    for (int i = 0; i < monkeys.size(); i++) {
        lcd_t *= monkeys[i]->divisible;
    }

    for (int i = 0; i < monkeys.size(); i++) {
        monkeys[i]->lcd = lcd_t;
    }

    /////////

    for (int round = 1; round <= 10000; round++) {
        for (int i = 0; i < monkeys.size(); i++) {
            monkeys[i]->execute_turn();
        }
    }

    sort(monkeys.begin(), monkeys.end(), [](Monkey *a, Monkey *b) {
        return a->total_inspects > b->total_inspects;
    });

    long monkey_business = monkeys[0]->total_inspects * monkeys[1]->total_inspects;
    cout << monkey_business << endl;

    // FINAL Cleanup
    for (auto& monkey : monkeys) {
        delete monkey;
    }
    return 0;
}
