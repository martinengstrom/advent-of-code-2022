#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <stack>
#include <algorithm>

using namespace std;

class Container {
    public:
    enum class Type {
        container,
        value
    };

    enum class RetVal {
        CORRECT,
        NOT_CORRECT,
        SKIP
    };

    struct Item {
        Type type;
        Container* container = NULL;
        int value;
    };

    vector<Item*>* items = NULL;
    Container* parent = NULL;

    void push_container(Container* c) {
        c->parent = this;
        Item *item = new Item;
        item->type = Type::container;
        item->container = c;
        items->push_back(item);
    }

    void push_number(int v) {
        Item *item = new Item;
        item->type = Type::value;
        item->value = v;
        items->push_back(item);
    }

    Container* convert_to_container_if_needed(Item* i) {
        if (i->type == Type::value) {
            Container *c = new Container(this);
            c->push_number(i->value);
            return c;
        }
        return NULL;
    }

    RetVal compare(Container* other) {
        /*
        If both values are integers, the lower integer should come first. If the left integer is lower than the right integer, 
        the inputs are in the right order. If the left integer is higher than the right integer, the inputs are not in the right order. 
        Otherwise, the inputs are the same integer; continue checking the next part of the input.
        */

        /*
        If both values are lists, compare the first value of each list, then the second value, and so on. 
        If the left list runs out of items first, the inputs are in the right order. If the right list runs out of items first, 
        the inputs are not in the right order. If the lists are the same length and no comparison makes a decision about the order, 
        continue checking the next part of the input.
        */

        for (int i = 0; i < this->items->size(); i++) {
            if (i < other->items->size()) {
                Item *their = other->items->at(i);
                Item *our = this->items->at(i);
                
                // Compare numbers
                if (our->type == Type::value && their->type == Type::value) {
                    if (our->value < their->value) return RetVal::CORRECT;
                    if (our->value > their->value) return RetVal::NOT_CORRECT;
                    if (our->value == their->value) continue;
                // Compare lists
                } else if (our->type == Type::container && their->type == Type::container) {
                    RetVal rv = our->container->compare(their->container);
                    if (rv == RetVal::SKIP) continue;
                    return rv;
                // Compare mixed list <-> number
                } else {
                    Container *to_be_deleted = NULL;

                    Container *their_container = convert_to_container_if_needed(their);
                    Container *our_container = convert_to_container_if_needed(our);
                    if (our_container == NULL) {
                        our_container = our->container;
                        to_be_deleted = their_container;
                    } else if (their_container == NULL) {
                        their_container = their->container;
                        to_be_deleted = our_container;
                    }
                    RetVal rv = our_container->compare(their_container);
                    delete to_be_deleted;

                    if (rv == RetVal::SKIP) continue;
                    return rv;
                }
            } else {
                return RetVal::NOT_CORRECT;
            }
        }

        if (other->items->size() > this->items->size())
            return RetVal::CORRECT;

        return RetVal::SKIP;
    };

    Container(Container* parent) {
        this->parent = parent;
        this->items = new vector<Item*>;
    }

    ~Container() {
        if (this->items != NULL) {
            for (Item* i : *(this->items)) {
                if (i->container != NULL) {
                    delete i->container;
                }
                delete i;
            }
            delete this->items;
        }
    }
};

Container* parse(string str) {
    Container *container = NULL;
    stack<string> buffer;
    for (char& c: str) {
        if (strncmp(&c, "[", 1) == 0) {
            Container *subcontainer = new Container(container);
            if (container != NULL)
                container->push_container(subcontainer);
            container = subcontainer;
            string empty;
            buffer.push(empty);
        } else if (strncmp(&c, "]", 1) == 0) {
            if (!(buffer.top().empty())) {
                container->push_number(stoi(buffer.top()));
            }
            buffer.pop();
            if (container->parent != NULL) // We dont want to lose our reference to this shit :D
                container = container->parent;
        }else if (strncmp(&c, ",", 1) == 0) {
            if (!(buffer.top().empty())) {
                container->push_number(stoi(buffer.top()));
                buffer.top().clear();
            }
        } else {
            buffer.top() += c;
        }
    }
    return container;
}

string remove_post_pre_fix(string a) {
    return a.substr(1).substr(0, a.size()-2);
}

void process_vector(vector<string> *strings) {
    sort(strings->begin(), strings->end(), [](string &a, string &b) {
        Container *ca = parse(a);
        Container *cb = parse(b);
        Container::RetVal result = ca->compare(cb);

        delete ca;
        delete cb;

        return result == Container::RetVal::CORRECT;
    });
}

bool process_pair(string a, string b) {
    Container *ca = parse(a);
    Container *cb = parse(b);

    Container::RetVal rv = ca->compare(cb);
    delete ca;
    delete cb;
    if (rv == Container::RetVal::CORRECT) {
        return true;
    } else if (rv == Container::RetVal::NOT_CORRECT) {
        return false;
    } else {
        cout << "Unable to make decision" << endl;
        return false;
    }
}

void do_part1() {
    
}

int main(int argc, char *argv[]) {
    vector<string> part2_strings;

    string prev;
    int idx = 1;
    int successful_idx = 0;
    int c = 0;

    for (string line; getline(cin, line); ) {
        if (line.compare("") != 0) part2_strings.push_back(line);

        if (c == 0) {
            prev = line;
        } else if (c == 1) {
            bool result = process_pair(prev, line);
            if (result) successful_idx += idx;
            idx++;
        } 
        
        if (c++ > 1) c = 0;
    }

    cout << "Part 1: " << successful_idx << endl;


    part2_strings.push_back("[[2]]");
    part2_strings.push_back("[[6]]");
    process_vector(&part2_strings);

    cout << "Part 2: ";
    int val = -1;
    for (int i = 0; i < part2_strings.size(); i++) {
        if ((part2_strings[i].compare("[[2]]") == 0) || part2_strings[i].compare("[[6]]") == 0) {
            if (val < 0) {
                val = (i+1);
            } else if (val >= 0) {
                cout << val * (i+1) << endl;
                break;
            }
        }
    }

    return 0;
}
