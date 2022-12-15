#ifndef ROUND_H
#define ROUND_H

#include <string>
#include <cstring>

enum Shape {
    ROCK,
    PAPER,
    SCISSOR
};

class Round {
    public:
        int compute(std::string);
    private:
        int compare(Shape,Shape);
        int get_shape_score(Shape);
        Shape get_shape(char*);
};

#endif