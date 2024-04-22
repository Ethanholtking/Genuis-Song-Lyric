#include "UnorderedMap.h"
#include <unordered_map> // WE VERIFIED WITH A TA THAT WE ARE ALLOWED TO USE THIS - used for data calculation, does not contribute to the actual data structures that we created

UnorderedMap::UnorderedMap(int inputCapacity) {
    capacity = inputCapacity;
    size = 0;
    loadFactor = getLoadFactor();
    array = new list<Node>[capacity];
}

float UnorderedMap::getLoadFactor() {
    return (float)size / (float)capacity;
}

string UnorderedMap::toLower(string &title)
{
    for (int i = 0; i < title.length(); i++)
        title[i] = tolower(title[i]);
    return title;
}

int UnorderedMap::hashFunction(std::string &title, int inputCapacity) { // add ascii of each character, mod total by capacity
    int asciiTotal = 0;
    for (char c : title) {
        asciiTotal += (int)c;
    }
    return asciiTotal % inputCapacity;
}

void UnorderedMap::addSong(string title) {
    string input = toLower(title);
    Node node = Node(input);
    int hash = hashFunction(title, capacity);
    array[hash].emplace_back(title);
    size++;
    loadFactor = getLoadFactor();
    if (loadFactor >= 0.75) {
        rebuild();
    }
}

Node* UnorderedMap::searchSong(std::string title) {
    title = toLower(title);
    int hash = hashFunction(title, capacity);
    if (!array[hash].empty()) { // ensures that title exists in array by searching for hash
        for (auto & node : array[hash]) { // iterates through list (chaining) to find song
            if (node.title == title) {
                return &node;
            }
        }
    }
    return nullptr;
}

void UnorderedMap::rebuild() { // rehashes all entries with new mapsize
    auto *newArray = new list<Node>[capacity * 2];
    list<Node> *currArray = array;
    for (int i = 0; i < capacity; i++) {
        if (!array[i].empty()) { // ensures that title exists in array by searching for hash
            for (auto &node: array[i]) { // iterates through list (chaining) to find song
                int hash = hashFunction(node.title, capacity * 2);
                newArray[hash].emplace_back(node.title);
            }
        }
    }
    array = newArray;
    delete[] currArray;
    capacity *= 2;
}

UnorderedMap::~UnorderedMap() {
    delete[] array;
}

vector<pair<string, float>> UnorderedMap::mostUsedWords() {
    unordered_map<string, int> words;
    for (int i = 0; i < capacity; i++) {
        if (!array[i].empty()) { // ensures that title exists in array by searching for hash
            for (auto &node: array[i]) { // iterates through list (chaining) to find song
                stringstream songTitle(node.title);
                string singleWord;
                vector<string> alreadyContains;
                while (songTitle >> singleWord) { // place all words in title into map to store words and frequencies
                    if (find(alreadyContains.begin(), alreadyContains.end(), singleWord) == alreadyContains.end()) {
                        if (words.find(singleWord) != words.end()) {
                            words[singleWord]++;
                            alreadyContains.push_back(singleWord);
                        } else {
                            words.emplace(singleWord, 1);
                            alreadyContains.push_back(singleWord);
                        }
                    }
                }
            }
        }
    }
    priority_queue<pair<int, string>> pQueue;
    for (auto &word : words) {
        pQueue.emplace(word.second, word.first);
    }
    vector<pair<string, float>> topFive;
    for (int i = 0; i < 5; i++) {
        pair<int, string> greatestWord = pQueue.top();
        pQueue.pop();
        topFive.emplace_back(greatestWord.second, ((float)greatestWord.first / (float)size));
    }
    return topFive;
}

float UnorderedMap::percentSongsWithWord(string word) {
    word = toLower(word);
    int wordCount = 0;
    for (int i = 0; i < capacity; i++) {
        if (!array[i].empty()) { // ensures that title exists in array by searching for hash
            for (auto &node: array[i]) { // iterates through list (chaining) to find song
                stringstream songTitle(node.title);
                string singleWord;
                bool alreadyContains = false;
                while (songTitle >> singleWord) { // place all words in title into map to store words and frequencies
                    if (!alreadyContains) {
                        if (word == singleWord) {
                            wordCount++;
                            alreadyContains = true;
                        }
                    }
                }
            }
        }
    }
    return (float)wordCount / (float)size;
}