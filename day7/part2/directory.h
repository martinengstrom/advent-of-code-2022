#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <vector>
#include "file.h"

class directory {
    public:
        void add_file(file*);
        void add_directory(directory*);
        long calculate_size();
        directory* get_parent();
        std::string get_name();
        std::vector<directory*> get_subdirectories();
        directory(std::string, directory*);
        ~directory();
    private:
        std::vector<directory*> directories;
        std::vector<file*> files;
        std::string name;
        directory* parent;
};

#endif
