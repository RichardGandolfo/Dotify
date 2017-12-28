DOTIFY

Dotify is a program that allows users to store songs in a library and many playlists. Functionality allows users to play a song, create a subset of songs in a playlist, add/remove songs/playlists, load songs and playlists into the data structures at the time the program is ran, and export data into 2 different files: one for the library and the other for playlists. Songs with that have the same name, artist, and album are not allowed in the library. This program is divided into several classes which play a different role.

Song - the most basic class of the program
The song class is rudimentary in that it only contains 3 strings, one each for the name, artist, and album. They are set via the constructor and can be returned by their get functions. 

SongWrapper - controls the external data of a song object
This class contains an instance of a Song object and keeps track of the ID number of the song (later assigned by the library) and the number of times the song was played. It's also responsible for compiling relevant information about itself and its internal Song object into a single, convenient string which can assist in printing.

Library - the most universal class
Library uses two separate unordered maps as its underling data structure(s). Every song that exists in this program exists in library, and these "songs" are actually stored as SongWrapper pointers. It assigns each individual song a unique ID number which is incremented after every new song add, ensuring uniqueness. It can add, remove, and print songs. Since a second map is used to map a string containing name+artist+album to an ID #, the check to see if it already contains a song can be done in constant time.

Playlist - subset of library
Every song that exists in a playlist must exist in library, and it also stores SongWrapper pointers. Similar to the library class, two maps are used where one is responsible for keeping track of the songwrapper pointers and the other is useful in determining if a song already exists in the playlist, allowing fast checking time. Also like library, it can add, remove, and print its songs.

DotifyManager - the driving force of the app
This class contains 2 important private data members: an instance of a library object and an unordered map that maps strings (playlist names) to actual playlist objects. It is mainly responsible for all interactions that involve adding songs from library to the playlist map, removing from some or all data structure, exporting data to files, and loading data into the app.

Dotify - user interaction
This contains a single instance of a DotifyManager. It is responsible for user interaction by using its run function to constantly seek input from the user, so long as "EXIT" is not entered. If a valid command is entered, the appropriate helper function is called to carry it out.

COMPILING/RUNNING
Compile this program by using the makefile. The executable is called Dotify. Run it by entering ./Dotify in the command line. It also accepts 2 additional input files. These are optional, and one, both, or neither can be entered. The first argument is treated as the library file and the second is the playlist file. Run by doing the following:
./Dotify <library file> <playlist file>
