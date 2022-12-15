#include "split.h"

vector<string> split(string line, string delim) {
    vector<string> result;
    auto start = 0U;
    auto end = line.find(delim);

    while (end != string::npos)
    {
        result.push_back(line.substr(start, end - start));
        start = end + delim.length();
        end = line.find(delim, start);
    }

    result.push_back(line.substr(start, end));
    return result;
}
