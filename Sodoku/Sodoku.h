/**********************************************************
 Title:       Sodoku.h
 Author:      Jonathan Galsurkar
 Description: Generates a fully valid sodoku board by just
 running the program
 Purpose:     See many random completed sodoku puzzles
 without doing any work!
 **********************************************************/

#ifndef Sodoku_h
#define Sodoku_h

class Sodoku
{
public:
    Sodoku();
    /*Constructor which takes no parameters
     Pre-condition:  Board is filled with nothing
     Post-condition: Every position in the board is set to
     0 and the first position is set to a
     random number between 1 and 9.     */
    
    void solveAndPrint();
    /*A void function(returns nothing) that takes in no paramters. It calls the
     solveBoard function which fills the board with valid numbers. It then
     outputs the two-dimensional array board, also making it it look pretty!
     Pre-condition: None
     Post-constion: Once called, prints out an awesome random completed Sodoku board
     */
    
private:
    bool isVacantSpot(int rowP, int columnP);
    /*Function that takes in two integers: a row and a column
     and returns a boolean. It checks to see if a certain
     position on the board is vacant(the spot is a 0)
     Pre-condition:  Must recieve a row and column to check
     Post-condition: Returns true if the position is a 0
     and false otherwise.
     */
    bool numExistsInRow(int rowP, int numberP);
    /*Function that takes in two integers: a row and a number
     and returns a boolean. It check if that number is in the row
     passed in
     Pre-condition:  It is assumed the number does not exist in the row
     Post-conditionL If the number is found in the row it will return true
     and return false otherwise.                         */
    
    bool numExistsInColumn(int columnP, int numberP);
    /*Function that takes in two integers: a column and a number
     and returns a boolean. It check if that number is in the column
     passed in
     Pre-condition:  It is assumed the number does not exist in the column
     Post-conditionL If the number is found in the column it will return true
     and return false otherwise.                            */
    
    bool numExistsInSubGrid(int rowP, int columnP, int numberP);
    /*Function that takes in three integers: a column,a row, and a number
     and returns a boolean. It check if that number is in the 3 by 3 grid
     surrounding the number based on the row and column passed in.
     Pre-condition:  It is assumed the number does not exist in the sub grid
     Post-condition: If the number is found in the sub grid it will return true
     and return false otherwise.                             */
    
    bool canAlterSpot(int rowP, int columnP, int numberP);
    /*Function that takes in three integers: a column,a row, and a number
     and returns a boolean. It checks to see if you are allowed to alter the spot
     by checking if the the number passed is NOT in the row, column, and sub grid.
     This is done by calling the three functions above
     Pre-condition: A row, column, and number are passed
     Post-conditon: If the number does NOT exist in the row AND the column AND the subgrid
     then it will return true. If it exists in any of them it will return false.*/
    
    bool solveBoard(int rowP, int columnP);
    /*  Function that takes in two integers: a column and a number
     and returns a boolean. It first checks every column in each row
     to see if it is less then the maximum column size and is not vacant(calling the
     isVacant function) until it hits that max column size. If it does it moves on
     the the next row and repeats. If it has gone through every row, the
     function returns true.
     While going through each row it places a number between 1 and 9 in every
     position if the spot can be altered(calling the canAlterSpot function). In an if statement,
     it then recursively calls itself and the while loop in the beginning does the incrementing for us.
     It continues like this until it hits the base case returning true. Otherwise if at any instance
     the spot cannot be altered, it backtracks and sets that row and column back to 0 and returns false
     which sets a chain of backtracking if necessary until it begins returning true again up until the base case */
    
    int board[9][9];
    //Creates a 9 by 9 two-dimensional array which will be the board for sodoku
};

#endif /* Sodoku_h */
