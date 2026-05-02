#ifndef TRAVELER_H
#define TRAVELER_H

#include<iostream>
#include<string>
#include "Person.h"
#include "Review.h"

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
    
    //setters
    void setMemberType(string memberType){this->memberType = memberType;}
    void setPoint(int point){this->point = point;}
    
    //getters
    string getMemberType()const{return memberType;}
    int getPoint()const{return point;}
    int getReviewNumber()const{return reviewNumber;}
    double getAverageRating()const{return averageRating;}
    
    //class method
    void readTravelerInfo(fstream&);
    
    void assignReviewNumber(const int&, const Review[]);
    void assignAverageRating(const int&, const Review[]);
    
    static void travelerManagement(const int&, const int&, Traveler[], Review[]);
    static void topReviewers(const int&, Traveler[]);

    void printTraveler()const;

    //operator overloading
    bool operator==(const Traveler&)const;
    bool operator<(const Traveler&)const;
    
    //friend function
    friend void writeUserFile(Traveler[], const int&, fstream&);
};

#endif