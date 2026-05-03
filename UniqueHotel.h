#ifndef UNIQUE_HOTEL_H
#define UNIQUE_HOTEL_H

#include<iostream>
#include<string>
#include "Review.h"

using namespace std;

class UniqueHotel : public Review{
private:
    int numReview;
    double averageRating;

public:
    //constructor
    UniqueHotel() : numReview(0), averageRating(0){}

    //destructor
    ~UniqueHotel(){}

    //getter
    int getNumReview()const{return numReview;}
    double getAverageRating()const{return averageRating;}
    
    //class methods

    //  create a list of unique hotels by this  //
    //  pointer to move along the array of      //
    //  uniqueHotelNum of uniqueHotels          //
    void assignUniqueHotels(const Review[], const int&, int&);

    //  sorting the hotel list based on average rating
    static void sortHotel(UniqueHotel[], const int&);
    
    void printUniqueHotel(const int&)const;

    //  operator overloading
    UniqueHotel& operator=(const Review&);
    bool operator>(const UniqueHotel&)const;
};

#endif