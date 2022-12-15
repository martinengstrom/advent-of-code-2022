#include <iostream>
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

int main(int argc, char *argv[]) {
   Round round;
   int total = 0;
   for (string line; getline(cin, line); ) {
       total += round.compute(line);
   }
   cout << total << endl;
}
