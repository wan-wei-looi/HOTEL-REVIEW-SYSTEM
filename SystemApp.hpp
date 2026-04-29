#ifndef SYSTEMAPP_H
#define SYSTEMAPP_H

#include<iostream>
#include<string>
#include "Traveler.hpp"
#include "Review.hpp"

using namespace std;

class SystemApp{
private:
    Traveler traveler[10];
    Review review[50];
public:
    SystemApp();
    ~SystemApp();

    void hotelSummary();
    void travelerManagement();
    void highestRatedHotel();
    void topReviewers();

    Traveler operator+(int);
    bool operator>(const Review&);
};

#endif SYSTEMAPP_H