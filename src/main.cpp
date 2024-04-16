#import <iostream>
#import <string>
using namespace std;

int main() {
    bool start = true;
    string input;
    string methodPick;
    string loopEnd;

    cout << endl;
    std::cout << "Welcome to the Genius Song Title Search!" << std::endl;
    while(start){
        std::cout << "Please enter the word to search:";
        cin >> input; // string to be searched in song list
        cout << endl;

        std::cout << "Which method would you like to search with?" << endl;
        cout << "(Type 1 for Unordered Map and type 2 for Ordered Map):";
        cin >> methodPick;

        // Hash set
        if(methodPick == "1"){
            cout << "show the result of Unordered map" << endl;
            cout << endl;
        }
        // Red Black tree
        else if(methodPick == "2"){
            cout << "show the result of Ordered map" << endl;
            cout << endl;
        }

        // Ask user if they want to search again
        cout << "Would you like to search again? (Y for yes N for no):";
        cin >> loopEnd;
        if(loopEnd == "n" || loopEnd == "N"){
            start = false;
        }
    }
    cout << "Thank you for using Genius Title Search!" << endl;
}