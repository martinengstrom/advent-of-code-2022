#include <iostream>
#include <cstring>


using namespace std;

// Find the first common character in two null terminated c-strings
char find_dupe(char* a, char* b) {
    char *pa = &a[0];
    while (*pa != '\0') {
        char *pb = &b[0];
        while (*pb != '\0') {
            if (strncmp(&pa[0], &pb[0], 1) == 0) {
                return pa[0];
            }
            ++pb;
        }
        ++pa;
    }
    return '\0';
}

int getPriorityOfChar(char* c) {
    int OFFSET_LOWERCASE_START = (int)'a';
    int OFFSET_LOWERCASE_END = (int)'z';
    int OFFSET_UPPERCASE_START = (int)'A';
    int OFFSET_UPPERCASE_END = (int)'Z';

    int ascii = (int)*c;
    int offset = 0;
    if ((ascii >= OFFSET_LOWERCASE_START) && (ascii <= OFFSET_LOWERCASE_END)) {
        offset = OFFSET_LOWERCASE_START - 1;
    } else if ((ascii >= OFFSET_UPPERCASE_START) && (ascii <= OFFSET_UPPERCASE_END)) {
        offset = OFFSET_UPPERCASE_START - 27;
    }
    return ascii - offset;
}

int main(int argc, char *argv[]) {
    int sum = 0;
    for (string line; getline(cin, line); ) {
        int length = line.length();
        char *c_line = new char[line.length() + 1];
        strcpy(c_line, line.c_str());

        if (length % 2 != 0)
            cout << "WARN. Uneven sizes" << endl;

        int half = length / 2;
        char first[half+1];
        char second[(length - half) + 1];

        memcpy(first,(void*)&c_line[0], half);
        memcpy(second,(void*)&c_line[half], length - half);

        first[half] = '\0';
        second[length - half] = '\0';

        char c = find_dupe(first, second);
        int priority = getPriorityOfChar(&c);
        sum += priority;
        delete []  c_line;
    }
    cout << sum << endl;
}
