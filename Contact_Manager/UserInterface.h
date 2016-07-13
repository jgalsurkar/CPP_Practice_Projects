/**********************************************************
 Title:       UserInterface.h
 Author:      Jonathan Galsurkar
 Description: Allows the user print the contact list,
 insert to it, delete from it, display a contact
 and save the current state of the list
 Purpose:     User functionality for their Contact List
 **********************************************************/

#ifndef UserInterface_h
#define UserInterface_h

#include "ContactManager.h"

using namespace std;

const int MAX = 4;

class UserInterface {
private:
    ContactManager * manager;
    
public:
    UserInterface(int argc, const char * argv[]);
    /*Constructor for the UserInterface. Passes in the command line and
     creates a contact manager by passing its parameters as arguements*/
    
    void mainMenu();
    /*Giant switch statement allowing the user to pick the functionality they want.
     Only accepts input 1-6. Calls every other function below and lets the user know
     how successful they were with their interaction */
    
    bool printContactList();
    /*Creates a list which is set to the contact managers list. It then
     goes through the list and retrives each contact and prints it's info one by
     one as well as the size of the list at the end. It returns true as long as the
     list isnt empty.*/
    
    bool insertToList();
    /*Asks the user for all the necessary information and stores it into
     an array. it then calls the contact managers insertContact function with the
     array as its parameter. if all was successul it returns true. Else false.*/
    
    bool deleteFromList();
    /*Asks the user for all the necessary information and stores it into
     an array. it then calls the contact managers deleteContact function with the
     array as its parameter. if the delete was succesful it returns true. Otherwise
     the contact doesnt exist and it returns false*/
    
    bool displayContact();
    /*Asks the user for all the necessary information and stores it into
     an array. it then calls the contact managers retrieveContact function with the
     array as its parameter. If the contact was found it displays it's information and returns true. Otherwise it
     returns false.*/
    
    bool saveContactList();
    /*Calls the contact managers saveList function which saves the state of the list and makes  a backup.
     It returns true if saveList returns true, and false otherwise.*/
    
};

UserInterface::UserInterface(int argc, const char * argv[]){
    manager  = new ContactManager (argc, argv);
    
}

void UserInterface::mainMenu(){
    
    char choice;
    //Prints a main menu for the user to input choices
    do{
        cout << "       +---------------------------------------------------------------+" << endl;
        cout << "       |    Press 1 to print the entire contact list alphabetically    |" << endl;
        cout << "       |    Press 2 to insert a new contact.                           |" << endl;
        cout << "       |    Press 3 to delete an existing contact.                     |" << endl;
        cout << "       |    Press 4 to display any contact.                            |" << endl;
        cout << "       |    Press 5 to save the current state of the contact list.     |" << endl;
        cout << "       |    Press 6 to quit the program                                |" << endl;
        cout << "       +---------------------------------------------------------------+" << endl;
        
        //Does not allow an invalid input and loops until their input is valid.
        cin  >> choice;
        while( (choice != '0') && (choice != '1') && (choice != '2') && (choice != '3') && (choice != '4') && (choice != '5') && (choice != '6')){
            cerr << "Invalid input. Please enter a choice between 1 and 6." << endl;
            cin  >> choice;
        }
        switch (choice){
                
            case '1' :
                if(!printContactList())
                    cout << "No contacts in list" << endl;
                break;
                
            case '2' :
                if(!insertToList())
                    cout << " * * * Error: exceeding the maximum size of the list. * * * \n" << endl;
                else
                    cout << " + + + Successfully inserted contact. + + + \n" << endl;
                break;
                
            case '3' :
                if(!deleteFromList())
                    cout << " * * * Error: No such contact exists. * * * \n" << endl;
                else
                    cout<< " + + + Sucessfully deleted contact. + + + \n" <<endl;
                break;
                
            case '4' :
                if(!displayContact())
                    cout << " * * * Error: No such contact exists. * * * \n" << endl;
                break;
                
            case '5' :
                if(!saveContactList())
                    cout << " * * * Error: There are no contacts to save * * * \n" << endl;
                else
                    cout << " + + + Contact List was saved successfully + + + \n" << endl;
                break;
        }
        
        
    }while(choice != '6');
}

bool UserInterface::printContactList(){
    AbstractList<Contact> * temp_list = manager->getAllContacts();
    //Create a list which now has all the contacts
    int length = temp_list->getLength();
    if(length == 0){
        return false;
    }
    
    Contact temp_contact;
    //retrieve each contact from every position in the list and print it out
    for(int i = 1; i <= length; i++){
        temp_contact = temp_list->retrieve(i);
        cout << "Contact # " << i << "\n" << endl;
        cout << temp_contact.getLName() << ", " << temp_contact.getFName() << endl;
        cout << "Phone Number: " << temp_contact.getphoneNum() << endl;
        cout << "Email: " << temp_contact.getEmail() << "\n" <<endl;
    }
    cout << "Total Contacts: " << length << endl;
    return true;
}

