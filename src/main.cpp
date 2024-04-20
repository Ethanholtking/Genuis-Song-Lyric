#import <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "red_black.h"
#include "UnorderedMap.cpp"
#include <chrono>
using namespace std;

// Function to read csv
vector<vector<string>> readCSV(const string& filename) {

    // Define vectors to store CSV
    vector<vector<string>> data;

    // reading in file
    ifstream file("Songs and Artists.csv");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return data;
    }

    // Read each line of the file
    string line;
    while(getline(file, line)){
        vector<string> row;
        stringstream ss(line);
        string cell;

        // Read and discard the first cell
        getline(ss, cell, ',');
        getline(ss, cell, ',');

        // Split the line into cells using comma as delimiter
        while(getline(ss, cell, ',')){
            row.push_back(cell);
        }

        data.push_back(row);

    }
    file.close();
    return data;
}


int main() {
    bool start = true;
    string input;
    string methodPick;
    string loopEnd;

    // Read in the CSV data

    vector<vector<string>> csvData = readCSV("Songs and Artists.csv");
    // FIXME: I checked and each vector<string> within the vector only has one element in it, is data being read in correctly?

    // insert data to hash map
    auto timeStart = chrono::high_resolution_clock::now();
    UnorderedMap map(16);

    for(const auto& element : csvData){ // FIXME: i believe this is adding each entry as a title, including artist name?
        for(const auto& str : element) {
            map.addSong(str);
        }
    }
    auto timeEnd = chrono::high_resolution_clock::now();
    auto timeToExecute = chrono::duration_cast<chrono::milliseconds>(timeEnd - timeStart);

    cout << "Loaded Unordered Map (Hash Table) in " << timeToExecute.count() << "ms!" << endl;

    cout << endl;
    std::cout << "Welcome to the Genius Song Title Search!\n" << std::endl;
    while(start){


        std::cout << "Which function would you like to use?" << endl;
        cout << "1. Most used words in song titles\n2. % of total songs that include specific word\n"
                "3. Search for a song\n4. Quit\n" << endl;
        cout << "(Type 1, 2, 3, or 4): ";
        cin >> methodPick;

        if (methodPick == "1") {
            cout << "find most used song titles" << endl;
        }
        else if (methodPick == "2") {
            cout << "find % of total songs" << endl;
        }
        else if (methodPick == "3") {
            std::cout << "Please enter the song to search:";
            cin >> input; // string to be searched in song list
            cout << endl;
        }
        else {
            start = false;
            break;
        }


        // Ask user if they want to search again
        cout << "Would you like to use again? (Y for yes N for no):";
        cin >> loopEnd;
        if(loopEnd == "n" || loopEnd == "N"){
            start = false;
        }
    }
    cout << "Thank you for using Genius Title Search!" << endl;
}