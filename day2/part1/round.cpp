#include "round.h"
/*
    Each game contains many rounds
    In each round:
     - Rock beats Scissors
     - Scissors beats paper
     - Paper beats Rock

    If both pick the same, its a draw
*/

using namespace std;

Shape Round::get_shape(char* input) {
    /*
        Their Sym   Our sym     Hand
        A           X           Rock
        B           Y           Paper
        C           Z           Scissor
    */

    if (strncmp(input, "A", 1) == 0 || strncmp(input, "X", 1) == 0) return ROCK;
    if (strncmp(input, "B", 1) == 0 || strncmp(input, "Y", 1) == 0) return PAPER;
    if (strncmp(input, "C", 1) == 0 || strncmp(input, "Z", 1) == 0) return SCISSOR;
    return ROCK;
}

int Round::compare(Shape theirs, Shape ours) {
    const int DRAW_SCORE = 3;
    const int WIN_SCORE = 6;
    const int LOSE_SCORE = 0;
    
    if (theirs == ours)
        return DRAW_SCORE;

   if (ours == ROCK && theirs == SCISSOR) return WIN_SCORE;
   if (ours == PAPER && theirs == ROCK) return WIN_SCORE;
   if (ours == SCISSOR && theirs == PAPER) return WIN_SCORE;

   return LOSE_SCORE;
}

int Round::get_shape_score(Shape shape) {
    if (shape == ROCK) return 1;
    if (shape == PAPER) return 2;
    if (shape == SCISSOR) return 3;
    return 0;
}

int Round::compute(string input) {
    Shape theirs = get_shape(&input[0]);
    Shape ours = get_shape(&input[2]);

    int our_shape_score = get_shape_score(ours);
    int round_score = compare(theirs, ours);
    return our_shape_score + round_score;
}