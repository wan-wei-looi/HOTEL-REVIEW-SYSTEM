#include<iostream>
#include<string>
#include<iomanip>

#include "Traveler.h"
#include "Review.h"
#include "UniqueHotel.h"

using namespace std;

//  assigning number of reviews and average     //
//  rating for each hotel start from the first  //
//  hotel with index[0] to the hotel with       //
//  index[uniqueHotelNum]                       //
void UniqueHotel::assignUniqueHotels(const Traveler tra[], const int& userCount, int& uniqueHotelNum){
    uniqueHotelNum = 0;
    
    for(int travelerIndex = 0; travelerIndex < userCount; travelerIndex++){
        for(int reviewIndex = 0; reviewIndex < tra[travelerIndex].getReviewNumber(); reviewIndex++){
            //  check for preexisting hotel;
            bool sameHotel = false;
            for(int hotelIndex = 0; hotelIndex < uniqueHotelNum; hotelIndex++){
                if((this + hotelIndex)->review[0].getHotelName() == tra[travelerIndex].getHotelName(reviewIndex)){
                    sameHotel = true;
                    break;
                }
            }

            if(!sameHotel){
                int hotelRevNum = 0;

                for(int traIndex = 0; traIndex < userCount; traIndex++){
                    for(int revIndex = 0; revIndex < tra[traIndex].getReviewNumber(); revIndex++){
                        if(tra[traIndex].getHotelName(revIndex) == tra[travelerIndex].getHotelName(reviewIndex)){
                            (this + uniqueHotelNum)->review[hotelRevNum++] = tra[traIndex].getReview(revIndex);
                        }
                    }
                }

                //  store hotel review number for each UniqueHotel object
                (this + uniqueHotelNum)->numReview = hotelRevNum;
    
                //  increments to the next unique hotel name
                uniqueHotelNum++;
            }
        }
    }

    // updating average rating for each hotel
    for(int hotelIndex = 0; hotelIndex < uniqueHotelNum; hotelIndex++){
        double rateSum = 0;
        int hotelRevNum = (this + hotelIndex)->numReview;

        for(int hotelReviewIndex = 0; hotelReviewIndex < hotelRevNum; hotelReviewIndex++){
            rateSum += (this + hotelIndex)->review[hotelReviewIndex].getRating();
        }

        (this + hotelIndex)->averageRating = (hotelRevNum)? (rateSum / hotelRevNum) : (rateSum);
    }
}

//  sorting unique hotels ONLY based on average rating
void UniqueHotel::sortHotel(UniqueHotel uniqueHotel[], const int& uniqueHotelNum){
    UniqueHotel temp;

    for(int i = 0; i < uniqueHotelNum; i++){
        for(int j = i + 1; j < uniqueHotelNum; j++){
            if(uniqueHotel[j] > uniqueHotel[i]){
                temp = uniqueHotel[i];
                uniqueHotel[i] = uniqueHotel[j];
                uniqueHotel[j] = temp;
            }
        }
    }
}

void UniqueHotel::searchReview(UniqueHotel hotel[], const int& uniqueHotelNum){
    string hotelName = "";
    int hotelRevNo = 0;

    cout << endl
         << "Insert hotel name: (Input is case sensitive)"
         << endl;

    getline(cin, hotelName);

    cout << endl
         << "HOTEL REVIEWS FOR : " << hotelName << endl
         << "=============================================================================================================" << endl
         << setw(8) << left << "User ID" << setw(10) << left << "| Rating" << setw(25) << left << "| Hotel" << "| Review" << endl
         << "=============================================================================================================" << endl;

    for(int hotelIndex = 0; hotelIndex < uniqueHotelNum; hotelIndex++){
        if(hotel[hotelIndex].getHotelName() == hotelName){
            for(int reviewIndex = 0; reviewIndex < hotel[hotelIndex].numReview; reviewIndex++){
                cout << setw(8) << left << hotel[hotelIndex].review[reviewIndex].getUserID() << "| "
                     << setw(8) << left << hotel[hotelIndex].review[reviewIndex].getRating() << "| "
                     << setw(23) << left << hotel[hotelIndex].getHotelName() << "| "
                     << hotel[hotelIndex].review[reviewIndex].getReview()
                     << endl;
                
                hotelRevNo++;
            }
        }
    }
    
    if(hotelRevNo){
        cout << endl
             << "There are " << hotelRevNo << " number of reviews for " << hotelName << "." << endl;
    }else{
        cout << endl
             << "There are no reviews for this Hotel, make sure your input is correct..." << endl;
    }
    cout << "=============================================================================================================" << endl;
}

void UniqueHotel::printUniqueHotel(const int& hotelIndex)const{
    cout << " " << setw(4) << left << (hotelIndex + 1) << " | "
         << fixed << setprecision(2) 
         << setw(30) << left << getHotelName() << " | "
         << setw(20) << left << numReview << " | "
         << setw(20) << left << averageRating << " | ";

    for(int stars = 0; stars < static_cast<int>(averageRating); stars++){
            cout << "*";
    }

    cout << endl;
}


//  operator overloading
bool UniqueHotel::operator>(const UniqueHotel& hotel)const{
    return ((this->averageRating) > hotel.averageRating);
}