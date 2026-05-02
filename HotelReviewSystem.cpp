#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>

#include "Person.h"
#include "Traveler.h"
#include "Review.h"
#include "UniqueHotel.h"
#include "SystemApp.h"

using namespace std;

//  Enumurators:
enum TravelerUpdateOpt {
    USER_NAME,
    STATE,
    EMAIL,
    MEMBER_TYPE,
    POINT,
    REVIEW,
    EXIT
};

enum UserOption {
    SHOW_DATA,
    SEARCH,
    TRAVELER_MANAGEMENT,
    ADD_REVIEWS,
    HIGHEST_RATED_HOTEL,
    TOP_REVIEWERS,
    EXIT_SYSTEM
};

//  operator overloading - Traveler class
bool Traveler::operator==(const Traveler& tra)const{
    return (this->getUserID() == tra.getUserID());
}

bool Traveler::operator<(const Traveler& tra)const{
    return (
        this->getReviewNumber() < tra.getReviewNumber()
        ||(
            this->getReviewNumber() == tra.getReviewNumber()
            &&
            this->getAverageRating() < tra.getAverageRating()
        )
    );
}

//  operator overloading - UniqueHotel class
UniqueHotel& UniqueHotel::operator=(const Review& rev){
    this->setUserID(rev.getUserID());
    this->setRating(rev.getRating());
    this->setReview(rev.getReview());
    this->setHotelName(rev.getHotelName());
    return *this;
}

bool UniqueHotel::operator>(const UniqueHotel& otherHotel)const{
    return ((this->getAverageRating()) > otherHotel.getAverageRating());
}

//  class methods - print function
void SystemApp::printTraveler()const{
    cout << endl
         << "TRAVELER INFORMATION: "<< endl
         << "=============================================================================================================" << endl
         << setw(8) << left << "User ID" << " | "
         << setw(20) << left << "User Name" << " | "
         << setw(18) << left << "State" << " | "
         << setw(25) << left << "Email" << " | "
         << setw(15) << left << "Membership" << " | "
         << "Points" << endl
         << "=============================================================================================================" << endl;

    for(int travelerIndex = 0; travelerIndex < TRAVELER_NUM; travelerIndex++){
        cout << setw(8) << left << traveler[travelerIndex].getUserID() << " | "
             << setw(20) << left << traveler[travelerIndex].getUserName() << " | "
             << setw(18) << left << traveler[travelerIndex].getState() << " | "
             << setw(25) << left << traveler[travelerIndex].getEmail() << " | "
             << setw(15) << left << traveler[travelerIndex].getMemberType() << " | "
             << traveler[travelerIndex].getPoint() << endl;
    }
    cout << "=============================================================================================================" << endl;
}

void SystemApp::printReview(const int& revNo)const{
    cout << endl
         << "REVIEW LIST: "<< endl
         << "=============================================================================================================" << endl
         << setw(10) << left << "User ID" << " | "
         << setw(10) << left << "Rating" << " | "
         << setw(25) << left << "Hotel" << " | "
         << "Review" << endl
         << "=============================================================================================================" << endl;

    for(int reviewIndex = 0; reviewIndex < revNo; reviewIndex++){
        cout << setw(10) << left << review[reviewIndex].getUserID() << " | "
             << setw(10) << left << review[reviewIndex].getRating() << " | "
             << setw(25) << left << review[reviewIndex].getHotelName() << " | "
             << review[reviewIndex].getReview() << endl;
    }
    cout << "=============================================================================================================" << endl;
}

void SystemApp::printUniqueHotel(const int& unique)const{
    cout << endl
         << "HOTEL RANKING BASED ON AVERAGE RATING: "<< endl
         << "=============================================================================================================" << endl
         << setw(5) << left << " Rank" << " | "
         << setw(30) << left << "Hotel" << " | "
         << setw(20) << left << "Number of Reviews" << " | "
         << setw(20) << left << "Average rating"  << " | "
         << "Stars" << endl
         << "=============================================================================================================" << endl;
    for(int hotelIndex = 0; hotelIndex < unique; hotelIndex++){
        cout << " " << setw(4) << left << (hotelIndex + 1) << " | "
             << fixed << setprecision(2) 
             << setw(30) << left << uniqueHotel[hotelIndex].getHotelName() << " | "
             << setw(20) << left << uniqueHotel[hotelIndex].getNumReview() << " | "
             << setw(20) << left << uniqueHotel[hotelIndex].getAverageRating() << " | ";
        for(int stars = 0; stars < uniqueHotel[hotelIndex].getAverageRating(); stars++){
            cout << "*";
        }
        cout << endl;
    }
    cout << "=============================================================================================================" << endl;
}

