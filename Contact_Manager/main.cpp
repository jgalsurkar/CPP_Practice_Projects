/**********************************************************
 Title:       main.cpp
 Author:      Jonathan Galsurkar
 Description: Opens up the main menu
 Purpose:     Go to the User Interface
 **********************************************************/

#include <iostream>

#include "UserInterface.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    //Creates an instance of the interface of type string and sends in the command line arguements
    UserInterface * contactInterface = new UserInterface(argc, argv);
    
    //The interface calls the main menu where the user will be able to interact with the program
    contactInterface->mainMenu();
    
    return 0;
}
