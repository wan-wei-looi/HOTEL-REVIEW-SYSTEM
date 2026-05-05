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

bool UniqueHotel::operator>(const UniqueHotel& hotel)const{
    return ((this->averageRating) > hotel.averageRating);
}



//  global print function prototype
void printMainMenu();

void printTravelerHeader();

void printReviewHeader();

void printUniqueHotelHeader();

void printTableFooter();



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
         << setw(30) << left << getHotelName() << " | "
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

void Traveler::readReviewList(fstream& revFile){
    
    revFile.clear();
    revFile.seekg(0, ios::beg); //resets every time it is called
    
    string uidInput;
    int ratingInput;
    string reviewInput;
    string hotelNameInput;


    //  assigning reviews based on uid
    while(!revFile.eof() && reviewNumber < TRAVELER_REV_NUM){
        getline(revFile, uidInput, '\t');
        
        revFile >> ratingInput;
        revFile.ignore();
        
        getline(revFile, reviewInput, '\t');
        
        getline(revFile, hotelNameInput, '\n');
        
        if(uidInput == userID){
            review[reviewNumber].setUserID(uidInput);
            review[reviewNumber].setRating(ratingInput);
            review[reviewNumber].setReview(reviewInput);
            review[reviewNumber].setHotelName(hotelNameInput);
            reviewNumber++;
        }
        while(revFile.peek() == '\n'){
            revFile.ignore();
        }
    }

    //  calculating average rating user
    double sumRating = 0;

    for(int reviewIndex = 0; reviewIndex < reviewNumber; reviewIndex++){
        sumRating += review[reviewIndex].getRating();
    }

    averageRating = (reviewNumber)? (sumRating / reviewNumber) : reviewNumber;
}



//  system functions
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

void Traveler::travelerManagement(Traveler tra[], const int& userCount){
    string input;
    int numInput;
    int tempInput = 0;
    
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
                     << "-------------------------------------------------------------------------------------------------------------" << endl
                     << "  " << "Review Index" << "  |"
                     << "  " << setw(25) << left << "Hotel" << "  |"
                     << "  " << setw(10) << left << "Rating" << "  |"
                     << "  " << "Review" << endl
                     << "-------------------------------------------------------------------------------------------------------------" << endl;
                for(int reviewIndex = 0; reviewIndex < tra[travelerIndex].getReviewNumber(); reviewIndex++){
                    cout << "  " << setw(12) << left << (reviewIndex + 1) << "  |"
                         << "  " << setw(25) << left << tra[travelerIndex].review[reviewIndex].getHotelName() << "  |"
                         << "  " << setw(10) << left << tra[travelerIndex].review[reviewIndex].getRating() << "  |"
                         << "  " << tra[travelerIndex].review[reviewIndex].getReview()
                         << endl;
                }
                cout << "-------------------------------------------------------------------------------------------------------------" << endl;
                cout << "Please select the Review Index of the review you wish to amend: ";
                cin >> numInput;
                cin.ignore();
                
                if(numInput > tra[travelerIndex].reviewNumber){
                    cout << "Invalid Input..." << endl;
                    break;
                }

                cout << endl
                     << "-------------------------------------------------------------------------------------------------------------" << endl
                     << " 1. Change hotel name:" << endl
                     << " 2. Change hotel rating:" << endl
                     << " 3. Change review" << endl
                     << "-------------------------------------------------------------------------------------------------------------" << endl;
                
                cout << "Please select your option: ";
                cin >> tempInput;
                cin.ignore();

                switch(tempInput){
                    case 1:
                        //altering the hotel name
                        cout << "Please insert the new hotel name:" << endl;
                        getline(cin, input);
                        tra[travelerIndex].review[--numInput].setHotelName(input);
                        break;

                    case 2:
                        //altering the rating
                        cout << "Please insert your new rating:" << endl;
                        cin >> tempInput;
                        if(tempInput < 1 || tempInput > 5){
                            cout << "Invalid input..." << endl;
                            break;
                        }
                        cin.ignore();
                        tra[travelerIndex].review[--numInput].setRating(tempInput);
                        break;

                    case 3:
                        //altering the review
                        cout << "Please insert your new review:" << endl;
                        getline(cin, input);
                        tra[travelerIndex].review[--numInput].setReview(input);
                        break;

                    default:
                        cout << "Invalid input..." << endl;
                }
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

void Traveler::addReview(Traveler tra[], const string UID[]){
    bool repeat = true;
    string input;
    int numInput;
    int travelerIndex = 0;

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
        for(travelerIndex; travelerIndex < TRAVELER_NUM; travelerIndex++){
            if(input == UID[travelerIndex]){
                tra[travelerIndex].review[(tra[travelerIndex].reviewNumber)].setUserID(input);
                repeat = false;
                break;
            }
        }
        if(repeat){
            travelerIndex = 0;
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
    tra[travelerIndex].review[(tra[travelerIndex].reviewNumber)].setHotelName(input);
    
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
            repeat = false;
            tra[travelerIndex].review[(tra[travelerIndex].reviewNumber)].setRating(numInput);
        }
    }while(repeat);

    cout << endl
         << "------------------------------------------------------" << endl
         << " Insert your review for " << input << endl
         << "------------------------------------------------------" << endl;

    getline(cin, input);
    tra[travelerIndex].review[(tra[travelerIndex].reviewNumber)].setReview(input);
    
    tra[travelerIndex].reviewNumber++;

    cout << endl
         << "<----------- New review successfully updated ----------->" << endl
         << endl;

    //  calculating average rating user
        double sumRating = 0;

        for(int reviewIndex = 0; reviewIndex < tra[travelerIndex].reviewNumber; reviewIndex++){
            sumRating += tra[travelerIndex].review[reviewIndex].getRating();
        }

        tra[travelerIndex].averageRating = (tra[travelerIndex].reviewNumber)? (sumRating / tra[travelerIndex].reviewNumber) : tra[travelerIndex].reviewNumber;
}

