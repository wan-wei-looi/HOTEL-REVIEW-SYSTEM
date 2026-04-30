#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>

#include "Person.hpp"
#include "Traveler.hpp"
#include "Review.hpp"
#include "SystemApp.hpp"

using namespace std;
//  Global constant:
const int TRAVELER_NUM = 10;
const int REVIEW_NUM = 50;

//  Enumurators:
enum travelerUpdateOpt {USER_NAME, STATE, EMAIL, MEMBER_TYPE, POINT, EXIT};

//  class method definition - Person class
void Person::setUserID(string userID){
    this->userID = userID;
}

void Person::setUserName(string userName){
    this->userName = userName;
}

void Person::setState(string state){
    this->state = state;
}

void Person::setEmail(string email){
    this->email = email;
}

//class method definition - Traveler class
void Traveler::setMemberType(string memberType){
    this->memberType = memberType;
}

void Traveler::setPoint(int point){
    this->point = point;
}

//  class method definition - Review class
void Review::setReview(string userID, int rating, string review, string hotelName){
    this->userID = userID;
    this->rating = rating;
    this->review = review;
    this->hotelName = hotelName;
}

void Review::addReview(){
    
}

//  class method definition - SystemApp class
void SystemApp::hotelSummary(){
    string hotelName = "";
    int revNo = 0;
    
    cout << endl
         << "Insert hotel name: (Input is case sensitive)"
         << endl;
    
    getline(cin, hotelName);

    for(int reviewIndex = 0; reviewIndex < REVIEW_NUM; reviewIndex++){
        if(reviewIndex == 0){
            cout << endl
                 << "=============================================================================================================" << endl
                 << setw(8) << left << "User ID" << setw(8) << left << "Rating" << setw(30) << left << "Hotel" << "Review" << endl
                 << "=============================================================================================================" << endl;
        }
        if(review[reviewIndex].getHotelName() == hotelName){
            printReview(review[reviewIndex]);
            revNo++;
        }
    }

    if(revNo){
        cout << endl
             << "There are " << revNo << " number of reviews for " << hotelName << "."
             << endl;
    }else{
        cout << endl
             << "There are no reviews for this Hotel, make sure your input is correct..."
             << endl;
    }
}

void SystemApp::travelerManagement(){
    string uid, input;
    int newPoint;

    travelerUpdateOpt options;
    int temp;
    int travelerIndex = 0;
    bool updateInfo = true;

    cout << endl
         << "Enter user ID to configure the corresponding user information: "
         << endl;
    
    getline(cin, uid);

    //searching for the user based on uid
    for(travelerIndex; travelerIndex < TRAVELER_NUM; travelerIndex++){
        if(traveler[travelerIndex].getUserID() == uid){
            break;
        }
    }
    while(updateInfo){
        cout << endl
             << "============================0============================" << endl
             << "              Traveler information update" << endl
             << "============================0============================" << endl
             << "  1. USER NAME" << endl
             << "  2. STATE" << endl
             << "  3. EMAIL" << endl
             << "  4. MEMBER TYPE" << endl
             << "  5. POINTS" << endl
             << "  6. EXIT SUBPAGE" << endl
             << "---------------------------------------------------------" << endl
             << endl;

        cin >> temp;

        options = static_cast<travelerUpdateOpt>(--temp);

        switch(options){
            //update userName
            case USER_NAME:
                cout << endl
                     << "Please insert new user name or remain the current user name: (current user name: " << traveler[travelerIndex].getUserName() << " )"
                     << endl;

                getline(cin, input);
                break;

            //update state
            case STATE:
                cout << endl
                     << "Please insert new state or remain the current state: (current state: " << traveler[travelerIndex].getState() << " )"
                     << endl;

                getline(cin, input);
                break;

            //update email
            case EMAIL:
                cout << endl
                     << "Please insert new email or remain the current email: (current email: " << traveler[travelerIndex].getEmail() << " )"
                     << endl;

                getline(cin, input);
                break;

            //update memberType
            case MEMBER_TYPE:
                cout << endl
                     << "Please insert new member type or remain the current member type: (current member type: " << traveler[travelerIndex].getMemberType() << " )"
                     << endl;

                getline(cin, input);
                break;

            //update point
            case POINT:
                cout << endl
                     << "Please insert new point or remain the current point: (current email: " << traveler[travelerIndex].getEmail() << " )"
                     << endl;

                getline(cin, input);
                break;

            case EXIT:
                updateInfo = false;
                break;

            default:
                cout << endl
                     << "Invalid input..."
                     << endl;
        }
    }
}

void SystemApp::highestRatedHotel(){
    
}

void SystemApp::topReviewers(){
    
}

//  operator overloading
Traveler SystemApp::operator+(int newPoint){}

//  friend global functions declaration
void printTravelerInfo(Traveler);

void printReview(Review);

int main(){
    SystemApp app;
    return 0;
}

void printTravelerInfo(Traveler tra){

}

void printReview(Review rev){

}