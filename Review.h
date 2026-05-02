#ifndef REVIEW_H
#define REVIEW_H

#include<iostream>
#include<string>

using namespace std;

class Review{
protected:
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

    //class method
    void readReviewList(fstream&);

    static void searchReview(Review[]);
    static void addReview(int&, const string[], Review[]);

    void printReview()const;

    //friend function
    friend void writeReviewFile(Review[], const int&, fstream&);
};

#endif