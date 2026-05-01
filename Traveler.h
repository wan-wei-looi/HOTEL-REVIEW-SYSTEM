#ifndef TRAVELER_H
#define TRAVELER_H

#include<iostream>
#include<string>
#include "Person.h"

class Traveler: public Person{
private:
    string memberType;
    int point;
    int reviewNumber;
    double averageRating;
public:
    //constructor
    Traveler() : memberType(""), point(0){}

    //destructor
    ~Traveler(){}
    
    //class methods - setters
    void setMemberType(string);
    void setPoint(int);
    void setReviewNumber(int);
    void setAverageRating(double);
    
    //class methods - getters
    string getMemberType()const{return memberType;}
    int getPoint()const{return point;}
    int getReviewNumber()const{return reviewNumber;}
    double getAverageRating()const{return averageRating;}

    //class method - print function
    void printTraveler()const;

    //operator overloading
    bool operator==(const Traveler&);
    bool operator<(const Traveler&);
    
    //friend function
    friend void writeUserFile(Traveler[]);
};

#endif