#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>

#include "Traveler.h"
#include "Person.h"
#include "Review.h"

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

void Traveler::assignTravelerReviews(Review rev[], const int& reviewNum){
    
    //  assigning reviews based on uid
    for(int reviewIndex = 0; reviewIndex < reviewNum; reviewIndex++){
        if(rev[reviewIndex].getUserID() == userID){
            review[reviewNumber++] = rev[reviewIndex];
        }
    }

    //  calculating average rating user
    double sumRating = 0;

    for(int reviewIndex = 0; reviewIndex < reviewNumber; reviewIndex++){
        sumRating += review[reviewIndex].getRating();
    }

    averageRating = (reviewNumber)? (sumRating / reviewNumber) : reviewNumber;
}


//  system function
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
             << "---------------------------------------------------------" << endl
             << "Your input: ";
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
                        do{
                            cout << "Please insert your new rating:" << endl;
                            cin >> tempInput;
                            cin.ignore();
                            if(tempInput < 1 || tempInput > 5){
                                cout << "Invalid input..." << endl;
                                break;
                            }
                        }while(tempInput < 1 || tempInput > 5);
                        
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
         << "=========================================================" << endl
         << "Enter the necessary information as prompted." << endl;
    do{
        cout << endl
             << "---------------------------------------------------------" << endl
             << " Insert User ID [User ID must be registered]" << endl
             << "---------------------------------------------------------" << endl;

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
         << "---------------------------------------------------------" << endl
         << " Insert hotel name" << endl
         << " ! System is case sensitive" <<endl 
         << " ! Different capitalisation refers to different hotel" << endl
         << "---------------------------------------------------------" << endl;

    getline(cin, input);
    tra[travelerIndex].review[(tra[travelerIndex].reviewNumber)].setHotelName(input);
    
    do{
        cout << endl
             << "---------------------------------------------------------" << endl
             << " Insert Rating (1 to 5)" << endl
             << "---------------------------------------------------------" << endl;
    
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
         << "---------------------------------------------------------" << endl
         << " Insert your review for " << input << endl
         << "---------------------------------------------------------" << endl;

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


//  print
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


//  friend global function definition
void createUIDlist(const Traveler tra[], const int& userCount, string UID[]){
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

