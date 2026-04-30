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
enum readWrite {READ, WRITE};

//  setters (line 21 - 45) mainly used for traveler info managemen
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

//  setter (line 49 - 54) used for adding review
//  class method definition - Review class
void Review::setReview(string userID, int rating, string review, string hotelName){
    this->userID = userID;
    this->rating = rating;
    this->review = review;
    this->hotelName = hotelName;
}

//  class method definition - SystemApp class
void SystemApp::addReview(Traveler tra[]){
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
    }while(repeat);
}

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
                 << "=============================================================================================================";
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

//unfinished definition -start
void SystemApp::highestRatedHotel(){
    
}

void SystemApp::topReviewers(){
    
}

//  operator overloading
bool SystemApp::operator>(const Review& rev){}
//unfinished definition -end

//  friend global functions declaration
void printTravelerInfo(Traveler);

void printReview(Review);

bool readWriteUserFile(Traveler[], bool);

bool readWriteReviewFile(Review[], int, bool);


int main(){
    SystemApp app;
    return 0;
}


//  friend global function definition
void printTravelerInfo(Traveler tra){

}

void printReview(Review rev){

}

bool readWriteUserFile(Traveler tra[], bool rW){
    static int userCount;
    
    //rW = 0(READ) means perform file reading
    if(rW == 0){
        userCount = 0;
        cout << endl
             << "============= Collecting data from user.txt =============" << endl
             << endl;

        ifstream userInFile("users.txt");

        if(!userInFile){
            cout << endl
                 << "File open error..." << endl
                 << "Press \"ENTER\" to exit program..."
                 << endl;
        
            getchar();
            return false;
        }

        while(getline(userInFile, tra[userCount].userID, '\t')){
            
            getline(userInFile, tra[userCount].userName, '\t');
            getline(userInFile, tra[userCount].state, '\t');
            getline(userInFile, tra[userCount].email, '\t');
            getline(userInFile, tra[userCount].memberType, '\t');
            userInFile >> tra[userCount].point;
            
            userCount++;

            while(userInFile.peek() == '\n'){
                userInFile.ignore();
            }
        }

        userInFile.close();
        cout << "<--------------user.txt successfully read--------------->" << endl;
        return true;
    }

    //rW = 1(WRITE) means perform file writing
    if(rW == 1){
        cout << endl
             << "============= Rewriting data into user.txt ==============" << endl
             << endl;

        ofstream userOutFile("users.txt");

        for(int userNumber = 0; userNumber < userCount; userNumber++){
            userOutFile << tra[userNumber].userID << '\t'
                        << tra[userNumber].userName << '\t'
                        << tra[userNumber].state << '\t'
                        << tra[userNumber].email << '\t'
                        << tra[userNumber].memberType << '\t'
                        << tra[userNumber].point << '\n';
        }

        userOutFile.close();
        cout << "<------------ user.txt successfully updated ------------>" << endl;
        return true;
    }
}

bool readWriteReviewFile(Review rev[],  int additionalRevs, bool rW){
    static int revCount;
    
    //rW = 0(READ) means perform file reading
    if(rW == 0){
        revCount = 0;
        cout << endl
             << "============= Collecting data from user.txt =============" << endl
             << endl;

        ifstream revInFile("users.txt");

        if(!revInFile){
            cout << endl
                 << "File open error..." << endl
                 << "Press \"ENTER\" to exit program..."
                 << endl;
        
            getchar();
            return false;
        }

        while(getline(revInFile, rev[revCount].userID, '\t')){
            
            revInFile >> rev[revCount].rating;
            revInFile.ignore();

            getline(revInFile, rev[revCount].review, '\t');
            getline(revInFile, rev[revCount].hotelName, '\t');
            
            revCount++;

            while(revInFile.peek() == '\n'){
                revInFile.ignore();
            }
        }

        revInFile.close();
        cout << "<-------------review.txt successfully read-------------->" << endl;
        return true;
    }

    //rW = 1(WRITE) means perform file writing
    if(rW == 1){
        cout << endl
             << "============= Rewriting data into user.txt ==============" << endl
             << endl;

        ofstream revOutFile("users.txt");

        for(int revNumber = 0; revNumber < (revCount + additionalRevs); revNumber++){
            revOutFile << rev[revNumber].userID << '\t'
                        << rev[revNumber].rating << '\t'
                        << rev[revNumber].review << '\t'
                        << rev[revNumber].hotelName << '\n';
        }

        revOutFile.close();
        cout << "<----------- review.txt successfully updated ----------->" << endl;
        return true;
    }
}