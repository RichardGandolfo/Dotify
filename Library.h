#ifndef LIBRARY_H
#define LIBRARY_H

#include "SongWrapper.h"
#include <unordered_map>
#include <vector>
#include <algorithm>

class Library
{
    //This class is responsible for storing SongWrapper pointers. Its underlying data strucutre(s) include 2 unordered maps,
    //one that maps the song's ID to its SongWrapper pointer. In order to achieve O(1) time complexity, a second unordered map
    //is used to store a single string, comprised of the song's name, artist, and album which is mapped to that song's ID number.
    //Because of this, checking to see if a potential new song already exists in the library can be done in constant time, given
    //its name artist and album. A private int is used to keep track of what ID number to assign to a new song. It is only ever
    //increased, ensuring that ID numbers are always unique.
    private:
        unordered_map<unsigned int, SongWrapper*> masterList;
        unordered_map<string, unsigned int> masterListHelper;
        int nextPosition=1;

    //A destructor is used since the addToList function makes use of the new function of the SongWrapper pointer.
    //These functions allow SongWrapper pointers to be added to both maps, the main one and its helper. A function also exists to
    //print all of the songs currently in the library. This class also "plays" and removes songs, once given the song ID number.
    //The rest are helper functions which check to see if a song exists, based on the ID number/string given and functions that sort the
    //existing songs so they can be printed in any desired order.
    public:
        ~Library();
        bool addToList(string name, string artist, string album);
        void directAdd(string name, string artist, string album, int plays, int id);
        bool removeFromList(unsigned int target);
        void displayList(string criteria);
        bool playSong(unsigned int identifier, unsigned int timesPlay);
        SongWrapper* getSong(unsigned int identifier);
        int getNumberFromDetails(string name, string artist, string album) {return masterListHelper[name+artist+album];}
        int getNumberOfSongs() {return masterList.size();}
        int getNext() {return nextPosition;}
        void changeNext(int update) {nextPosition=update;}
        bool checkContainsSong(string name, string artist, string album);
        bool checkContainsKey(unsigned int pos);
        void fillVector(vector<SongWrapper*>&temp);
        bool sortName(vector<SongWrapper*>&temp);
        bool sortArtist(vector<SongWrapper*>&temp);
        bool sortAlbum(vector<SongWrapper*>&temp);
        bool sortPlays(vector<SongWrapper*>&temp);
};

#endif // LIBRARY_H
