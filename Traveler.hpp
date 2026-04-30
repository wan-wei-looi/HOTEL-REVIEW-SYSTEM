#ifndef TRAVELER_H
#define TRAVELER_H

#include<iostream>
#include<string>
#include "Person.hpp"

class Traveler: public Person{
private:
    string memberType;
    int point;
public:
    //constructor
    Traveler() : memberType(""), point(0){}

    //destructor
    ~Traveler(){}
    
    //class methods - setters
    void setMemberType(string);
    void setPoint(int);
    
    //class methods - getters
    string getMemberType(){return memberType;}
    int getPoint(){return point;}
    
    //friend function
    friend void printTravelerInfo(Traveler);

    friend bool readWriteUserFile(Traveler[], bool);
};

#endif TRAVELER_H