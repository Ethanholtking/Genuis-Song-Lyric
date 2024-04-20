#import <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "red_black.h"
#include "UnorderedMap.cpp"
#include <chrono>
#include <iomanip>
using namespace std;

// Function to read csv
vector<string> readCSV(const string& filename) {

    // Define vectors to store CSV
    vector<string> data;

    // reading in file
    ifstream file("Songs and Artists.csv");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return data;
    }

    // Read each line of the file
    string line;
    while(getline(file, line)){
        //vector<string> row;
        stringstream ss(line);
        string cell;

        // Read and discard the first cell
        getline(ss, cell, ',');
        getline(ss, cell, ',');

        // Split the line into cells using comma as delimiter
        getline(ss, cell, ',');
        data.push_back(cell);
    }
    file.close();
    return data;
}
int main() {
    bool start = true;
    string input;
    string methodPick;
    string loopEnd;
    cout << endl;

    // Read in the CSV data
    vector<string> csvData = readCSV("Songs and Artists.csv");

    // Chrono timer
    auto timeStart = chrono::high_resolution_clock::now();

    // insert data to hash map
    UnorderedMap map(16);
    for(const auto& element : csvData){
        map.addSong(element);
    }
    auto timeEnd = chrono::high_resolution_clock::now();
    auto timeToExecute = chrono::duration_cast<chrono::milliseconds>(timeEnd - timeStart);

    cout << "Loaded Unordered Map (Hash Table) in " << timeToExecute.count() << "ms!" << endl;
    cout << endl;
    std::cout << "Welcome to the Genius Song Title Search!\n";
    while(start){
        cout << std::endl;
        std::cout << "Which function would you like to use?" << endl;
        cout << "1. Most used words in song titles\n2. % of total songs that include specific word\n"
                "3. Search for a song\n4. Quit\n";
        cout << "(Type 1, 2, 3, or 4):";
        cin >> methodPick;
        cout << endl;

        if (methodPick == "1") {
            cout << "Showing most used words in song titles:" << endl;
            // Chrono timer
            auto timeStart = chrono::high_resolution_clock::now();
            vector<pair<string, float>> top5 = map.mostUsedWords();
            auto timeEnd = chrono::high_resolution_clock::now();
            auto timeToExecute = chrono::duration_cast<chrono::milliseconds>(timeEnd - timeStart);

            for (int i = 0; i < 5; i++) {
                cout << i + 1 << ": " << top5[i].first << " (" << setprecision(4) << top5[i].second * 100 << "%)"
                     << endl;
            }
            cout << "Finding most used words in song titles in Unordered Map (Hash Table) in " << timeToExecute.count()
                 << "ms!" << endl;
        }
        else if (methodPick == "2") {
            string word;
            float percentRes;
            cout << "Please enter a word you would like to search:";
            cin >> word;
            cout << endl;
            auto timeStart = chrono::high_resolution_clock::now();
            percentRes = map.percentSongsWithWord(word); //FIXME not sure if it is outputing the correct percentage
            auto timeEnd = chrono::high_resolution_clock::now();
            auto timeToExecute = chrono::duration_cast<chrono::milliseconds>(timeEnd - timeStart);

            cout << "Percentage the word \"" << word << "\" was used in song titles: " << percentRes << "%" << endl;
            cout << "Finding percentage of single word in a song title in Unordered Map (Hash Table) in " << timeToExecute.count()
                 << "ms!" << endl;
        }

        // FIXME Not able to print the title of node when found in search song in UnOrdered cpp
        else if (methodPick == "3") {
            string findTitle;
            std::cout << "Please enter the song to search:";
            getline(cin >> std::ws, findTitle); // string to be searched in song list
            cout << findTitle << endl;

            auto timeStart = chrono::high_resolution_clock::now();
            Node* songFound = map.searchSong(findTitle);
            auto timeEnd = chrono::high_resolution_clock::now();
            auto timeToExecute = chrono::duration_cast<chrono::milliseconds>(timeEnd - timeStart);

            cout << "Finding song title in Unordered Map (Hash Table) in " << timeToExecute.count()
                 << "ms!" << endl;
            if (songFound != nullptr) {
                cout << songFound->title  << " was found in the database!" << endl;
            }
            else{
                cout << "Song is not in database!" << endl;
            }
        }
        else {
            start = false;
            break;
        }
        // Ask user if they want to search again
        cout << endl;
        cout << "Would you like to use again? (Y for yes N for no):";
        cin >> loopEnd;
        if(loopEnd == "n" || loopEnd == "N"){
            start = false;
        }
    }
    cout << "Thank you for using Genius Title Search!" << endl;
}