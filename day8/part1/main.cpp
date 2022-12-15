#include <iostream>
#include <vector>
#include <climits>
using namespace std;

bool check_height(size_t y, size_t x, vector<string> rows) {
    int height = rows[y][x] - '0';

    // Check left
    bool left_ok = false;
    for (size_t i = x-1; i < ~(size_t)0; i--) {
        if ((rows[y][i] - '0') >= height)
            left_ok = true;
    }

    // Check right
    bool right_ok = false;
    for (size_t i = x+1; i < rows[y].length(); i++) {
        if ((rows[y][i] - '0') >= height)
            right_ok = true;
    }

    // Check top
    bool top_ok = false;
    for (size_t i = y-1; i < ~(size_t)0; i--) {
        if ((rows[i][x] - '0') >= height)
            top_ok = true;
    }

    bool bottom_ok = false;
    for (size_t i = y+1; i < rows.size(); i++) {
        if ((rows[i][x] - '0') >= height)
            bottom_ok = true;
    }

    return left_ok && right_ok && top_ok && bottom_ok;
}

int main(int argc, char *argv[]) {
    vector<string> rows;
    for (string line; getline(cin, line); ) {
        rows.push_back(line);
    }

    // Skip top and bottom row
    int hidden_trees = 0;
    for (size_t y = 1; y < rows.size() - 1; y++) {
        for (size_t x = 1; x < rows[y].length() - 1; x++) {
            if (check_height(y, x, rows)) hidden_trees++;
        }
    }

    int total = rows.size() * rows[0].length();
    cout << total - hidden_trees << endl;
    return 0;
}
