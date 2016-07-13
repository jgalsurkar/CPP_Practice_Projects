/**********************************************************
 Title:       ContactManager.h
 Author:      Jonathan Galsurkar
 Description: Manages everything that goes on with a contact
 within a list.
 Purpose:     Header for all the contact functionality
 **********************************************************/

#ifndef ContactManager_h
#define ContactManager_h

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "AbstractList.h"
#include "PointerList.h"
#include "ArrayList.h"
#include "Contact.h"

using namespace std;

class ContactManager{
private:
    AbstractList<Contact> * main_list;
    int find(std::string info_array[]);
    /*Finds the position in the mainlist whos nodes data matches
     all the fields in the infoArray*/
    
public:
    ContactManager(int argc, const char * argv[]);
    /*Constructor for the ContactManager, opens the file in the
     command line, creates appropriate lists based on the the number
     of arguements and inserts the data from the file into the list*/
    
    AbstractList<Contact> * getAllContacts();
    /*returns the mainList*/
    
    bool insertContact(std::string info_array[]);
    /*Sets a contact with the data in the infoArray. Attempts
     to insert it in the mainList which should always work and returns true except for
     when we have reached the maximum size of the array based one, which it then returns false*/
    
    bool deleteContact(std::string info_array[]);
    /*Uses the find function with the infoArray passed. If the position was not found
     it returns false, otherwise it removes the contact from the list at that position*/
    
    Contact retrieveContact(std::string info_array[]);
    /*Uses the find function with the infoArray passed. The return type is a contact. If the position was not found that contacts last name is set to be empty, otherwise it calls the retrieve function and returns the contact recieved from it*/
    
    bool saveList();
    /*If the list is empty it will return false, otherwise it saves the current mainList to a text file and a backup file*/
};
ContactManager::ContactManager(int argc, const char * argv[]){
    
    ifstream fin;
    
    //Exits the program if the file isn't found.
    
    fin.open(argv[1]);
    if(fin.fail()){
        cerr << "No such file found. Gracefully exiting." << endl;
        exit(1);
    }
    
    /*If there are 2 arguements in the command line a pointer based list
     is created. Otherwise if there are 3, an array based is created with the
     third arguement being the size of the list*/
    
    int MAX = NULL;
    if (argc == 2){
        main_list = new PointerList<Contact> ();
    }
    else if (argc == 3){
        MAX = atoi(argv[2]);
        main_list = new ArrayList<Contact>(MAX);
    }
    
    Contact temp_contact;
    //If the list is empty, don't insert anything
    ifstream test;
    test.open(argv[1]);
    test.seekg(0, ios::end);
    //If the list isnt empty read from the file and make a contact to insert to the list
    if(test.tellg() != 0){
        
        string info_array[4];
        while(!fin.eof())
        {
            getline(fin, info_array[0], ',');
            getline(fin, info_array[1], ',');
            getline(fin, info_array[2], ',');
            getline(fin, info_array[3], '\n');
            
            temp_contact.setFName(info_array[0]);
            temp_contact.setLName(info_array[1]);
            temp_contact.setphoneNum(info_array[2]);
            temp_contact.setEmail(info_array[3]);
            
            //Dealing with array based lists that have more contacts in the file than the given size.
            try{
                main_list->insert(temp_contact);
            }
            catch(int){
                cout << " * * * Error: The file has more contacts than the list can hold. * * * " << endl;
                cout << " * * * Only inserted the first " << MAX << " contacts in the file * * * \n" << endl;
            }
        }
    }
}

int ContactManager::find(string info_array[]){
    //Flag to return if it wasnt found
    int pos = -1;
    //List shouldnt be empty and the info array must have at least one piece of data
    if (main_list->isEmpty())
        return pos;
    
    if(info_array[0] == "" && info_array[1] == "" && info_array[2] == "" && info_array[3] == "")
        return pos;
    
    int points;
    
    //If we hit a match per field, we increase the points. If points is equal to 4 everything matched.
    for(int i = 1; i <= main_list->getLength(); ++i){
        
        points = 0;
        Contact temp = main_list->retrieve(i);
        
        if(info_array[0] == "" || temp.getFName() == info_array[0])
            points++;
        
        if(info_array[1] == "" || temp.getLName() == info_array[1])
            points++;
        
        if(info_array[2] == "" || temp.getphoneNum() == info_array[2])
            points++;
        
        if(info_array[3] == "" || temp.getEmail() == info_array[3])
            points++;
        //If everything matched, return the position
        if(points == 4){
            pos = i;
            return pos;
        }
    }
    return pos;
}

AbstractList<Contact> * ContactManager::getAllContacts(){
    return main_list;
}

bool ContactManager::insertContact(string info_array[]){
    
    Contact temp;
    //set each field in the contact
    temp.setFName(info_array[0]);
    temp.setLName(info_array[1]);
    temp.setphoneNum(info_array[2]);
    temp.setEmail(info_array[3]);
    
    //Try to insert, this is mostly for the array based which has a finite size and wont insert after
    try{
        main_list->insert(temp);
    }
    catch(int){
        return false;
    }
    return true;
}

bool ContactManager::deleteContact(string info_array[]){
    //-1 is the flag, so if position is equal to that we return false
    int position = find(info_array);
    
    if(position == -1){
        return false;
    }//If many people share the same field they will all be deleted
    else{
        while(position != -1){//loops through the list removing every instance until none are found
            main_list->remove(position);
            position = find(info_array);
        }
    }
    return true;
}

Contact ContactManager::retrieveContact(string info_array[]){
    
    int position = find(info_array);
    
    Contact retrieved_contact;
    
    if(position == -1)//flag to let us know if the contact is there or not
        retrieved_contact.setLName("");
    else
        retrieved_contact = main_list->retrieve(position);
    
    return retrieved_contact;
    
}

bool ContactManager::saveList(){
    
    if(main_list->isEmpty())
        return false;
    //two streams are made, one for backup and the actual file
    ofstream fout;
    ofstream foutBackup;
    
    fout.open("contactList.txt");
    foutBackup.open("contactList.bkp");
    
    int length = main_list->getLength();
    
    Contact temp;
    //Looping through the list and saving each contacts info into both files
    for(int i = 1; i <= length; i++){
        temp = main_list->retrieve(i);
        fout << temp.getLName() << "," << temp.getFName() << "," << temp.getphoneNum() << "," << temp.getEmail() << "\n";
        foutBackup << temp.getLName() << "," << temp.getFName() << "," << temp.getphoneNum() << "," << temp.getEmail() << "\n";
    }
    
    return true;
}




#endif /* ContactManager_h */


