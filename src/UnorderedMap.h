#ifndef GENUIS_SONG_LYRIC_UNORDEREDMAP_H
#define GENUIS_SONG_LYRIC_UNORDEREDMAP_H

#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <algorithm>
#include <queue>
using namespace std;



struct Node {
    string title;
    Node(string& inputTitle) { title = inputTitle; }
};

class UnorderedMap {
private:
    list<Node>* array;
    float loadFactor;
    int capacity;
    int size;
public:
    UnorderedMap(int inputCapacity);
    ~UnorderedMap();
    float getLoadFactor();
    int hashFunction(string& title, int inputCapacity);
    void addSong(string title);
    Node* searchSong(string title);
    void rebuild();
    vector<pair<string, float>> mostUsedWords();
    float percentSongsWithWord(string word);
    string toLower(string& title);
    int getSize() { return size; };
    int getCapacity() { return capacity; };
};


#endif //GENUIS_SONG_LYRIC_UNORDEREDMAP_H
