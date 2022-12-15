#include <iostream>
#include <vector>
#include <climits>
#include <cstring>
#include <algorithm>
#include <list>

using namespace std;

struct Node {
    bool visited;
    int estimate;
    int height;
    int x;
    int y;
    Node* prev;
};

bool height_within_limit(Node* n, int current) {
    return n->height <= (current + 1);
}

void reposition_unvisited_node(list<Node*>* unvisited_nodes, Node* node) {
    // Remove node from current list, and reinsert it at new position
    unvisited_nodes->remove(node);

    list<Node*>::iterator it = unvisited_nodes->begin();
    while (it != unvisited_nodes->end()) {
        Node* n = *it;
        if (n->estimate > node->estimate) {
            unvisited_nodes->insert(it, node);
            break;
        } else ++it;
    };
}

vector<Node*> get_adjacent(vector<vector<Node*>>* nodes, int y, int x) {
    vector<Node*> adjacent_nodes;
    int current_height = nodes->at(y)[x]->height;
    if (y < nodes->size()-1) {
        Node *n = nodes->at(y+1)[x];
        if (height_within_limit(n, current_height)) {
            adjacent_nodes.push_back(n);
        }
    }

    if (y > 0) {
        Node *n = nodes->at(y-1)[x];
        if (height_within_limit(n, current_height)) {
            adjacent_nodes.push_back(n);
        }
    }

    if (x < nodes->at(y).size()-1) {
        Node *n = nodes->at(y)[x+1];
        if (height_within_limit(n, current_height)) {
            adjacent_nodes.push_back(n);
        }
    }

    if (x > 0) {
        Node *n = nodes->at(y)[x-1];
        if (height_within_limit(n, current_height)) {
            adjacent_nodes.push_back(n);
        }
    }

    return adjacent_nodes;
}

void dijkstra(vector<vector<Node*>>* nodes, 
                list<Node*>* unvisited_nodes, 
                int current_y, 
                int current_x,
                Node* target) {
    Node* current = nodes->at(current_y)[current_x];
    long current_estimate = current->estimate;
    current->visited = true;
    unvisited_nodes->remove(current);

    // Get adjacent
    vector<Node*> adjacent_nodes = get_adjacent(nodes, current_y, current_x);

    // Remove nodes we already visited from new visits
    adjacent_nodes.erase(remove_if(adjacent_nodes.begin(), adjacent_nodes.end(), [](Node *n){
        return n->visited;
    }), adjacent_nodes.end());

    // Update their estimates
    for (Node* node : adjacent_nodes) {
        long new_estimate = current->estimate + 1;
        if (new_estimate < node->estimate) {
            node->estimate = new_estimate;
            node->prev = current;
            reposition_unvisited_node(unvisited_nodes, node);
        }
    }

    if (unvisited_nodes->size() == 0) return;
    Node* next = unvisited_nodes->front();
    if (target->visited) return;
    if (next->estimate == INT_MAX) return;
    dijkstra(nodes, unvisited_nodes, next->y, next->x, target);
}

void reset(vector<vector<Node*>>* nodes, list<Node*>* unvisited_nodes) {
    unvisited_nodes->clear();
    for (int y = 0; y < nodes->size(); y++) {
        for (int x = 0; x < nodes->at(y).size(); x++) {
            Node *node = nodes->at(y)[x];
            node->estimate = INT_MAX;
            node->prev = NULL;
            node->visited = false;
            unvisited_nodes->push_back(node);
        }
    }
}

int main(int argc, char *argv[]) {
    vector<vector<Node*>> nodes;
    list<Node*> unvisited_nodes;

    Node* start;
    Node* target;

    int y_counter = 0;
    for (string line; getline(cin, line); ) {
        int x_counter = 0;
        vector<Node*> current_x;
        for (auto& c : line) {
            int height = 0;
            Node* node = new Node;

            if (strncmp(&c, "S", 1) == 0) {
                start = node;
                height = 'a' - 'a';
                node->estimate = 0;
            } else if (strncmp(&c, "E", 1) == 0) {
                target = node;
                height = 'z' - 'a';
                node->estimate = INT_MAX;
            } else {
                height = c - 'a';
                node->estimate = INT_MAX;
            }

            node->visited = false;
            node->height = height;
            node->x = x_counter;
            node->y = y_counter;

            current_x.push_back(node);
            unvisited_nodes.push_back(node);
            x_counter++;
        }
        nodes.push_back(current_x);
        y_counter++;
    }

    dijkstra(&nodes, &unvisited_nodes, start->y, start->x, target);
    cout << "Part 1:" << endl;
    cout << target->estimate << endl << endl;

    vector<Node*> starting_nodes;
    for (int y = 0; y < nodes.size(); y++)
        for (int x = 0; x < nodes[y].size(); x++)
            if (nodes[y][x]->height == 0)
                starting_nodes.push_back(nodes[y][x]);
                

    int steps = INT_MAX;
    int c = 0;
    for (Node* n : starting_nodes) {
        cout << "\rTesting " << ++c << "/" << starting_nodes.size();
        reset(&nodes, &unvisited_nodes);
        n->estimate = 0;
        dijkstra(&nodes, &unvisited_nodes, n->y, n->x, target);
        int total_steps = target->estimate;
        if (total_steps < steps) steps = total_steps;
    }

    cout << endl << "Part 2:" << endl;
    cout << steps << endl;

    // Not really needed, but good practise.
    for (auto& v : nodes)
        for (auto& n : v)
            delete n;
}
