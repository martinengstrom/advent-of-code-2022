#include <iostream>
#include <vector>

// https://adventofcode.com/2022/day/4

using namespace std;

struct range {
    int start;
    int end;
};

vector<string> split(string line, string delim) {
    vector<string> result;
    auto start = 0U;
    auto end = line.find(delim);

    while (end != std::string::npos)
    {
        result.push_back(line.substr(start, end - start));
        start = end + delim.length();
        end = line.find(delim, start);
    }

    result.push_back(line.substr(start, end));
    return result;
}

range parseElf(string data) {
    vector<string> splits = split(data, "-");
    range elf;
    elf.start = stoi(splits[0]);
    elf.end = stoi(splits[1]);
    return elf;
}

/*
   |-------|
       |--------|
           |--------|
   |----------------|

*/
bool findOverlap(range range1, range range2) {
    return (
        ((range1.end >= range2.start) && (range1.end <= range2.end)) ||
        ((range1.start >= range2.start) && (range1.start <= range2.end)) ||
        ((range1.start <= range2.start) && (range1.end >= range2.end))
    );
}

int main(int argc, char *argv[]) {
    int counter = 0;
    for (string line; getline(cin, line); ) {
        vector<string> splits = split(line, ",");
        range elf1 = parseElf(splits[0]);
        range elf2 = parseElf(splits[1]);

        if (findOverlap(elf1, elf2) || findOverlap(elf2, elf1)) counter++;
    }

    cout << counter << endl;
    return 0;
}
