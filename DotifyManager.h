#ifndef DOTIFYMANAGER_H
#define DOTIFYMANAGER_H

#include "Library.h"
#include "Playlist.h"
#include <cstdlib>
#include <fstream>
#include <sstream>

class DotifyManager
{
    //Underlying data structures include a Library object which contains every song that's added and an unordered map
    //which maps strings, representing titles of playlists, to actual playlist objects.
    private:
        Library allSongs;
        unordered_map<string, Playlist> allPlaylists;

    //These functions perform tasks that coordinate the interactions between the unordered map and library objects.
    //Essentially, the main purpose of these member functions are to add songs to the library or playlist map, remove
    //songs from both the library and the playlist map or just the playlist, checking to see if a song or playlist exists in the
    //library or map, respectively, alter details about a playlist as well as alter data within that playlist, and print existing songs,
    //existing playlists, and all the songs within each of those playlists. The more complex functions are the 4 autogenerate
    //functions which detect songs within the library that match a given criteria and add them to a newly created playlist.
    //Another important function is export which writes out library and playlist data to files. The final and largest function is
    //load which contains necessary algorithms to add songs from up to 2 files to the library and playlists. All of the remaining
    //functions are helpers, called by the larger functions, that sort/print/return data as needed.
    public:
        bool containsPlaylist(string name);
        bool playlistContainsSong(string name, int id) {return allPlaylists[name].containsSong(id);}
        bool libraryContainsID(int id) {return allSongs.checkContainsKey(id);}
        bool libraryContainsSong(string name, string artist, string album) {return allSongs.checkContainsSong(name,artist,album);}
        bool addToLibrary(string name, string artist, string album) {return allSongs.addToList(name,artist,album);}
        SongWrapper* getFromLibrary(int id) {return allSongs.getSong(id);}
        int getSongID(string name, string artist, string album) {return allSongs.getNumberFromDetails(name,artist,album);}
        bool createNewPlaylist(string name);
        bool removeAPlaylist(string title);
        bool renameAPlaylist(string oldTitle, string newTitle);
        bool removeSongFromAll(int identifier);
        bool addSongToPlaylist(string name, int identifier);
        bool removeSongFromPlaylist(string name, int identifier);
        bool changePlaylistRating(string name, int rating);
        void printSongsInPlaylist(string name);
        bool playSong(int identifier, int timesToPlay);
        void printLibrary(string criteria);
        void printPlaylists();
        bool autogenerateName(string query);
        bool autogenerateArtist(string query);
        bool autogenerateAlbum(string query);
        bool autogenerateMagic();
        void exportLibrary(string file);
        void exportPlaylists(string file);
        int librarySize() {return allSongs.getNumberOfSongs();}
        int playlistSize(string title) {return allPlaylists[title].getNumberOfSongs();}
        bool noPlaylists() {return allPlaylists.empty();}
        void findSimilarSongs(SongWrapper*current);
        string makeListRemovedPlaylists(vector<string> removedPlaylists);
        void fillVector(vector<Playlist>& temp);
        void fillVector(vector<SongWrapper*>& temp);
        void sortByPlays(vector<SongWrapper*>& temp);
        void sortPlaylists(vector<Playlist>& temp);
        void load(int argc, char*argv[]);
};

#endif // DOTIFYMANAGER_H
