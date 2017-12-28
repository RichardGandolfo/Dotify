#ifndef SONG_H
#define SONG_H

#include <iostream>
#include <string>
using namespace std;

//This is the most fundamental class of the program. It contains 3 strings representing its
// name, artist, and album. It sets its information with a constructor and can return information about its 3 private members.
class Song
{
    private:
        string name;
        string artist;
        string album;

    public:
        Song(string x, string y, string z): name(x), artist(y), album(z) {}
        string getName() {return name;}
        string getArtist() {return artist;}
        string getAlbum() {return album;}
};

#endif
