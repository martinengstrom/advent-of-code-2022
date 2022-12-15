#include <iostream>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;

bool find_dupe(char* a) {
    char *pa = &a[0];
    for (int i = 0; i < 3; i++) {
        char *pb = &a[i + 1];
        for (int x = i + 1; x < 4; x++) {
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

        for (string::size_type i = 0; i < line.size(); i++) {
            char buf[4];
            int len = strlen(c_line) - (i + 1) > 3 ? 3 : strlen(c_line) - (i + 1);
            memcpy(buf + 1, c_line + i + 1, sizeof(char)*len);
            buf[0] = c_line[i];

            bool fisk_i_fickorna = find_dupe(&buf[0]);
            if (!fisk_i_fickorna) {
                cout << i+4 << endl;
                break;
            }
        }

        delete [] c_line;
    }

    return 0;
}
