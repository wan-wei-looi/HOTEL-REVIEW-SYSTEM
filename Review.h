#ifndef REVIEW_H
#define REVIEW_H

#include<iostream>
#include<string>

using namespace std;

//global constant - fixed maximum number of reviews a user can have
const int REVIEW_NUM = 50;

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

    //setter
    void setUserID(string userID){this->userID = userID;}
    void setRating(int rating){this->rating = rating;}
    void setReview(string review){this->review = review;}
    void setHotelName(string hotelName){this->hotelName = hotelName;}

    //getter
    string getUserID()const{return userID;}
    int getRating()const{return rating;}
    string getReview()const{return review;}
    string getHotelName()const{return hotelName;}

    //class methods
    //  file reading
    void readReviewList(fstream&);

    //  print
    void printReview()const;
};

#endif