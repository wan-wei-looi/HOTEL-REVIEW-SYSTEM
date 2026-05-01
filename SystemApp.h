#ifndef SYSTEMAPP_H
#define SYSTEMAPP_H

#include<iostream>
#include<string>
#include "Traveler.h"
#include "Review.h"
#include "UniqueHotel.h"

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
    void addReview(int&);
    void hotelReview();
    void travelerManagement();
    void sortHotel(const int&, int&);
    void topReviewers(const int&);

    //friend function
    friend void writeUserFile(Traveler[]);
};

#endif