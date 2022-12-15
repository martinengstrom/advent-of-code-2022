#include "file.h"

using namespace std;

string file::get_name() {
    return this->name;
}

long file::get_size() {
    return this->size;
}

file::file(string name, long size) {
    this->name = name;
    this->size = size;
}
