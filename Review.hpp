#ifndef REVIEW_H
#define REVIEW_H

#include<iostream>
#include<string>

using namespace std;

class Review{
private:
    string userID;
    int rating;
    string review;
    string hotelName;

public:
    //constructor
    Review() : userID(""), rating(0), review(""), hotelName(""){}
    
    //destructor
    ~Review(){};

    //class method - setter
    void setReview(string, int, string, string);

    //class method - getter
    int getRating(){return rating;}
    string getReview(){return review;}
    string getHotelName(){return hotelName;}

    //friend function
    friend void printReview(Review);
};

#endif REVIEW_H