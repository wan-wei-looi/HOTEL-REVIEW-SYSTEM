#ifndef TRAVELER_H
#define TRAVELER_H

#include<iostream>
#include<string>
#include "Person.h"
#include "Review.h"

using namespace std;

//global constant - fixed number of traveler
const int TRAVELER_NUM = 15;
const int TRAVELER_REV_NUM = 10;

class Traveler: public Person{
private:
    string memberType;
    int point;
    int reviewNumber;
    double averageRating;

    Review review[TRAVELER_REV_NUM];

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

    void readTravelerInfo(fstream&);                            //file reading

    void assignTravelerReviewInfo(Review[], const int&);        //updates the review, number of reviews and average rating of traveler
    
    static void searchReview(Traveler[], const int&);
    static void travelerManagement(Traveler[], const int&);
    static void topReviewers(Traveler[], const int&);

    void printTravelerInfo()const;
    void printTravelerReview()const;

    //operator overloading
    bool operator==(const Traveler&)const;
    bool operator<(const Traveler&)const;
    
    //friend function
    friend void writeUserFile(Traveler[], const int&, fstream&);
};

#endif