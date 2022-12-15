#include "directory.h"

using namespace std;

void directory::add_file(file* f) {
    this->files.push_back(f);
}

void directory::add_directory(directory* d) {
    this->directories.push_back(d);
}

long directory::calculate_size() {
    long total = 0;
    for (auto& file : this->files) {
        total += file->get_size();
    }

    for (auto& dir : this->directories) {
        total += dir->calculate_size();
    }

    return total;
}

directory* directory::get_parent() {
    return this->parent;
}

string directory::get_name() {
    return this->name;
}

vector<directory*> directory::get_subdirectories() {
    return this->directories;
}

directory::directory(string name, directory* parent){
    this->name = name;
    this->parent = parent;
}

directory::~directory() {
    for (auto& dir : this->directories) {
        delete dir;
    }

    for (auto& file : this->files) {
        delete file;
    }
}
