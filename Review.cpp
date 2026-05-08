#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>

#include "Review.h"

using namespace std;

//  file reading
void Review::readReviewList(fstream& revFile){
    string input;
    int numInput;

    getline(revFile, input, '\t');
    setUserID(input);
    userID = input;

    revFile >> numInput;
    revFile.ignore();
    setRating(numInput);
    rating = numInput;

    getline(revFile, input, '\t');
    setReview(input);
    review = input;

    getline(revFile, input, '\n');
    setHotelName(input);
    hotelName = input;

    while(revFile.peek() == '\n'){
        revFile.ignore();
    }
}

void Review::printReview()const{
    cout << setw(8) << left << userID << " | "
         << setw(10) << left << rating << " | "
         << setw(25) << left << hotelName << " | "
         << review << endl;
}