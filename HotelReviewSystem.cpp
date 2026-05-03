#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>

//header files
#include "Person.h"
#include "Traveler.h"
#include "Review.h"
#include "UniqueHotel.h"

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



//  operator overloading
//  Traveler class
bool Traveler::operator==(const Traveler& tra)const{
    return (this->userID == tra.userID);
}

bool Traveler::operator<(const Traveler& tra)const{
    return (
        this->reviewNumber < tra.reviewNumber
        ||(
            this->reviewNumber == tra.reviewNumber
            &&
            this->averageRating < tra.averageRating
        )
    );
}

//  UniqueHotel class
UniqueHotel& UniqueHotel::operator=(const Review& rev){
    this->userID = rev.getUserID();
    this->rating = rev.getRating();
    this->review = rev.getReview();
    this->hotelName = rev.getHotelName();
    return *this;
}

bool UniqueHotel::operator>(const UniqueHotel& hotel)const{
    return ((this->averageRating) > hotel.averageRating);
}



//  print function prototype
void printMainMenu();

void printTravelerHeader();

void printReviewHeader();

void printUniqueHotelHeader();

void printTableFooter();



//  updates the review, number of reviews and average rating of traveler
void Traveler::assignTravelerReviewInfo(Review rev[], const int& revNo){

    reviewNumber = 0;
    double totalRating = 0;

    for(int reviewIndex = 0; reviewIndex < revNo; reviewIndex++){
        if(userID == rev[reviewIndex].getUserID()){
            review[reviewNumber] = rev[reviewIndex];
            reviewNumber++;

            totalRating += rev[reviewIndex].getRating();
        }
    }

    if(reviewNumber){
        averageRating = totalRating / reviewNumber;
    }else{
        averageRating = reviewNumber;
    }
}



