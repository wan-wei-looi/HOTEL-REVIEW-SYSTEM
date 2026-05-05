#ifndef UNIQUE_HOTEL_H
#define UNIQUE_HOTEL_H

#include<iostream>
#include<string>
#include "Traveler.h"
#include "Review.h"

using namespace std;

//global constant - fixed maximum number of reviews a hotel can have
const int HOTEL_REV_NUM = 10;

class UniqueHotel{
private:
    Review review[HOTEL_REV_NUM];
    int numReview;
    double averageRating;

public:
    //constructor
    UniqueHotel() : numReview(0), averageRating(0){}

    //destructor
    ~UniqueHotel(){}

    //getter
    string getHotelName()const{return review[0].getHotelName();}
    int getNumReview()const{return numReview;}
    double getAverageRating()const{return averageRating;}
    
    //class methods

    //  create a list of unique hotels by this  //
    //  pointer to move along the array of      //
    //  uniqueHotelNum of uniqueHotels          //
    void assignUniqueHotels(const Traveler[], const int&, int&);

    //  sorting the hotel list based on average rating
    static void sortHotel(UniqueHotel[], const int&);

    static void searchReview(UniqueHotel[], const int&);
    
    void printUniqueHotel(const int&)const;

    //  operator overloading
    bool operator>(const UniqueHotel&)const;
};

#endif