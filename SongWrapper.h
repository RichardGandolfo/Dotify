#ifndef SONGWRAPPER_H
#define SONGWRAPPER_H

#include "Song.h"

class SongWrapper
{
    //This class is the main object being stored by larger containers. It contains an instance of a Song object. Its other 2
    //private members track the number of times the song was played and an int identifier which is assigned by the library.
    private:
        Song internalSong;
        unsigned int numPlays=0;
        unsigned int identifier;

    //A constructor is used to assign data to the embedded Song object. The class can update the number of plays and ID number.
    //It also returns information about itself as strings and ints.
    public:
        SongWrapper(string a, string b, string c): internalSong(a, b, c) {}
        void incrementPlays() {numPlays++;}
        void setID(unsigned int ID) {identifier = ID;}
        string getName() {return internalSong.getName();}
        string getArtist() {return internalSong.getArtist();}
        string getAlbum() {return internalSong.getAlbum();}
        unsigned int getNumberPlays() {return numPlays;}
        unsigned int getID() {return identifier;}
        string FullDetails() {return internalSong.getName()+internalSong.getArtist()+internalSong.getAlbum();}
        //These format functions return a string in a variety of different styles that is later printed by another class.
        string formatForPlaylist()
        {
            return internalSong.getName()+"|"+internalSong.getArtist()+"|"+internalSong.getAlbum();
        }
        string formatForLibrary()
        {
            return formatForPlaylist()+"|"+to_string(numPlays)+"|"+to_string(identifier);
        }
        string formatForPrint()
        {
            return "\""+getName()+"\""+" "+"by"+" "+getArtist()+" "+"("+getAlbum()+") "+"- "+to_string(numPlays)+" plays "+"[#"+to_string(identifier)+"]";
        }
        string formatForAutogen()
        {
            return "\""+getName()+"\""+" by "+getArtist()+" "+"("+getAlbum()+")";
        }
        string printAssist()
        {
            return "\""+getName()+"\""+" "+"by"+" "+getArtist()+" "+"("+getAlbum()+"), identified as #"+to_string(identifier);
        }
        string to_string(int number);
};

#endif // SONGWRAPPER_H
