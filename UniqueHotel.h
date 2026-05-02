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
    
    //class method
    static void assignUniqueHotels(const int&, int&, const Review[], UniqueHotel[]);
    static void sortHotel(const int&, UniqueHotel[]);
    
    void printUniqueHotel(const int&)const;

    //operator overloading
    UniqueHotel& operator=(const Review&);
    bool operator>(const UniqueHotel&)const;
};

#endif