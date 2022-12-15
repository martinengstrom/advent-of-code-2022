#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int get_score(size_t y, size_t x, vector<string> *rows) {
    int height = rows->at(y)[x] - '0';

    // Check left
    int left_score = 0;
    if (x > 0) {
        for (size_t i = x-1; i < ~(size_t)0; i--) {
            left_score++;
            if ((rows->at(y)[i] - '0') >= height)
                break;
        }
    }

    // Check right
    int right_score = 0;
    if (x < rows->at(y).length() - 1) {
        for (size_t i = x+1; i < rows->at(y).length(); i++) {
            right_score++;
            if ((rows->at(y)[i] - '0') >= height)
                break;
        }
    }

    // Check top
    int top_score = 0;
    if (y > 0) {
        for (size_t i = y-1; i < ~(size_t)0; i--) {
            top_score++;
            if ((rows->at(i)[x] - '0') >= height)
                break;
        }
    }

    int bottom_score = 0;
    if (y < rows->size() - 1) {
        for (size_t i = y+1; i < rows->size(); i++) {
            bottom_score++;
            if ((rows->at(i)[x] - '0') >= height)
                break;
        }
    }

    return top_score * left_score * bottom_score * right_score;
}

int main(int argc, char *argv[]) {
    vector<string> rows;
    for (string line; getline(cin, line); ) {
        rows.push_back(line);
    }

    int high_score = 0;
    for (size_t y = 0; y < rows.size(); y++) {
        for (size_t x = 0; x < rows[y].length(); x++) {
            int a = get_score(y, x, &rows);
            high_score = (a > high_score) ? a : high_score;
        }
    }

    cout << high_score << endl;
    return 0;
}
