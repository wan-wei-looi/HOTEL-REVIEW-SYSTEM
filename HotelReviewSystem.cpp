#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>

#include "Person.h"
#include "Traveler.h"
#include "Review.h"
#include "UniqueHotel.h"

using namespace std;

//  Global constants
const int TRAVELER_NUM = 10;
const int REVIEW_NUM = 50;

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

//  print function prototype
void printMainMenu();

void printTravelerHeader();

void printReviewHeader();

void printUniqueHotelHeader();

void printTableFooter();



//  class setters
void Traveler::setReviewNumber(const int& revNo, const Review review[]){
    int reviewNumber = 0;

    for(int reviewIndex = 0; reviewIndex < revNo; reviewIndex++){
        if(getUserID() == review[reviewIndex].getUserID()){
            reviewNumber++;
        }
    }
    this->reviewNumber = reviewNumber;
}

void Traveler::setAverageRating(const int& revNo, const Review review[]){
    double totalRating = 0;

    for(int reviewIndex = 0; reviewIndex < revNo; reviewIndex++){
        if(getUserID() == review[reviewIndex].getUserID()){
            totalRating += review[reviewIndex].getRating();
        }
    }

    if(totalRating){
        this->averageRating = totalRating / reviewNumber;
    }else{
        this->averageRating = totalRating;
    }
}

void UniqueHotel::assignUniqueHotel(const int& revNo, int& uniqueHotelNum, const Review review[], UniqueHotel uniqueHotel[]){
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
    //assigning number of reviews and average rating for each hotel
    for(int i = 0; i < uniqueHotelNum; i++){
        double rateSum = 0;
        int numHotel = 0;
        for(int j = 0; j < revNo; j++){
            if(uniqueHotel[i].getHotelName() == review[j].getHotelName()){
                rateSum += review[j].getRating();
                numHotel++;
            }
        }
        uniqueHotel[i].numReview = numHotel;

        if(numHotel){
            uniqueHotel[i].averageRating = rateSum / numHotel;
        }else{
            uniqueHotel[i].averageRating = 0;
        }
    }
}


