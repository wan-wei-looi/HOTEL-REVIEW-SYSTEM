#ifndef SYSTEMAPP_H
#define SYSTEMAPP_H

#include<iostream>
#include<string>
#include "Traveler.hpp"
#include "Review.hpp"
#include "UniqueHotel.hpp"

using namespace std;

//  Global constant:
const int TRAVELER_NUM = 10;
const int REVIEW_NUM = 50;

class SystemApp{
private:
    Traveler traveler[TRAVELER_NUM];
    Review review[REVIEW_NUM];
    UniqueHotel uniqueHotel[REVIEW_NUM];
public:
    SystemApp(int&);    // file reading
    ~SystemApp(){};   // file writing

    //class method - getter
    Traveler* getTraveler(){return traveler;}
    Review* getReview(){return review;}

    //method
    void addReview(Traveler[], int&);
    void hotelReview();
    void travelerManagement();
    void highestRatedHotel(const int&, int&);
    void topReviewers();

    //friend function
    friend void writeUserFile(Traveler[]);
};

#endif SYSTEMAPP_H