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
    void setUserID(string);
    void setUserName(string);
    void setState(string);
    void setEmail(string);

    //class methods - getters
    string getUserID(){return userID;}
    string getUserName(){return userName;}
    string getState(){return state;}
    string getEmail(){return email;}
};

#endif