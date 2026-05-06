#include<iostream>
#include<string>
#include<iomanip>

#include "Review.h"

using namespace std;

void Review::printReview()const{
    cout << setw(8) << left << userID << " | "
         << setw(10) << left << rating << " | "
         << setw(25) << left << hotelName << " | "
         << review << endl;
}