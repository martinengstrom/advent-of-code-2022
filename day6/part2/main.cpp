#include <iostream>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;

#define MARKER_LENGTH 14

bool find_dupe(char* a) {
    char *pa = &a[0];
    for (int i = 0; i < (MARKER_LENGTH-1); i++) {
        char *pb = &a[i + 1];
        for (int x = i + 1; x < MARKER_LENGTH; x++) {
            if (strncmp(&pa[0], &pb[0], 1) == 0) {
                return true;
            }
            ++pb;
        }
        ++pa;
    }
    return false;
}

int main(int argc, char *argv[]) {
    for (string line; getline(cin, line); ) {
        char *c_line = new char[line.length() + 1];
        strcpy(c_line, line.c_str());

        for (size_t i = 0; i < strlen(c_line); i++) {
            char buf[MARKER_LENGTH];
            int len = strlen(c_line) - (i + 1) > (MARKER_LENGTH - 1) ? (MARKER_LENGTH - 1) : strlen(c_line) - (i + 1);
            memcpy(buf + 1, c_line + i + 1, sizeof(char)*len);
            buf[0] = c_line[i];

            bool fisk_i_fickorna = find_dupe(&buf[0]);
            if (!fisk_i_fickorna) {
                cout << i+MARKER_LENGTH << endl;
                break;
            } 
        }

        delete [] c_line;
    }

    return 0;
}