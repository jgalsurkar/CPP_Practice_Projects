/**********************************************************
 Title:       main.cpp
 Author:      Jonathan Galsurkar
 **********************************************************/

#include "Sodoku.h"

int main(int argc, const char * argv[]) {
    //Creates an instance of Sodoku class.
    Sodoku game;
    
    /*Prints a fully generated sodoku board by calling
     the function solveAndPrint*/
    game.solveAndPrint();
    
    return 0;
}