//  sorting unique hotels based on average rating
void UniqueHotel::sortHotel(const int& uniqueHotelNum, UniqueHotel uniqueHotel[]){
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



//  class methods - print function
void Traveler::printTraveler()const{
    cout << setw(8) << left << userID << " | "
         << setw(20) << left << userName << " | "
         << setw(18) << left << state << " | "
         << setw(25) << left << email << " | "
         << setw(15) << left << memberType << " | "
         << point << endl;
}

void Review::printReview()const{
    cout << setw(8) << left << getUserID() << " | "
         << setw(10) << left << getRating() << " | "
         << setw(25) << left << getHotelName() << " | "
         << getReview() << endl;
}

void UniqueHotel::printUniqueHotel(const int& hotelIndex)const{
    cout << " " << setw(4) << left << (hotelIndex + 1) << " | "
             << fixed << setprecision(2) 
             << setw(30) << left << getHotelName() << " | "
             << setw(20) << left << getNumReview() << " | "
             << setw(20) << left << getAverageRating() << " | ";
        for(int stars = 0; stars < getAverageRating(); stars++){
            cout << "*";
        }
        cout << endl;
}


//  file reading
void Traveler::readTravelerInfo(fstream& userFile){
    int numInput;
    string input;

    getline(userFile, input, '\t');
    setUserID(input);

    getline(userFile, input, '\t');
    setUserName(input);

    getline(userFile, input, '\t');
    setState(input);
    
    getline(userFile, input, '\t');
    setEmail(input);

    getline(userFile, input, '\t');
    setMemberType(input);
    
    userFile >> numInput;
    setPoint(numInput);

    while(userFile.peek() == '\n'){
        userFile.ignore();
    }
}

void Review::readReviewList(fstream& revFile){
    string input;
    int numInput;

    getline(revFile, input, '\t');
    setUserID(input);

    revFile >> numInput;
    revFile.ignore();
    setRating(numInput);

    getline(revFile, input, '\t');
    setReview(input);
    
    getline(revFile, input, '\n');
    setHotelName(input);

    while(revFile.peek() == '\n'){
        revFile.ignore();
    }
}



void Review::searchReview(Review review[]){
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
                 << setw(8) << left << "User ID" << setw(10) << left << "| Rating" << setw(25) << left << "| Hotel" << "| Review" << endl
                 << "=============================================================================================================" << endl;
        }
        if(review[reviewIndex].getHotelName() == hotelName){
            cout << setw(8) << left << review[reviewIndex].getUserID() << "| "
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

void Traveler::travelerManagement(const int& userCount, const int& revNo, Traveler traveler[], Review review[]){
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
    for(travelerIndex; travelerIndex < userCount; travelerIndex++){
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

void Review::addReview(int& revNo, const string UID[], Review review[]){
    bool repeat = true;
    string input;
    int numInput;

    cout << endl
         << "REVIEW SUBMISSION:" << endl
         << "======================================================" << endl
         << "Enter the necessary information as prompted." << endl;
    do{
        cout << endl
             << "------------------------------------------------------" << endl
             << " Insert User ID [User ID must be registered]" << endl
             << "------------------------------------------------------" << endl;

        getline(cin, input);

        for(int userIndex = 0; userIndex < TRAVELER_NUM; userIndex++){
            if(input == UID[userIndex]){
                repeat = false;
                review[revNo].setUserID(input);
            }
        }
        if(repeat){
            cout << endl
                 << "Please try again, " << input << " is not a valid user ID..." << endl
                 << endl;
        }
    }while(repeat);

    cout << endl
         << "------------------------------------------------------" << endl
         << " Insert hotel name" << endl
         << " ! System is case sensitive" <<endl 
         << " ! Different capitalisation refers to different hotel" << endl
         << "------------------------------------------------------" << endl;

    getline(cin, input);
    review[revNo].setHotelName(input);
    
    do{
        cout << endl
             << "------------------------------------------------------" << endl
             << " Insert Rating (1 to 5)" << endl
             << "------------------------------------------------------" << endl;
    
        cin >> numInput;
        cin.ignore();

        if(numInput < 1 || numInput > 5){
            cout << endl
                 << "Please try again, rating must be between 1 and 5 (inclusive)" << endl
                 << endl;
        }else{
            review[revNo].setRating(numInput);
        }
    }while(numInput < 1 || numInput > 5);

    cout << endl
         << "------------------------------------------------------" << endl
         << " Insert your review for " << input << endl
         << "------------------------------------------------------" << endl;

    getline(cin, input);
    review[revNo].setReview(input);
    
    revNo++;

    cout << endl
         << "<----------- New review successfully updated ----------->" << endl
         << endl;
}

//add into traveler class
void Traveler::topReviewers(const int& userCount, Traveler traveler[]){
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
         << setw(15) << left << top1.userName << " | "
         << setw(10) << left << top1.userID << " | "
         << setw(20) << left << top1.reviewNumber << " | "
         << fixed << setprecision(2) 
         << top1.averageRating
         << endl;
         
    cout << setw(4) << left << " 2" << " | "
         << setw(15) << left << top2.userName << " | "
         << setw(10) << left << top2.userID << " | "
         << setw(20) << left << top2.reviewNumber << " | "
         << fixed << setprecision(2) 
         << top2.averageRating
         << endl;

    cout << setw(4) << left << " 3" << " | "
         << setw(15) << left << top3.userName << " | "
         << setw(10) << left << top3.userID << " | "
         << setw(20) << left << top3.reviewNumber << " | "
         << fixed << setprecision(2) 
         << top3.averageRating
         << endl;
    
    cout << "=============================================================================================================" << endl;
}

//  friend global functions declaration
void writeUserFile(Traveler[], const int&, fstream&);

void writeReviewFile(Review[], const int&, fstream&);

//  normal global function declaration
UserOption userSelection();

int main(){

    fstream userFile("users.txt", ios::in | ios::out);
    fstream revFile("reviews.txt", ios::in | ios::out);

    cout << "============ Collecting data from text files ============" << endl
         << endl;

    if(!userFile || !revFile){
        cout << endl
             << "File open error..." << endl
             << "Press \"ENTER\" to exit program..."
             << endl;
        getchar();
    }

    int userCount = 0;
    int reviewNumber = 0;
    int uniqueHotelNum = 0;
    
    Traveler traveler[TRAVELER_NUM];
    while(!userFile.eof()){
        traveler[userCount++].readTravelerInfo(userFile);
    }

    Review review[REVIEW_NUM];
    while(!revFile.eof()){
        review[reviewNumber++].readReviewList(revFile);
    }

    //  assigning number of reviews and average rating of each users
    for(int travelerIndex = 0; travelerIndex < userCount; travelerIndex++){
        traveler[travelerIndex].setReviewNumber(reviewNumber, review);
        traveler[travelerIndex].setAverageRating(reviewNumber, review);
    }

    //  print out user and review for confirmation
    printTravelerHeader();
    for(int travelerIndex = 0; travelerIndex < userCount; travelerIndex++){
        traveler[travelerIndex].printTraveler();
    }
    printTableFooter();

    printReviewHeader();
    for(int reviewIndex = 0; reviewIndex < reviewNumber; reviewIndex++){
        review[reviewIndex].printReview();
    }
    printTableFooter();
    

    cout << "<-------------text files successfully read-------------->" << endl
         << endl;
    cout << endl << endl << endl;

    UniqueHotel uniqueHotel[REVIEW_NUM];
    UniqueHotel::assignUniqueHotel(reviewNumber, uniqueHotelNum, review, uniqueHotel);

    //  an array of user ID initialised
    string UID[userCount];
    for(int userIndex = 0; userIndex < userCount; userIndex++){
        UID[userIndex] = traveler[userIndex].getUserID();
    }

    UserOption option;
    while(option != EXIT_SYSTEM){
        option = userSelection();
        switch(option){
            case SHOW_DATA:
                printTravelerHeader();
                for(int travelerIndex = 0; travelerIndex < userCount; travelerIndex++){
                    traveler[travelerIndex].printTraveler();
                }
                printTableFooter();

                printReviewHeader();
                for(int reviewIndex = 0; reviewIndex < reviewNumber; reviewIndex++){
                    review[reviewIndex].printReview();
                }
                printTableFooter();
                
                cout << endl << endl << endl;
                break;

            case SEARCH:
                Review::searchReview(review);
                cout << endl << endl << endl;
                break;

            case TRAVELER_MANAGEMENT:
                Traveler::travelerManagement(userCount, reviewNumber, traveler, review);
                cout << endl << endl << endl;
                break;

            case ADD_REVIEWS:
                Review::addReview(reviewNumber, UID, review);
                cout << endl << endl << endl;

                // update traveler reviewNumber and averageRating
                for(int travelerIndex = 0; travelerIndex < userCount; travelerIndex++){
                    traveler[travelerIndex].setReviewNumber(reviewNumber, review);
                    traveler[travelerIndex].setAverageRating(reviewNumber, review);
                }
                break;

            case HIGHEST_RATED_HOTEL:
                UniqueHotel::sortHotel(uniqueHotelNum, uniqueHotel);

                printUniqueHotelHeader();
                for(int hotelIndex = 0; hotelIndex < uniqueHotelNum; hotelIndex++){
                    uniqueHotel[hotelIndex].printUniqueHotel(hotelIndex);
                }
                printTableFooter();

                cout << endl << endl << endl;
                break;

            case TOP_REVIEWERS:
                Traveler::topReviewers(userCount, traveler);
                cout << endl << endl << endl;
                break;

            case EXIT_SYSTEM:
                writeUserFile(traveler, userCount, userFile);
                writeReviewFile(review, reviewNumber, revFile);
                break;
                
                default:
                cout << endl
                << "Input error, try again..."
                << endl;
                cout << endl << endl << endl;
            }
        }
        
    cout << endl
         << "Thank you for using the Hotel Review System..." << endl;
    cout << "Please press ENTER to exit system...";
    getchar();

    return 0;
}

//  print functions definition
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

void printTravelerHeader(){
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
}

void printReviewHeader(){
    cout << endl
         << "REVIEW LIST: "<< endl
         << "=============================================================================================================" << endl
         << setw(8) << left << "User ID" << " | "
         << setw(10) << left << "Rating" << " | "
         << setw(25) << left << "Hotel" << " | "
         << "Review" << endl
         << "=============================================================================================================" << endl;

}

void printUniqueHotelHeader(){
    cout << endl
         << "HOTEL RANKING BASED ON AVERAGE RATING: "<< endl
         << "=============================================================================================================" << endl
         << setw(5) << left << " Rank" << " | "
         << setw(30) << left << "Hotel" << " | "
         << setw(20) << left << "Number of Reviews" << " | "
         << setw(20) << left << "Average rating"  << " | "
         << "Stars" << endl
         << "=============================================================================================================" << endl;
}

void printTableFooter(){
    cout << "=============================================================================================================" << endl
         << endl;
}



//  friend global function definition
void writeUserFile(Traveler tra[], const int& userCount, fstream& userFile){
    cout << endl
         << "============= Rewriting data into user.txt ==============" << endl
         << "..." << endl
         << endl;

    userFile.clear();
    userFile.seekg(0, ios::beg);

    for(int userNumber = 0; userNumber < userCount; userNumber++){
        userFile << tra[userNumber].userID << '\t'
                 << tra[userNumber].userName << '\t'
                 << tra[userNumber].state << '\t'
                 << tra[userNumber].email << '\t'
                 << tra[userNumber].memberType << '\t'
                 << tra[userNumber].point << '\n';
    }

    userFile.close();

    cout << "<------------ user.txt successfully updated ------------>" << endl
         << endl;
}

void writeReviewFile(Review rev[],  const int& revNo, fstream& revFile){
    cout << endl
         << "============= Rewriting data into user.txt ==============" << endl
         << "..." << endl
         << endl;
    
    revFile.clear();
    revFile.seekg(0, ios::beg);

    for(int revNumber = 0; revNumber < revNo; revNumber++){
        revFile << rev[revNumber].userID << '\t'
                << rev[revNumber].rating << '\t'
                << rev[revNumber].review << '\t'
                << rev[revNumber].hotelName << '\n';
    }

    revFile.close();

    cout << "<----------- review.txt successfully updated ----------->" << endl
         << endl;
}



//  user selection function definition
UserOption userSelection(){
    UserOption option;
    int input = 0;

    printMainMenu();
    
    cin >> input; cin.ignore();
    option = static_cast<UserOption>(--input);
    
    return option;
}