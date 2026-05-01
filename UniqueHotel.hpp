#ifndef UNIQUE_HOTEL_H
#define UNIQUE_HOTEL_H

#include<iostream>
#include<string>
#include "Review.hpp"

using namespace std;
class UniqueHotel : public Review{
private:
    double averageRating;
public:
    //constructor
    UniqueHotel() : averageRating(0){}

    //destructor
    ~UniqueHotel(){}

    //class method - setter
    void setAverageRating(double);

    //class method - getter
    double getAverageRating()const{return averageRating;}

    //class method - print function
    void printUniqueHotel()const;

    //operator overloading
    UniqueHotel& operator=(const Review&);
    bool operator>(const UniqueHotel&)const;
};

#endif UNIQUE_HOTEL_H