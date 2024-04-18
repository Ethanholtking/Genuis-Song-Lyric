#import <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "red_black.h"
#include "UnorderedMap.cpp"
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

    /*
    // Temp print data
    for (const auto& row : csvData) {
        for (const auto& cell : row) {
            std::cout << cell << "\t";
        }
        std::cout << std::endl;
    }
    */

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
            UnorderedMap map(csvData.size());
            string title;
            string artist;




            for(int i=0; i<=(csvData.size()-1); i++){
                //title = csvData.at(i).at(i+1);
                i++;
            }


            //cout << artist << title << endl;
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