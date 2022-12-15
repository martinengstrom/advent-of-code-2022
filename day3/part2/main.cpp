#include <iostream>
#include <cstring>


using namespace std;

// Find all common characters in two null terminated c-strings
size_t find_dupe(char* buffer, char* a, char* b) {
    int found = 0;
    buffer[0] = '\0';

    char *pa = &a[0];
    while (*pa != '\0') {
        char *pb = &b[0];
        while (*pb != '\0') {
            if (strncmp(&pa[0], &pb[0], 1) == 0) {
                buffer[found] = pa[0];
                buffer[found+1] = '\0';
                found++;
            }
            ++pb;
        }
        ++pa;
    }

    size_t size = strlen(buffer);
    return size;
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
    int current = 0;
    char *elfs[3];
    for (string line; getline(cin, line); ) {
        char *c_line = new char[line.length() + 1];
        strcpy(c_line, line.c_str());

        elfs[current] = c_line;

        if (current == 2) {
            // Check all their shit
            char* buffer = (char*)malloc(sizeof(char) * 256);
            char* buffer2 = (char*)malloc(sizeof(char) * 256);
            find_dupe(buffer, elfs[0], elfs[1]);
            find_dupe(buffer2, buffer, elfs[2]);

            int priority = getPriorityOfChar(&buffer2[0]);
            sum += priority;

            free(buffer);
            free(buffer2);

            delete [] elfs[0];
            delete [] elfs[1];
            delete [] elfs[2];
            current = 0;
        } else {
            current++;
        }
    }
    cout << sum << endl;
}
