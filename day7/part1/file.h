#ifndef FILE_H
#define FILE_H

#include <string>

class file {
    public:
        std::string get_name();
        long get_size();
        file(std::string, long);
    private:
        std::string name;
        long size;
};

#endif