bool UserInterface::insertToList(){
    
    string info_array[MAX];
    //Garbage is for getline since it skips one field without a getline before it.
    string data;
    string garbage;
    //Let user input all fields in a Contact and omit what is allowed
    cout << "\n--- NOTE : You may omit the phone number and email. ----" << "\n";
    
    cout << "\nInput the first name of the contact you would like inserted" << endl;
    cin  >> data;
    info_array[0] = data;
    
    cout << "Input the last name of the contact you would like inserted" << endl;
    cin  >> data;
    info_array[1] = data;
    
    cout << "Input the phone number of the contact you would like inserted" << endl;
    getline(cin, garbage);
    getline(cin, data);
    if(data.empty()){
        data = "";
    }
    info_array[2] = data;
    
    cout << "Input the email of the contact you would like inserted" << endl;
    getline(cin, data);
    if(data.empty()){
        data = "";
    }
    info_array[3] = data;
    
    //use the manager to insert a contact with the data just obtained
    if(!manager->insertContact(info_array)){
        return false;
    }
    return true;
    
    
}

bool UserInterface::deleteFromList(){
    
    string info_array[MAX];
    
    string data;
    //Garbage is for getline since it skips one field without a getline before it.
    string garbage;
    
    //Let user input all fields in a Contact and omit what is allowed
    cout << "\n--- NOTE : You may omit all the fields except the last name" << endl;
    cout <<"BUT WARNING, IT SHALL DELETE EVERYONE WITH WHATEVER FIELDS INPUTTED. ----" << "\n";
    
    cout << "\nInsert the first name of the contact you would like to delete" << endl;
    getline(cin, garbage);
    getline(cin, data);
    if(data.empty()){
        data = "";
    }
    info_array[0] = data;
    
    cout << "Insert the last name of the contact you would like to delete" << endl;
    cin  >> data;
    info_array[1] = data;
    
    cout << "Insert the phone number of the contact you would like to delete" << endl;
    getline(cin, garbage);
    getline(cin, data);
    if(data.empty()){
        data = "";
    }
    info_array[2] = data;
    
    cout << "Insert the email of the contact you would like to delete" << endl;
    getline(cin, data);
    if(data.empty()){
        data = "";
    }
    info_array[3] = data;
    
    //use the manager to delete a contact with the data just obtained
    if(manager->deleteContact(info_array)){
        return true;
    }
    return false;
    
}

bool UserInterface::displayContact(){
    
    string info_array[MAX];
    
    string data;
    //Garbage is for getline since it skips one field without a getline before it.
    string garbage;
    
    cout << "\n--- NOTE : Please insert at least one field regardless of which one. ----" << "\n";
    
    cout << " \nInsert the first name of the contact you would like to display" << endl;
    getline(cin, garbage);
    getline(cin, data);
    if(data.empty()){
        data = "";
    }
    info_array[0] = data;
    
    cout << "Insert the last name of the contact you would like to display" << endl;
    getline(cin, data);
    if(data.empty()){
        data = "";
    }
    info_array[1] = data;
    
    cout << "Insert the phone number of the contact you would like to display" << endl;
    getline(cin, data);
    if(data.empty()){
        data = "";
    }
    info_array[2] = data;
    
    cout << "Insert the email of the contact you would like to display" << endl;
    getline(cin, data);
    if(data.empty()){
        data = "";
    }
    info_array[3] = data;
    
    //There is no contact with no fields so this will returns false
    if((info_array[0] == "") && (info_array[1] == "") && (info_array[2] == "") && (info_array[3] == "") ){
        return false;
    }
    
    //A temporary contact is set equal to the retrieve of the specific contact done by manager
    Contact temp_contact = manager->retrieveContact(info_array);
    
    //this is a flag to see if we found it.
    string temp = temp_contact.getLName();
    if(temp == "")
        return false;
    //otherwise we did find it thus it prints its elements
    else{
        
        cout << "Last Name: " << temp_contact.getLName() << endl;
        cout << "First Name: " << temp_contact.getFName() << endl;
        cout << "Phone Number: " << temp_contact.getphoneNum() << endl;
        cout << "Email: " << temp_contact.getEmail() << endl;
        return true;
    }
}

bool UserInterface::saveContactList(){
    //Calls saveList from manager which makes a backup.
    if(manager->saveList())
        return true;
    return false;
}

#endif /* UserInterface_h */
