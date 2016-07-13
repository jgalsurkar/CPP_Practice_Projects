/**********************************************************
 Title:       Contact.h
 Author:      Jonathan Galsurkar
 Description: Holds the information for a contact and methods
              to retreive it
 Purpose:     Allows you to get and set all data in a contact
 **********************************************************/

#ifndef Contact_h
#define Contact_h

class Contact {
    
private:
    std::string first_name;
    std::string last_name;
    std::string phone_num;
    std::string email;
    
public:
    std::string getLName() {return last_name;} //returns the last name
    std::string getFName() {return first_name;} //returns the first name
    std::string getphoneNum() {return phone_num;} //returns the phoneNum
    std::string getEmail() {return email;} //returns the email
    
    void setLName(std::string lName) {last_name = lName;} //sets the last name with the parameter
    void setFName(std::string fName) {first_name = fName;} //sets the first name with the parameter
    void setphoneNum(std::string phone_numP) {phone_num = phone_numP;} //sets the phoneNum with the parameter
    void setEmail(std::string emailP) {email = emailP;} //sets the email with the parameter
    bool operator< (const Contact &right);
};

bool Contact::operator< (const Contact &right){
    if (this->last_name == right.last_name)
        return this->first_name < right.first_name;
    return this->last_name < right.last_name;
}

#endif /* Contact_h */
