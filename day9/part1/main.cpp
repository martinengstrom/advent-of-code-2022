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
    else
        cout << "Unknown direction" << endl;

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

void test_needs_move() {
    //....
    //TH..
    //T..H
    cout << (needs_move(1, 0, 0, 0) == false) << endl;
    cout << (needs_move(2, 0, 0, 0) == true) << endl;
   
    //....
    //H...
    //T...

    //H...
    //....
    //T...
    cout << (needs_move(0, 0, 1, 0) == false) << endl;
    cout << (needs_move(0, 0, 2, 0) == true) << endl;

    //    H.H
    //    .T.
    //    H.H
    cout << (needs_move(0, 1, 0, 1) == false) << endl;
    cout << (needs_move(2, 1, 0, 1) == false) << endl;
    cout << (needs_move(0, 1, 2, 1) == false) << endl;
    cout << (needs_move(2, 1, 2, 1) == false) << endl;
   
    //    H...H
    //    ..T..
    //    H...H
    cout << (needs_move(0, 2, 0, 1) == true) << endl;
    cout << (needs_move(4, 2, 0, 1) == true) << endl;
    cout << (needs_move(0, 2, 4, 1) == true) << endl;
    cout << (needs_move(4, 2, 4, 1) == true) << endl;

    // .....    .....    .....
    // .....    ..H..    ..H..
    // ..H.. -> ..... -> ..T..
    // .T...    .T...    .....
    // .....    .....    .....

    // ..T
    // ...
    // .H.

    cout << (needs_move(2, 1, 3, 1) == true);
    cout << (needs_move(1, 3, 0, 3) == true);
}

void move_tail(End *head, End *tail) {
    // Check adjacent up/down/left/right
    int hx = head->x;
    int hy = head->y;
    int tx = tail->x;
    int ty = tail->y;

    if (!needs_move(hx, tx, hy, ty)) return;


    int delta_x = 0;
    int delta_y = 0;

    // Check diag first
    //    H...H
    //    ..T..
    //    H...H

    // Glöm ej även
    //    ...H. 
    //    .....
    //    ..T..
    //    delta x: 1
    //    delta y: 2
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
    }

    tail->x += delta_x;
    tail->y += delta_y;

    // Update history;
    tail->history[tail->x][tail->y] += 1;
}

void print_board(End *head, End *tail) {
    for (int y = -5; y < 5; y++) {
        for (int x = -5; x < 5; x++) {
            if (head->x == x && head->y == y)
                cout << "H";
            else if (tail->x == x && tail->y == y)
                cout << "T";
            else
                cout << ".";
            cout << " ";
        }
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    End head = get_start_end();
    End tail = get_start_end();

    for (string line; getline(cin, line); ) {
        Move move = parse_move(line);
        for (int i = 0; i < move.steps; i++) {
            move_head(move.direction, &head);
            move_tail(&head, &tail);
        }
    }
    
    int visited_at_least_once = 0;
    for (auto const& x : tail.history) {
       visited_at_least_once += x.second.size();
    }

    cout << visited_at_least_once << endl;
    return 0;
}