//  class method definition - SystemApp class
void SystemApp::updateUserAveRating(const int& revNo){
    //set or update total number of reviews and average rating from each users
    for(int travelerIndex = 0; travelerIndex < TRAVELER_NUM; travelerIndex++){
        int reviewNumber = 0;
        double totalRating = 0;

        for(int reviewIndex = 0; reviewIndex < revNo; reviewIndex++){
            if(traveler[travelerIndex].getUserID() == review[reviewIndex].getUserID()){
                reviewNumber++;
                totalRating += review[reviewIndex].getRating();
            }
        }
        traveler[travelerIndex].setReviewNumber(reviewNumber);
        if(reviewNumber){
            traveler[travelerIndex].setAverageRating(totalRating / reviewNumber);
        }else{
            traveler[travelerIndex].setAverageRating(0);
        }
    }
}

void SystemApp::hotelReview(){
    string hotelName = "";
    int hotelRevNo = 0;
    
    cout << endl
         << "Insert hotel name: (Input is case sensitive)"
         << endl;
    
    getline(cin, hotelName);

    for(int reviewIndex = 0; reviewIndex < REVIEW_NUM; reviewIndex++){
        if(reviewIndex == 0){
            cout << endl
                 << "HOTEL REVIEWS FOR : " << hotelName << endl
                 << "=============================================================================================================" << endl
                 << setw(10) << left << "User ID" << setw(10) << left << "| Rating" << setw(25) << left << "| Hotel" << "| Review" << endl
                 << "=============================================================================================================" << endl;
        }
        if(review[reviewIndex].getHotelName() == hotelName){
            cout << setw(10) << left << review[reviewIndex].getUserID() << "| "
                 << setw(8) << left << review[reviewIndex].getRating() << "| "
                 << setw(23) << left << review[reviewIndex].getHotelName() << "| "
                 << review[reviewIndex].getReview()
                 << endl;
            hotelRevNo++;
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

void SystemApp::travelerManagement(const int& revNo){
    string input;
    int numInput;
    
    TravelerUpdateOpt options;
    int travelerIndex = 0;
    bool updateInfo = false;

    cout << endl
         << "Enter user ID to configure the corresponding user information: "
         << endl;
    getline(cin, input);

    //searching for the user based on uid
    for(travelerIndex; travelerIndex < TRAVELER_NUM; travelerIndex++){
        if(traveler[travelerIndex].getUserID() == input){
            updateInfo = true;
            break;
        }
    }
    if(!updateInfo){
        cout << endl
             << "UserID not found..."
             << endl;
    }

    while(updateInfo){
        cout << endl
             << "============== Traveler information update ==============" << endl
             << "  1. USER NAME" << endl
             << "  2. STATE" << endl
             << "  3. EMAIL" << endl
             << "  4. MEMBER TYPE" << endl
             << "  5. POINTS" << endl
             << "  6. REVIEWS BY TRAVELER" << endl
             << "  7. EXIT SUBPAGE" << endl
             << "---------------------------------------------------------" << endl;
        cin >> numInput;
        cin.ignore();

        options = static_cast<TravelerUpdateOpt>(--numInput);

        switch(options){
            //update userName
            case USER_NAME:
                cout << endl
                     << "Please insert new user name or remain the current user name: (current user name: " << traveler[travelerIndex].getUserName() << ")"
                     << endl;
                getline(cin, input);
                traveler[travelerIndex].setUserName(input);
                break;

            //update state
            case STATE:
                cout << endl
                     << "Please insert new state or remain the current state: (current state: " << traveler[travelerIndex].getState() << ")"
                     << endl;
                getline(cin, input);
                traveler[travelerIndex].setState(input);
                break;

            //update email
            case EMAIL:
                cout << endl
                     << "Please insert new email or remain the current email: (current email: " << traveler[travelerIndex].getEmail() << ")"
                     << endl;
                getline(cin, input);
                traveler[travelerIndex].setEmail(input);
                break;

            //update memberType
            case MEMBER_TYPE:
                cout << endl
                     << "Please insert new member type or remain the current member type: (current member type: " << traveler[travelerIndex].getMemberType() << ")"
                     << endl;
                getline(cin, input);
                traveler[travelerIndex].setMemberType(input);
                break;

            //update point
            case POINT:
                cout << endl
                     << "Please insert new point or remain the current point: (current point: " << traveler[travelerIndex].getPoint() << ")"
                     << endl;
                cin >> numInput;
                cin.ignore();
                traveler[travelerIndex].setPoint(numInput);
                break;

            case REVIEW:
                cout << endl
                     << " Review Index  |  Review" << endl
                     << "-------------------------------------------------------------------------------------------------------------" << endl;
                for(int reviewIndex = 0; reviewIndex < revNo; reviewIndex++){
                    if(review[reviewIndex].getUserID() == traveler[travelerIndex].getUserID()){
                        cout << setw(8) << reviewIndex
                             << " | "
                             << review[reviewIndex].getReview()
                             << endl;
                    }
                }
                cout << "-------------------------------------------------------------------------------------------------------------" << endl;
                
                cout << "Please select the Review Index of the review you wish to amend: ";
                cin >> numInput;
                cin.ignore();

                cout << "Please insert your new review:" << endl;
                getline(cin, input);
                review[numInput].setReview(input);
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

void SystemApp::addReview(int& revNo){
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
            if(userID == traveler[userIndex].getUserID()){
                repeat = false;
                this->review[revNo].setUserID(userID);
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
    this->review[revNo].setHotelName(hotelName);
    
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
        }else{
            this->review[revNo].setRating(rating);
        }
    }while(rating < 1 || rating > 5);

    cout << endl
         << "------------------------------------------------------" << endl
         << " Insert your review for " << hotelName << endl
         << "------------------------------------------------------" << endl;

    getline(cin, review);
    this->review[revNo].setReview(review);
    
    revNo++;

    cout << endl
         << "<----------- New review successfully updated ----------->" << endl
         << endl;

    updateUserAveRating(revNo);
}

void SystemApp::sortHotel(const int& revNo, int& uniqueHotelNum){
    //  making a list of unique hotel
    for(int i = 0; i < revNo; i++){
        bool sameHotel = false;
        for(int j = 0; j < uniqueHotelNum; j++){
            if(uniqueHotel[j].getHotelName() == review[i].getHotelName()){
                sameHotel = true;
                break;
            }
        }
        if(!sameHotel){
            uniqueHotel[uniqueHotelNum] = review[i];
            uniqueHotelNum++;
        }
    }

    //  assigning averageRating for respective unique hotels
    for(int i = 0; i < uniqueHotelNum; i++){
        double rateSum = 0;
        int numHotel = 0;
        for(int j = 0; j < revNo; j++){
            if(uniqueHotel[i].getHotelName() == review[j].getHotelName()){
                rateSum += review[j].getRating();
                numHotel++;
            }
        }
        uniqueHotel[i].setNumReview(numHotel);

        if(numHotel){
            uniqueHotel[i].setAverageRating(rateSum/numHotel);
        }else{
            uniqueHotel[i].setAverageRating(0);
        }
    }

    //  sort uniqueHotel ONLY based on average rating
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

void SystemApp::topReviewers(){
    Traveler top1, top2, top3;
    
    //finding user who has the most reviews, then the highest average rating
    for(int travelerIndex = 0; travelerIndex < TRAVELER_NUM; travelerIndex++){
        if(top1 == traveler[travelerIndex] || top2 == traveler[travelerIndex] || top3 == traveler[travelerIndex]){
            continue;
        }
        
        if(top1 < traveler[travelerIndex]){
            top3 = top2;
            top2 = top1;
            top1 = traveler[travelerIndex];

        }else if(top2 < traveler[travelerIndex]){
            top3 = top2;
            top2 = traveler[travelerIndex];

        }else if(top3 < traveler[travelerIndex]){
            top3 = traveler[travelerIndex];
        }
    }
    cout << endl
         << "TOP 3 REVIEWER LEADERBOARD:" << endl
         << "=============================================================================================================" << endl
         << setw(4) << left << " No" << " | "
         << setw(15) << left << "User Name" << " | "
         << setw(10) << left << "User ID" << " | "
         << setw(20) << left << "Number of Reviews" << " | "
         << "Average Rating" << endl
         << "=============================================================================================================" << endl;
         
    cout << setw(4) << left << " 1" << " | " 
         << setw(15) << left << top1.getUserName() << " | "
         << setw(10) << left << top1.getUserID() << " | "
         << setw(20) << left << top1.getReviewNumber() << " | "
         << fixed << setprecision(2) 
         << top1.getAverageRating()
         << endl;
         
    cout << setw(4) << left << " 2" << " | "
         << setw(15) << left << top2.getUserName() << " | "
         << setw(10) << left << top2.getUserID() << " | "
         << setw(20) << left << top2.getReviewNumber() << " | "
         << fixed << setprecision(2) 
         << top2.getAverageRating()
         << endl;

    cout << setw(4) << left << " 3" << " | "
         << setw(15) << left << top3.getUserName() << " | "
         << setw(10) << left << top3.getUserID() << " | "
         << setw(20) << left << top3.getReviewNumber() << " | "
         << fixed << setprecision(2) 
         << top3.getAverageRating()
         << endl;
    
    cout << "=============================================================================================================" << endl;
}

//  constructors - SystemApp class
SystemApp::SystemApp(int& revNo){
    int userCount = 0;
    cout << endl
            << "============ Collecting data from text files ============" << endl
            << endl;

    ifstream userInFile("users.txt");
    ifstream revInFile("reviews.txt");

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
            while(userInFile.peek() == '\n'){
                userInFile.ignore();
            }

            traveler[userCount].setPoint(numInput);

            userCount++;
    
        }

        string uid, rev, hotel;
        int rate;
        while(getline(revInFile, uid, '\t')){

            revInFile >> rate;
            revInFile.ignore();

            getline(revInFile, rev, '\t');
            
            getline(revInFile, hotel, '\n');

            review[revNo].setUserID(uid);
            review[revNo].setRating(rate);
            review[revNo].setReview(rev);
            review[revNo].setHotelName(hotel);
            revNo++;

            while(revInFile.peek() == '\n'){
                revInFile.ignore();
            }
        }
    
        userInFile.close();
        revInFile.close();

        printTraveler();
        printReview(revNo);

        cout << "<-------------text files successfully read-------------->" << endl
             << endl;

        updateUserAveRating(revNo);
    }
}

//  friend global functions declaration
void writeUserFile(Traveler[]);

void writeReviewFile(Review[], int&);

//  normal global function declaration
void printMainMenu();

void userSelection(SystemApp&, int&, int&);

int main(){
    int reviewNumber = 0;
    int uniqueHotelNum = 0;
    SystemApp app(reviewNumber);
    app.sortHotel(reviewNumber, uniqueHotelNum);        //initialise and sort unique hotel list

    userSelection(app, reviewNumber, uniqueHotelNum);

    writeUserFile(app.getTraveler());
    writeReviewFile(app.getReview(), reviewNumber);

    cout << "Please press ENTER to exit system...";
    getchar();

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

    ofstream revOutFile("reviews.txt");

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

//  normal global function definition
void printMainMenu(){
    cout << endl
         << "======================= MAIN MENU =======================" << endl
         << "  1. SHOWING DATA" << endl
         << "  2. SEARCH HOTEL REVIEW" << endl
         << "  3. TRAVELER MANAGEMENT" << endl
         << "  4. SUBMITTING NEW REVIEWS" << endl
         << "  5. HOTEL RANKING" << endl
         << "  6. TOP REVIEWERS" << endl
         << "  7. EXIT AND UPDATE TEXT FILES" << endl
         << "---------------------------------------------------------" << endl
         << "Your Input: ";
}

void userSelection(SystemApp& app, int& revNo, int& unique){
    UserOption option;
    int input = 0;

    while(option != EXIT_SYSTEM){
        printMainMenu();
        cin >> input; cin.ignore();

        option = static_cast<UserOption>(--input);

        switch(option){
            case SHOW_DATA:
                //print user and review file
                app.printTraveler();
                app.printReview(revNo);
                cout << endl << endl << endl;
                break;

            case SEARCH:
                app.hotelReview();
                cout << endl << endl << endl;
                break;

            case TRAVELER_MANAGEMENT:
                app.travelerManagement(revNo);
                cout << endl << endl << endl;
                break;

            case ADD_REVIEWS:
                app.addReview(revNo);
                cout << endl << endl << endl;
                break;

            case HIGHEST_RATED_HOTEL:
                //checking if a new hotel is added
                app.sortHotel(revNo, unique);
                //printing
                app.printUniqueHotel(unique);
                cout << endl << endl << endl;
                break;

            case TOP_REVIEWERS:
                app.topReviewers();
                cout << endl << endl << endl;
                break;

            case EXIT_SYSTEM:
                cout << endl
                     << "Thank you for using the Hotel Review System" << endl
                     << endl;
                break;

            default:
                cout << endl
                     << "Input error, try again..."
                     << endl;
                cout << endl << endl << endl;
        }

    }
}