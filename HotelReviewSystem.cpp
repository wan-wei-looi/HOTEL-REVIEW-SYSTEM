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
enum UserOption {
    SHOW_DATA,
    SEARCH,
    TRAVELER_MANAGEMENT,
    ADD_REVIEWS,
    HIGHEST_RATED_HOTEL,
    TOP_REVIEWERS,
    EXIT_SYSTEM
};


//  global print function prototype
void printMainMenu();

void printTravelerHeader();

void printReviewHeader();

void printUniqueHotelHeader();

void printTableFooter();


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
    int reviewNum = 0;
    int uniqueHotelNum = 0;
    
    Review review[REVIEW_NUM];
    while(!revFile.eof() && reviewNum < REVIEW_NUM){
        review[reviewNum++].readReviewList(revFile);
    }

    Traveler traveler[TRAVELER_NUM];
    while(!userFile.eof() && userCount < TRAVELER_NUM){
        traveler[userCount++].readTravelerInfo(userFile);
    }
    
    for(int userIndex = 0; userIndex < userCount; userIndex++){
        traveler[userIndex].assignTravelerReviews(review, reviewNum);
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


//  user selection function definition
UserOption userSelection(){
    UserOption option;
    int input = 0;

    printMainMenu();
    
    cin >> input; cin.ignore();
    option = static_cast<UserOption>(--input);
    
    return option;
}