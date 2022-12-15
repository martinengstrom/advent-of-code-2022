#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[]) {
    std::vector<int> cals;
    int i = 0;
    for (std::string line; std::getline(std::cin, line);) {
        if (line.length() == 0) {
            cals.push_back(i);
            i = 0;
        } else {
            i += std::stoi(line);
        }
    }
    std::sort(cals.begin(), cals.end());
    std::cout << cals[cals.size() - 1] << std::endl;
    return 0;
}
