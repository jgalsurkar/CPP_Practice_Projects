/**********************************************************
 Title:       Sodoku.cpp
 Author:      Jonathan Galsurkar
 Description: Generates a fully valid sodoku board by just
 running the program
 **********************************************************/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Sodoku.h"

using namespace std;

const int rowMax = 9;
const int columnMax = 9;

Sodoku::Sodoku()
{
    srand(time(0)); // Sets a random number generator based on the current time which is constantly changing.
    //Initializing the board to 0
    for(int row = 0; row<rowMax; row++){
        for(int column = 0; column<columnMax; column++){
            board[row][column] = 0;
        }
    }
    board[0][0] = 1 + (rand() % 9);//Setting a random number in Position [0][0], the first position.
}

bool Sodoku::isVacantSpot(int rowP, int columnP)
{
    if(board[rowP][columnP] == 0){ //Checks if the board in that position equals 0
        return true;
    }
    else
        return false;
}

bool Sodoku::numExistsInRow(int rowP, int numberP)
{
    bool existsInRow = false;
    
    //Checks if the number given is in the row by looping through it and checking for each position
    for(int i = 0; i<rowMax; i++){
        if(board[rowP][i] == numberP){
            existsInRow = true;
        }
    }
    return existsInRow;
}

bool Sodoku::numExistsInColumn(int columnP, int numberP)
{
    bool existsInColumn = false;
    
    //Checks if the number given is in the column by looping through it and checking for each position
    for(int i = 0; i<columnMax; i++){
        if(board[i][columnP] == numberP){
            existsInColumn = true;
        }
    }
    return existsInColumn;
}

bool Sodoku::numExistsInSubGrid(int rowP, int columnP, int numberP)
{
    /*We need to get back to the beginning position of each 3 by 3 sub grid.
     Both the row and column have an initial position of 0 and ending position of 8.
     Positions of 0,3 and 6 mod 3 would give us 0 and those positions subtracted from
     the given row and column would allow us to keep them in their current place.
     positions of 1,4, and 7 mod 3 would give us 1 so by subtracting them from the
     given row and column would move them up or left by 1 position.
     Positions of 2, 5 and 8 mod 3 would give us 2 so by subtracting them from the
     given row and column would move them up or left by 2 positions.
     This allows us to hit the beginning of each sub gride since those positions are 0,
     3 and 6 since those mod 3 = 0.*/
    int subRow = rowP - (rowP%3);
    int subColumn = columnP - (columnP%3);
    
    bool existsInSubGrid = false;
    
    for(int tempRow = subRow; tempRow<subRow+3; tempRow++){/*We add three to subRow so we can go down through the three
                                                            rows from the start of the sub grid.*/
        for(int tempColumn = subColumn; tempColumn<subColumn+3; tempColumn++){//We add three to subColumn so we
            if(board[tempRow][tempColumn] == numberP){                        //can go right three columns for the start of the sub grid
                existsInSubGrid = true;
            }
        }
    }
    return existsInSubGrid;
}

bool Sodoku::canAlterSpot(int rowP, int columnP, int numberP)
{
    /*We check that the numbers do NOT appear in any of the following and return true if they dont.
     If they do in either one it will return false. */
    if( (!numExistsInRow(rowP, numberP)) && (!numExistsInColumn(columnP, numberP)) && (!numExistsInSubGrid(rowP, columnP, numberP)) ){
        // Testing-cout<<"returning true canAlterSpot"<<endl;
        return true;
    }
    else
        return false;
}

bool Sodoku::solveBoard(int rowP, int columnP)
{
    /*This function will first be called with the row and column in
     position 0,0 which will be filled with a random number. The while loop is used for incrementing the rows and
     column for the recursion. The numbers will be placed in the row and column later*/
    while (rowP < rowMax && !isVacantSpot(rowP,columnP)) {
        columnP++;
        if (columnP == columnMax) {
            rowP++;
            columnP = 0;
        }
    }
    
    /*BASE CASE. The board's maximum position for the row is 8, if we
     go past that, then we have reached the end of the board thus returning true to
     get out of the recursion*/
    if (rowP == rowMax){
        return true;
    }
    
    /*The for look will check if that number can go into a certain position
     by seeing if it can alter the spot. If it can then it will place the number
     and call the function again, in which the while loop will increment the row or column
     to get to the next position. Since solve is a boolean it will return true and as we
     run through sucessful recursions it will continuous let the if statement return true which
     after reaching the base case will set a chain of returning true*/
    for(int number = 1; number<=9; number++){
        if(canAlterSpot(rowP, columnP, number)){

            board[rowP][columnP] = number;
            if(solveBoard(rowP,columnP)){
                return true;
            }
        }
    }
    /*This is the backtracking, in the case you cannot alter the spot in
     an instance of the recursion it will place that position back to 0 and
     return false which will change the number that the loop will try to put in
     to alter the spot. T*/
    board[rowP][columnP] = 0;
    return false;
}

void Sodoku::solveAndPrint()
{
    /*Calls the solveBoard function with the row and column to be 0,0
     the counts will be used to seperate parts of the board for an
     organized sodoku board*/
    solveBoard(0,0);
    int count1 = 0;
    int count2 = 0;
    
    /*Outputting the two dimensional array. Every three numbers we want
     to seperate them by either = signs or | sign depending on whether
     it is the row or column in order to give the baord a more organized look.*/
    for(int i = 0; i<rowMax; i++){
        if(count2 % 3 == 0){
            cout << " ===========================" <<endl;
        }
        for(int j = 0; j<columnMax; j++){
            if(count1 % 3 == 0){
                cout << " | ";
            }
            cout << board[i][j] << " ";
            count1++;
        }
        count2++;
        cout << "|";
        cout << endl;
    }
    cout << " ===========================" <<endl;
}