//  assigning number of reviews and average rating for each hotel
void UniqueHotel::assignUniqueHotels( const Review rev[], UniqueHotel uniqueHotel[], const int& revNo, int& uniqueHotelNum){
    
    // removing duplicates
    for(int reviewIndex = 0; reviewIndex < revNo; reviewIndex++){
        bool sameHotel = false;

        for(int hotelIntex = 0; hotelIntex < uniqueHotelNum; hotelIntex++){
            if(uniqueHotel[hotelIntex].hotelName == rev[reviewIndex].getHotelName()){
                sameHotel = true;
                break;
            }
        }

        if(!sameHotel){
            uniqueHotel[uniqueHotelNum] = rev[reviewIndex];
            uniqueHotelNum++;
        }
    }

    // updating number of reviews and average rating for each hotel
    for(int hotelIndex = 0; hotelIndex < uniqueHotelNum; hotelIndex++){
        double rateSum = 0;
        int numHotel = 0;

        for(int reviewIndex = 0; reviewIndex < revNo; reviewIndex++){
            if(uniqueHotel[hotelIndex].hotelName == rev[reviewIndex].getHotelName()){
                rateSum += rev[reviewIndex].getRating();
                numHotel++;
            }
        }

        uniqueHotel[hotelIndex].numReview = numHotel;

        if(numHotel){
            uniqueHotel[hotelIndex].averageRating = rateSum / numHotel;
        }else{
            uniqueHotel[hotelIndex].averageRating = 0;
        }
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



//  class methods 
//  print function
void Review::printReview()const{
    cout << setw(8) << left << userID << " | "
         << setw(10) << left << rating << " | "
         << setw(25) << left << hotelName << " | "
         << review << endl;
}

void Traveler::printTravelerInfo()const{
    cout << setw(8) << left << userID << " | "
         << setw(20) << left << userName << " | "
         << setw(18) << left << state << " | "
         << setw(25) << left << email << " | "
         << setw(15) << left << memberType << " | "
         << point << endl;
}

void Traveler::printTravelerReview()const{
    for(int reviewIndex = 0; reviewIndex < reviewNumber; reviewIndex++){
        review[reviewIndex].printReview();
    }
}

void UniqueHotel::printUniqueHotel(const int& hotelIndex)const{
    cout << " " << setw(4) << left << (hotelIndex + 1) << " | "
         << fixed << setprecision(2) 
         << setw(30) << left << hotelName << " | "
         << setw(20) << left << numReview << " | "
         << setw(20) << left << averageRating << " | ";

    for(int stars = 0; stars < static_cast<int>(averageRating); stars++){
            cout << "*";
    }

    cout << endl;
}



//  file reading
void Traveler::readTravelerInfo(fstream& userFile){
    int numInput;
    string input;

    getline(userFile, input, '\t');
    userID = input;

    getline(userFile, input, '\t');
    userName = input;

    getline(userFile, input, '\t');
    state = input;
    
    getline(userFile, input, '\t');
    email = input;

    getline(userFile, input, '\t');
    memberType = input;
    
    userFile >> numInput;
    point = numInput;

    while(userFile.peek() == '\n'){
        userFile.ignore();
    }
}

void Review::readReviewList(fstream& revFile){
    string input;
    int numInput;

    getline(revFile, input, '\t');
    userID = input;

    revFile >> numInput;
    revFile.ignore();
    rating = numInput;

    getline(revFile, input, '\t');
    review = input;
    
    getline(revFile, input, '\n');
    hotelName = input;

    while(revFile.peek() == '\n'){
        revFile.ignore();
    }
}



//  system functions
void Traveler::searchReview(Traveler tra[], const int& userCount){
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

    for(int travelerIndex = 0; travelerIndex < userCount; travelerIndex++){
        for(int reviewIndex = 0; reviewIndex < tra[travelerIndex].reviewNumber; reviewIndex++){
            if(tra[travelerIndex].review[reviewIndex].getHotelName() == hotelName){
                cout << setw(8) << left << tra[travelerIndex].review[reviewIndex].getUserID() << "| "
                     << setw(8) << left << tra[travelerIndex].review[reviewIndex].getRating() << "| "
                     << setw(23) << left << tra[travelerIndex].review[reviewIndex].getHotelName() << "| "
                     << tra[travelerIndex].review[reviewIndex].getReview()
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

void Traveler::travelerManagement(Traveler tra[], const int& userCount){
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
        if(tra[travelerIndex].userID == input){
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
                     << "Please insert new user name or remain the current user name: (current user name: " << tra[travelerIndex].userName << ")"
                     << endl;
                getline(cin, input);
                tra[travelerIndex].userName = input;
                break;

            //update state
            case STATE:
                cout << endl
                     << "Please insert new state or remain the current state: (current state: " << tra[travelerIndex].state << ")"
                     << endl;
                getline(cin, input);
                tra[travelerIndex].state = input;
                break;

            //update email
            case EMAIL:
                cout << endl
                     << "Please insert new email or remain the current email: (current email: " << tra[travelerIndex].email << ")"
                     << endl;
                getline(cin, input);
                tra[travelerIndex].email = input;
                break;

            //update memberType
            case MEMBER_TYPE:
                cout << endl
                     << "Please insert new member type or remain the current member type: (current member type: " << tra[travelerIndex].memberType << ")"
                     << endl;
                getline(cin, input);
                tra[travelerIndex].memberType = input;
                break;

            //update point
            case POINT:
                cout << endl
                     << "Please insert new point or remain the current point: (current point: " << tra[travelerIndex].point << ")"
                     << endl;
                cin >> numInput;
                cin.ignore();
                tra[travelerIndex].point = numInput;
                break;

            //update review from user
                //show a list of reviews by user
            case REVIEW:
                cout << endl
                     << "  " << "Review Index" << "  |"
                     << "  " << setw(25) << left << "Hotel" << "  |"
                     << "  " << "Review" << endl
                     << "-------------------------------------------------------------------------------------------------------------" << endl;
                for(int reviewIndex = 0; reviewIndex < tra[travelerIndex].getReviewNumber(); reviewIndex++){
                    cout << "  " << setw(13) << left << (reviewIndex + 1) << "  |"
                         << "  " << setw(25) << left << tra[travelerIndex].review[reviewIndex].getHotelName() << "  |"
                         << "  " << tra[travelerIndex].review[reviewIndex].getReview()
                         << endl;
                }
                cout << "-------------------------------------------------------------------------------------------------------------" << endl;
                
                cout << "Please select the Review Index of the review you wish to amend: ";
                cin >> numInput;
                cin.ignore();

                //altering the review
                cout << "Please insert your new review:" << endl;
                getline(cin, input);
                tra[travelerIndex].review[--numInput].setReview(input);
                break;
            
            //exit subpage
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

void Traveler::topReviewers(Traveler tra[], const int& userCount){
    Traveler top3Reviewers[3];
    
    //finding user who has the most reviews, then the highest average rating
    for(int travelerIndex = 0; travelerIndex < userCount; travelerIndex++){
        if(top3Reviewers[0] == tra[travelerIndex] || 
            top3Reviewers[1] == tra[travelerIndex] ||
            top3Reviewers[2] == tra[travelerIndex]){

            continue;
        }
        
        if(top3Reviewers[0] < tra[travelerIndex]){
            top3Reviewers[2] = top3Reviewers[1];
            top3Reviewers[1] = top3Reviewers[0];
            top3Reviewers[0] = tra[travelerIndex];

        }else if(top3Reviewers[1] < tra[travelerIndex]){
            top3Reviewers[2] = top3Reviewers[1];
            top3Reviewers[1] = tra[travelerIndex];

        }else if(top3Reviewers[2] < tra[travelerIndex]){
            top3Reviewers[2] = tra[travelerIndex];
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
        
    for(int index = 0; index < 3; index++){
        cout << setw(4) << right << (index + 1) << " | " 
             << setw(15) << left << top3Reviewers[index].userName << " | "
             << setw(10) << left << top3Reviewers[index].userID << " | "
             << setw(20) << left << top3Reviewers[index].reviewNumber << " | "
             << fixed << setprecision(2) 
             << top3Reviewers[index].averageRating
             << endl;
             
    }
    
    cout << "=============================================================================================================" << endl;
}

void Review::addReview(Review rev[], const string UID[], int& revNo){
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

        //user ID validation
        for(int userIndex = 0; userIndex < TRAVELER_NUM; userIndex++){
            if(input == UID[userIndex]){
                repeat = false;
                rev[revNo].userID = input;
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
    rev[revNo].hotelName = input;
    
    do{
        cout << endl
             << "------------------------------------------------------" << endl
             << " Insert Rating (1 to 5)" << endl
             << "------------------------------------------------------" << endl;
    
        cin >> numInput;
        cin.ignore();

        if(numInput < 1 || numInput > 5){
            repeat = true;
            cout << endl
                 << "Please try again, rating must be between 1 and 5 (inclusive)" << endl
                 << endl;
        }else{
            rev[revNo].rating = numInput;
        }
    }while(repeat);

    cout << endl
         << "------------------------------------------------------" << endl
         << " Insert your review for " << input << endl
         << "------------------------------------------------------" << endl;

    getline(cin, input);
    rev[revNo].review = input;
    
    revNo++;

    cout << endl
         << "<----------- New review successfully updated ----------->" << endl
         << endl;
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
        return 1;
    }

    int userCount = 0;
    int reviewNumber = 0;
    int uniqueHotelNum = 0;
    
    Traveler traveler[TRAVELER_NUM];
    while(!userFile.eof() && userCount < TRAVELER_NUM){
        traveler[userCount++].readTravelerInfo(userFile);
    }

    Review review[REVIEW_NUM];
    while(!revFile.eof() && reviewNumber < REVIEW_NUM){
        review[reviewNumber++].readReviewList(revFile);
    }

    //  assigning number of reviews and average rating of each traveler    
    for(int travelerIndex = 0; travelerIndex < userCount; travelerIndex++){
        traveler[travelerIndex].assignTravelerReviewInfo(review, reviewNumber);
    }

    //  print out user and review for confirmation
    printTravelerHeader();
    for(int travelerIndex = 0; travelerIndex < userCount; travelerIndex++){
        traveler[travelerIndex].printTravelerInfo();
    }
    printTableFooter();

    printReviewHeader();
    for(int travelerIndex = 0; travelerIndex < userCount; travelerIndex++){
        traveler[travelerIndex].printTravelerReview();
    }
    printTableFooter();
    

    cout << "<-------------text files successfully read-------------->" << endl
         << endl;
    cout << endl << endl << endl;


    UniqueHotel uniqueHotel[REVIEW_NUM];
    //initialising a list of unique hotels
    UniqueHotel::assignUniqueHotels(review, uniqueHotel, reviewNumber, uniqueHotelNum);

    //  an array of user ID initialised
    string UID[TRAVELER_NUM];
    for(int userIndex = 0; userIndex < userCount; userIndex++){
        UID[userIndex] = traveler[userIndex].getUserID();
    }

    UserOption option = SHOW_DATA;
    while(option != EXIT_SYSTEM){
        option = userSelection();
        switch(option){
            case SHOW_DATA:

                // print traveler information
                printTravelerHeader();
                for(int travelerIndex = 0; travelerIndex < userCount; travelerIndex++){
                    traveler[travelerIndex].printTravelerInfo();
                }
                printTableFooter();

                // print review information
                printReviewHeader();
                for(int travelerIndex = 0; travelerIndex < userCount; travelerIndex++){
                    traveler[travelerIndex].printTravelerReview();
                }
                printTableFooter();
                
                cout << endl << endl << endl;
                break;

            case SEARCH:
                Traveler::searchReview(traveler, userCount);
                cout << endl << endl << endl;
                break;

            case TRAVELER_MANAGEMENT:
                Traveler::travelerManagement(traveler, userCount);
                cout << endl << endl << endl;
                break;

            case ADD_REVIEWS:
                Review::addReview(review, UID, reviewNumber);
                cout << endl << endl << endl;

                // update traveler reviewNumber and averageRating
                for(int travelerIndex = 0; travelerIndex < userCount; travelerIndex++){
                    traveler[travelerIndex].assignTravelerReviewInfo(review, reviewNumber);
                }

                // update number of reviews and average rating of each hotels
                UniqueHotel::assignUniqueHotels(review, uniqueHotel, reviewNumber, uniqueHotelNum);

                break;

            case HIGHEST_RATED_HOTEL:
                UniqueHotel::sortHotel(uniqueHotel, uniqueHotelNum);

                printUniqueHotelHeader();
                for(int hotelIndex = 0; hotelIndex < uniqueHotelNum; hotelIndex++){
                    uniqueHotel[hotelIndex].printUniqueHotel(hotelIndex);
                }
                printTableFooter();

                cout << endl << endl << endl;
                break;

            case TOP_REVIEWERS:
                Traveler::topReviewers(traveler, userCount);
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
         << "============= Rewriting data into users.txt ==============" << endl
         << "..."
         << endl;

    // clear flags and move cursor back to start of text file
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

    cout << "<------------ users.txt successfully updated ------------>" << endl
         << endl;
}

void writeReviewFile(Review rev[],  const int& revNo, fstream& revFile){
    cout << endl
         << "============= Rewriting data into reviews.txt ==============" << endl
         << "..."
         << endl;
    
    // clear flags and move cursor back to start of text file
    revFile.clear();
    revFile.seekg(0, ios::beg);

    for(int revNumber = 0; revNumber < revNo; revNumber++){
        revFile << rev[revNumber].userID << '\t'
                << rev[revNumber].rating << '\t'
                << rev[revNumber].review << '\t'
                << rev[revNumber].hotelName << '\n';
    }

    revFile.close();

    cout << "<----------- reviews.txt successfully updated ----------->" << endl
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