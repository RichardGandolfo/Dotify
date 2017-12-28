#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "SongWrapper.h"
#include <map>
#include <unordered_map>

class Playlist
{
    //This class is a blueprint for a single Playlist, in which is contained a string representing the playlist name,
    //an int rating which is only between 1 and 5, inclusively, and 2 maps as its underlying data structure. The first one
    //is the main subset of songs from the library that preserves the order in which songs are added. The second map allows O(1) access to a song,
    //given its ID number. A nextPosition int is used similarly to the Library class.
    private:
        string title;
        unsigned int rating=1;
        //maps in order position to SongWrapper pointer
        map<unsigned int, SongWrapper*> subset;
        //maps ID number of song to its order number
        unordered_map<unsigned int, unsigned int> subsetHelper;
        int nextPosition=1;

    public:
        //Functions allow the user to rename the playlist, change the rating, add or remove songs from the playlist, and print the
        //songs within the playlist. The other functions are helpers which return if a song exists in the playlist, format info into
        //a string, and returns info about the object itself.
        bool renamePlaylist(string newTitle) {title=newTitle;}
        bool updateRating(int newRating) {rating=newRating;}
        bool addToPlaylist(SongWrapper*);
        bool removeFromPlaylist(int identifier);
        string getTitle() {return title;}
        int getRating() {return rating;}
        int getNumberOfSongs() {return subset.size();}
        SongWrapper* getSong(int order) {return subset[order];}
        int getNext() {return nextPosition;}
        bool containsOrder(int order);
        void printSongs();
        string formatPlaylistInfo()
        {
            return "\""+title+"\""+" - "+"Rating: "+to_string(rating)+" - "+to_string(subset.size())+" songs";
        }
        bool containsSong(int identifier);
        string to_string(int number);
};
#endif // PLAYLIST_H
