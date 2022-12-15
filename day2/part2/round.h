#ifndef ROUND_H
#define ROUND_H

#include <string>
#include <cstring>

enum Shape {
    ROCK,
    SCISSOR,
    PAPER
};

enum Condition {
    CONDITION_WIN,
    CONDITION_LOSE,
    CONDITION_DRAW
};


class Round {
    public:
        int compute(std::string);
    private:
        int compare(Shape,Shape);
        int get_shape_score(Shape);
        Shape get_shape(char*);
        Shape get_shape(Shape, Condition);
        Condition get_condition(char*);
};

#endif