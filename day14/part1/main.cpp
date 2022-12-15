#include <iostream>
#include <vector>
#include "split.h"

using namespace std;

enum class Type {
    air,
    sand,
    rock
};

struct XY {
    int x = 0;
    int y = 0;
};

typedef vector<XY*> path_t;
typedef vector<vector<Type*>*> world_t;

void set_type(int y, int x, Type* t, world_t* world) {
    delete world->at(y)->at(x);
    world->at(y)->at(x) = t;
}

void set_rock(int y, int x, world_t* world) {
    Type *t = new Type;
    *t = Type::rock;
    set_type(y, x, t, world);
}

void set_sand(int y, int x, world_t* world) {
    Type *t = new Type;
    *t = Type::sand;
    set_type(y, x, t, world);
}

void insert_path(path_t* path, world_t* world) {
    int current_x = path->at(0)->x;
    int current_y = path->at(0)->y;

    if (path->size() == 1)
        cout << "WARN Single node path!!!" << endl;

    for (int i = 1; i < path->size(); i++) {
        int new_x = path->at(i)->x;
        int new_y = path->at(i)->y;

        if (new_x == current_x) {
            // Vertical line
            int start_y = current_y;
            int end_y = (current_y < new_y) ? new_y+1 : new_y-1;
            int incr = (current_y < new_y) ? 1 : -1; 

            int y = start_y;
            do {
                set_rock(y, current_x, world);
                y += incr;
            } while (y != end_y);
        } else if (new_y == current_y) {
            // Horizontal line
            int start_x = current_x;
            int end_x = (current_x < new_x) ? new_x+1 : new_x-1;
            int incr = (current_x < new_x) ? 1 : -1;

            int x = start_x;
            do {
                set_rock(current_y, x, world);
                x += incr;
            } while (x != end_x);
        } else {
            cout << "WARN. Parse error" << endl;
        }

        current_x = new_x;
        current_y = new_y;
    }    
}

void print(world_t* world, int x_offset) {
    for (int y = 0; y < world->size(); y++) {
        for (int x = 0 + x_offset; x < world->at(y)->size(); x++) {
            Type *t = world->at(y)->at(x);
            if (*t == Type::air) {
                cout << ".";
            } else if (*t == Type::rock) {
                cout << "#";
            } else if (*t == Type::sand) {
                cout << "+";
            }
        }
        cout << endl;
    }
}

bool check_bounds(int y, int x, world_t *world) {
    return (
        (y >= 0 && y < world->size()) &&
        (x >= 0 && x < world->at(0)->size())
    );
}

// Return true if sand did not fall out into the void
bool simulate_sand(world_t *world) {

    int current_x = 500;
    int current_y = 1;

    while(true) {
        bool moved = false;
        int desired_y = current_y + 1;
        int desired_x = current_x;

        // A unit of sand always falls down one step if possible.
        if (!(check_bounds(current_y + 1, current_x, world))) return false;
        if (*(world->at(desired_y)->at(desired_x)) == Type::air) {
            current_x = desired_x;
            current_y = desired_y;
            moved = true;
            continue;
        }

        desired_x = current_x - 1;
        if (!moved && !(check_bounds(desired_y, desired_x, world))) return false;
        if (!moved && (*(world->at(desired_y)->at(desired_x)) == Type::air)) {
            current_x = desired_x;
            current_y = desired_y;
            moved = true;
            continue;
        }

        desired_x = current_x + 1;
        if (!moved && !(check_bounds(desired_y, desired_x, world))) return false;
        if (!moved && (*(world->at(desired_y)->at(desired_x)) == Type::air)) {
            current_x = desired_x;
            current_y = desired_y;
            moved = true;
            continue;
        }

        // It never moved, so its at rest
        if (!moved) {
            // Set new position to sand
            set_sand(current_y, current_x, world);
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    vector<path_t*> *paths = new vector<path_t*>();
    for (string line; getline(cin, line); ) {
        vector<string> coords = split(line, " -> ");
        path_t *current_path = new path_t();
        for (auto& coord : coords) {
            vector<string> xy = split(coord, ",");
            XY *c = new XY;
            c->x = stoi(xy[0]);
            c->y = stoi(xy[1]);
            current_path->push_back(c);
        }
        paths->push_back(current_path);
    }

    int max_y = 0;
    int max_x = 0;

    for (auto path : *paths) {
        for (auto coord : *path) {
            max_y = coord->y > max_y ? coord->y : max_y;
            max_x = coord->x > max_x ? coord->x : max_x;
        }
    }

    // Initialize vector with the correct size
    world_t *world = new world_t();
    for (int y = 0; y <= max_y; y++) {
        vector<Type*> *vx = new vector<Type*>();
        for (int x = 0; x <= max_x; x++) {
            Type *t = new Type;
            *t = Type::air;
            vx->push_back(t);
        }
        world->push_back(vx);
    }

    // Add the paths into the world
    for (auto path : *paths) {
        insert_path(path, world);

        for (auto coord : *path)
            delete coord;
        delete path;
    }
    delete paths;

    //set_sand(0, 500, world);

    // Begin sand simulation
    while(simulate_sand(world));

    long units_of_sand = 0;
    for (auto y : *world) {
        for (auto x : *y) {
            if (*x == Type::sand) units_of_sand++;
        }
    }

    // Because the sand spawner counts as sand
    cout << units_of_sand << endl;

    for (auto vec_x : *world) {
        for (auto t : *vec_x) {
            delete t;
        }
        delete vec_x;
    }
    delete world;
}
