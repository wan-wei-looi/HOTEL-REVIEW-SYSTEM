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
    string getUserID()const{return userID;}
    int getRating()const{return rating;}
    string getReview()const{return review;}
    string getHotelName()const{return hotelName;}

    //class method - print function
    void printReview()const;

    //friend function
    friend void writeReviewFile(Review[], int&);
};

#endif