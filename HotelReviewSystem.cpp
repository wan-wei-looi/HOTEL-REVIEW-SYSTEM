#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>

#include "Person.hpp"
#include "Traveler.hpp"
#include "Review.hpp"
#include "UniqueHotel.hpp"
#include "SystemApp.hpp"

using namespace std;

//  Enumurators:
enum travelerUpdateOpt {USER_NAME, STATE, EMAIL, MEMBER_TYPE, POINT, EXIT};

//  setters (line 18 - 41) mainly used for traveler info managemen
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

//  setter (line 45 - 50) used for adding review
//  class method definition - Review class
void Review::setReview(string userID, int rating, string review, string hotelName){
    this->userID = userID;
    this->rating = rating;
    this->review = review;
    this->hotelName = hotelName;
}

//  class method definition - UniqueHotel Class
void UniqueHotel::setAverageRating(double ave){
    averageRating = ave;
}

//  operator overloading - UniqueHotel class
UniqueHotel& UniqueHotel::operator=(const Review& rev){
    this->setReview(
        rev.getUserID(),
        rev.getRating(),
        rev.getReview(),
        rev.getHotelName()
    );
    return *this;
}

//  class method definition - SystemApp class
void SystemApp::addReview(Traveler tra[], int& revNo){
    bool repeat = true;
    string userID;
    int rating;
    string review;
    string hotelName;

    cout << endl
         << "REVIEW SUBMISSION:" << endl
         << "======================================================" << endl
         << "Enter the necessary information as prompted." << endl;
    do{
        cout << endl
             << "------------------------------------------------------" << endl
             << " Insert User ID [User ID must be registered]" << endl
             << "------------------------------------------------------" << endl;

        getline(cin, userID);

        for(int userIndex = 0; userIndex < TRAVELER_NUM; userIndex++){
            if(userID == tra[userIndex].getUserID()){
                repeat = false;
            }
        }
        if(repeat){
            cout << endl
                 << "Please try again, " << userID << " is not a valid user ID..." << endl
                 << endl;
        }
    }while(repeat);

    cout << endl
         << "------------------------------------------------------" << endl
         << " Insert hotel name" << endl
         << " ! System is case sensitive" <<endl 
         << " ! Different capitalisation refers to different hotel" << endl
         << "------------------------------------------------------" << endl;

    getline(cin, hotelName);
    
    do{
        cout << endl
             << "------------------------------------------------------" << endl
             << " Insert Rating (1 to 5)" << endl
             << "------------------------------------------------------" << endl;
    
        cin >> rating;
        cin.ignore();

        if(rating < 1 || rating > 5){
            cout << endl
                 << "Please try again, rating must be between 1 and 5 (inclusive)" << endl
                 << endl;
        }
    }while(rating < 1 || rating > 5);

    cout << endl
         << "------------------------------------------------------" << endl
         << " Insert your review for" << hotelName << endl
         << "------------------------------------------------------" << endl;

    getline(cin, review);

    this->review[revNo].setReview(userID, rating, review, hotelName);
    revNo++;

    cout << "<----------- New review successfully updated ----------->" << endl
         << endl;
}

void SystemApp::hotelReview(){
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
                 << "=============================================================================================================";
        }
        if(review[reviewIndex].getHotelName() == hotelName){
            //print(placeholder)
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

//unfinished definition -start
void SystemApp::highestRatedHotel(const int& revNo){
    //UniqueHotel temp;
    int uniqueHotelNum = 0;
    
    //  making a list of unique hotel
    for(int i = 0; i < revNo; i++){
        bool sameHotel = false;
        for(int j = 0; j < uniqueHotelNum; j++){
            if(uniqueHotel[j].getHotelName() == review[i].getHotelName()){
                sameHotel = true;
                break;
            }
            if(!sameHotel){
                uniqueHotel[uniqueHotelNum] = review[i];
            }
        }
    }

    //  assigning averageRating for respective unique hotels
    for(int i = 0; i < uniqueHotelNum; i++){
        double rateSum = 0;
        int numHotel = 0;
        for(int j = 0; i < revNo; j++){
            if(uniqueHotel[i].getHotelName() == review[i].getHotelName()){
                rateSum += review[i].getRating();
                numHotel++;
            }
        }


    }
}

void SystemApp::topReviewers(){
    
}

//  operator overloading
bool SystemApp::operator==(const Review& rev)const{

}
//unfinished definition -end

//  constructors - SystemApp class
SystemApp::SystemApp(int& revNo){
    int userCount = 0;
    cout << endl
            << "============ Collecting data from text files ============" << endl
            << endl;

    ifstream userInFile("users.txt");
    ifstream revInFile("review.txt");

    if(!userInFile || !revInFile){
        cout << endl
                << "File open error..." << endl
                << "Press \"ENTER\" to exit program..."
                << endl;
        getchar();
    }else{

        string input;
        int numInput;

        while(getline(userInFile, input, '\t')){
            traveler[userCount].setUserID(input);

            getline(userInFile, input, '\t');
            traveler[userCount].setUserName(input);

            getline(userInFile, input, '\t');
            traveler[userCount].setState(input);
            
            getline(userInFile, input, '\t');
            traveler[userCount].setEmail(input);

            getline(userInFile, input, '\t');
            traveler[userCount].setMemberType(input);
            
            userInFile >> numInput;
            traveler[userCount].setPoint(numInput);

            userCount++;
    
            while(userInFile.peek() == '\n'){
                userInFile.ignore();
            }
        }

        string uid, rev, hotel;
        int rate;
        while(getline(revInFile, uid, '\t')){

            revInFile >> rate;
            revInFile.ignore();

            getline(revInFile, rev, '\t');
            
            getline(revInFile, hotel, '\t');

            review[revNo].setReview(uid, rate, rev,hotel);
            
            revNo++;

            while(revInFile.peek() == '\n'){
                revInFile.ignore();
            }
        }
    
        userInFile.close();
        revInFile.close();
        cout << "<-------------text files successfully read-------------->" << endl
             << endl;
    }

}

//  friend global functions declaration
void writeUserFile(Traveler[]);

void writeReviewFile(Review[], int&);


int main(){
    int reviewNumber = 0;
    SystemApp app(reviewNumber);

    return 0;
}


//  friend global function definition
void writeUserFile(Traveler tra[]){
    cout << endl
         << "============= Rewriting data into user.txt ==============" << endl
         << "..." << endl
         << endl;

    ofstream userOutFile("users.txt");

    for(int userNumber = 0; userNumber < TRAVELER_NUM; userNumber++){
        userOutFile << tra[userNumber].userID << '\t'
                    << tra[userNumber].userName << '\t'
                    << tra[userNumber].state << '\t'
                    << tra[userNumber].email << '\t'
                    << tra[userNumber].memberType << '\t'
                    << tra[userNumber].point << '\n';
    }

    userOutFile.close();
    cout << "<------------ user.txt successfully updated ------------>" << endl
         << endl;
}

void writeReviewFile(Review rev[],  int& revNo){
    cout << endl
         << "============= Rewriting data into user.txt ==============" << endl
         << "..." << endl
         << endl;

    ofstream revOutFile("users.txt");

    for(int revNumber = 0; revNumber < revNo; revNumber++){
        revOutFile << rev[revNumber].userID << '\t'
                   << rev[revNumber].rating << '\t'
                   << rev[revNumber].review << '\t'
                   << rev[revNumber].hotelName << '\n';
    }

    revOutFile.close();
    cout << "<----------- review.txt successfully updated ----------->" << endl
         << endl;
}
