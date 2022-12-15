#include <iostream>
#include <vector>
#include <map>
#include "split.h"

using namespace std;

enum class Direction {
    up,
    down,
    left,
    right
};

struct Move {
    Direction direction;
    int steps;
};

Move parse_move(string move) {
    vector<string> splits = split(move, " ");
    Direction d; 
    if (splits[0].compare("R") == 0)
        d = Direction::right;
    else if (splits[0].compare("L") == 0)
        d = Direction::left;
    else if (splits[0].compare("U") == 0)
        d = Direction::up;
    else if (splits[0].compare("D") == 0)
        d = Direction::down;

    Move m;
    m.direction = d;
    m.steps = stoi(splits[1]);
    return m;
}

struct End {
    int x;
    int y;
    map<int, map<int, int>> history;
};

End get_start_end() {
    End end;
    end.x = 0;
    end.y = 0;

    end.history[0][0] = 1;
    return end;
}

void move_head(Direction direction, End *end) {
    if (direction == Direction::up) end->y++;
    else if (direction == Direction::down) end->y--;
    else if (direction == Direction::right) end->x++;
    else if (direction == Direction::left) end->x--;
}

bool needs_move(int hx, int tx, int hy, int ty) {
    return !(
        (
            (hx - tx >= -1 && hx - tx <= 1) &&
            (hy - ty >= -1 && hy - ty <= 1)
        ) ||
        (
            (hy - ty >= -1 && hy - ty <= 1) &&
            (hx - tx == -1 || hx - tx == 1)
        )
    );
}

void print_binary(int v) {
    for (int i = sizeof(i)*8; i >= 0; i--)
        cout << (((v >> i) & 1U) == 1 ? "1" : "0");
    cout << endl;
}

void move_tail(End *head, End *tail) {
    int hx = head->x;
    int hy = head->y;
    int tx = tail->x;
    int ty = tail->y;

    if (!needs_move(hx, tx, hy, ty)) return;

    int delta_x = 0;
    int delta_y = 0;

    if ((hx - tx == -2 || hx - tx == 2) && 
        (hy - ty == -1 || hy - ty == 1)) {

        delta_y = hy-ty;
        delta_x = hx-tx;
        if (delta_x < 0) delta_x ++;
        if (delta_x > 0) delta_x --;

    } else if ( (hx - tx == -1 || hx - tx == 1) && 
                (hy - ty == -2 || hy - ty == 2) ) {

        delta_y = hy-ty;
        delta_x = hx-tx;
        if (delta_y < 0) delta_y ++;
        if (delta_y > 0) delta_y --;

    } else if (hx - tx == -2 && hy == ty) {
        // We need to move X left
        delta_x = -1;
    } else if (hx - tx == 2 && hy == ty) {
        // We need to move X right
        delta_x = 1;
    } else if (hy - ty == 2 && hx == tx) {
        // We need to move Y up
        delta_y = 1;
    } else if (hy - ty == -2 && hx == tx) {
        // We need to move Y down
        delta_y = -1;
    } else if ( (hx - tx == -2 || hx - tx == 2) && 
                (hy - ty == -2 || hy - ty == 2) ) {

        delta_y = hy-ty;
        delta_x = hx-tx;

        if (delta_y < 0) delta_y ++;
        if (delta_x < 0) delta_x ++;
        if (delta_y > 0) delta_y --;
        if (delta_x > 0) delta_x --;
    }

    tail->x += delta_x;
    tail->y += delta_y;
    tail->history[tail->x][tail->y] += 1;
}

void print_board(vector<End> *knots, int size) {
    for (int y = size; y > -size; y--) {
        cout << y << " ";
        if (y >= 0 && y < 10) cout << " ";
        for (int x = -size; x < size; x++) {
           bool found = false;
           for (size_t k = 0; k < knots->size(); k++) {
               if (knots->at(k).y == y && knots->at(k).x == x) {
                   cout << (k == 0 ? "H" : to_string(k));
                   found = true;
                   break;
               }
           }
           if (!found) cout << ".";
           cout << " ";
        }
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    vector<End> knots;
    for (int i = 0; i < 10; i++) {
        knots.push_back(get_start_end());
    }

    for (string line; getline(cin, line); ) {
        Move move = parse_move(line);
        for (int i = 0; i < move.steps; i++) {
           move_head(move.direction, &knots[0]);
           for (size_t x = 1; x < knots.size(); x++) {
               move_tail(&knots[x-1], &knots[x]);
           }
        }
    }
    
    int visited_at_least_once = 0;
    for (auto const& x : knots[knots.size()-1].history) {
       visited_at_least_once += x.second.size();
    }

    cout << visited_at_least_once << endl;
    return 0;
}
