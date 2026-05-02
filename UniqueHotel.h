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

    //class method - setter
    void setNumReview(int num){numReview = num;}
    void setAverageRating(double ave){averageRating = ave;}

    //class method - getter
    int getNumReview()const{return numReview;}
    double getAverageRating()const{return averageRating;}

    //operator overloading
    UniqueHotel& operator=(const Review&);
    bool operator>(const UniqueHotel&)const;
};

#endif