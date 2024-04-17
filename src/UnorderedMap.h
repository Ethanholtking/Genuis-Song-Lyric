#ifndef GENUIS_SONG_LYRIC_UNORDEREDMAP_H
#define GENUIS_SONG_LYRIC_UNORDEREDMAP_H

#import <string>
#import <list>
using namespace std;



struct Node {
    string artist;
    string title;
    Node(string &inputTitle, string &inputArtist) {title = inputTitle; artist = inputArtist;}
};

class UnorderedMap {
private:
    list<Node> *array;
    float loadFactor;
    int capacity;
    int size;
public:
    UnorderedMap(int inputCapacity);
    ~UnorderedMap();
    float getLoadFactor();
    int hashFunction(string &title, int inputCapacity);
    void addSong(string title, string artist);
    Node* searchSong(string title);
    void rebuild();
};


#endif //GENUIS_SONG_LYRIC_UNORDEREDMAP_H