//  friend global functions declaration
void createUIDlist(Traveler[], const int&, string[]);

void writeUserFile(Traveler[], const int&, fstream&);

void writeReviewFile(Traveler[], const int&, fstream&);

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
    int uniqueHotelNum = 0;
    
    Traveler traveler[TRAVELER_NUM];
    while(!userFile.eof() && userCount < TRAVELER_NUM){
        traveler[userCount++].readTravelerInfo(userFile);
    }
    for(int travelerIndex = 0; travelerIndex < userCount; travelerIndex++){
        traveler[travelerIndex].readReviewList(revFile);
    }

    Review review[REVIEW_NUM];

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
    //initialising a list of unique hotels - must start with the first one, index[0]
    uniqueHotel[0].assignUniqueHotels(traveler, userCount, uniqueHotelNum);

    //  an array of user ID initialised
    string UID[TRAVELER_NUM];
    createUIDlist(traveler, userCount, UID);

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
                UniqueHotel::searchReview(uniqueHotel, uniqueHotelNum);
                cout << endl << endl << endl;
                break;

            case TRAVELER_MANAGEMENT:
                Traveler::travelerManagement(traveler, userCount);
                cout << endl << endl << endl;
                break;

            case ADD_REVIEWS:
                Traveler::addReview(traveler, UID);
                cout << endl << endl << endl;                
                break;
                
            case HIGHEST_RATED_HOTEL:

                // update number of reviews and average rating of each hotels - must start with the first one, index[0]
                uniqueHotel[0].assignUniqueHotels(traveler, userCount, uniqueHotelNum);
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
                writeReviewFile(traveler, userCount, revFile);
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
void createUIDlist(Traveler tra[], const int& userCount, string UID[]){
    for(int index = 0; index < userCount; index++){
        UID[index] = tra[index].userID;
    }
}

void writeUserFile(Traveler tra[], const int& userCount, fstream& userFile){
    cout << endl
         << "============= Rewriting data into users.txt ==============" << endl
         << "..."
         << endl;

    // clear flags and move cursor back to start of text file
    userFile.clear();
    userFile.seekp(0, ios::beg);

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

void writeReviewFile(Traveler tra[],  const int& userCount, fstream& revFile){
    cout << endl
         << "============= Rewriting data into reviews.txt ==============" << endl
         << "..."
         << endl;
    
    // clear flags and move cursor back to start of text file
    revFile.clear();
    revFile.seekp(0, ios::beg);

    for(int travelerIndex = 0; travelerIndex < userCount; travelerIndex++){
        for(int reviewIndex = 0; reviewIndex < tra[travelerIndex].reviewNumber; reviewIndex++){
            revFile << tra[travelerIndex].review[reviewIndex].getUserID() << '\t'
                    << tra[travelerIndex].review[reviewIndex].getRating() << '\t'
                    << tra[travelerIndex].review[reviewIndex].getReview() << '\t'
                    << tra[travelerIndex].review[reviewIndex].getHotelName() << '\n';
        }
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