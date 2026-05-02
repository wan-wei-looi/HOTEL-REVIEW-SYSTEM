#ifndef PERSON_H
#define PERSON_H

#include<iostream>
#include<string>

using namespace std;

class Person{
protected:
    string userID;
    string userName;
    string state;
    string email;
public:
    //constructor
    Person() : userID(""), userName(""), state(""), email(""){}
    
    //destructor
    ~Person(){}

    //class methods - setter
    void setUserID(string userID){this->userID = userID;}
    void setUserName(string userName){this->userName = userName;}
    void setState(string state){this->state = state;}
    void setEmail(string email){this->email = email;}

    //class methods - getters
    string getUserID()const{return userID;}
    string getUserName()const{return userName;}
    string getState()const{return state;}
    string getEmail()const{return email;}
};

#endif