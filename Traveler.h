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
    Traveler() : memberType(""), point(0), reviewNumber(0), averageRating(0){}

    //destructor
    ~Traveler(){}
    
    //class methods - setters
    void setMemberType(string memberType){this->memberType = memberType;}
    void setPoint(int point){this->point = point;}
    void setReviewNumber(int num){reviewNumber = num;}
    void setAverageRating(double ave){averageRating = ave;}
    
    //class methods - getters
    string getMemberType()const{return memberType;}
    int getPoint()const{return point;}
    int getReviewNumber()const{return reviewNumber;}
    double getAverageRating()const{return averageRating;}

    //operator overloading
    bool operator==(const Traveler&)const;
    bool operator<(const Traveler&)const;
    
    //friend function
    friend void writeUserFile(Traveler[]);
};

#endif