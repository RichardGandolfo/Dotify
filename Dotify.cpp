#include "Dotify.h"

//Loop that keeps running as long as user does not enter EXIT. If a command is valid, the appropriate helper function
//is called by run.
void Dotify::run()
{
    string input;
    while (getline(cin,input) and input!="EXIT")
    {
        if (input == "AS")
        {
            AS();
        }
        else if (input == "RS")
        {
            RS();
        }
        else if (input == "PLY")
        {
            PLY();
        }
        else if (input == "LB")
        {
            LB();
        }
        else if (input == "AP")//
        {
            AP();
        }
        else if (input == "RP")//
        {
            RP();
        }
        else if (input == "RN")//
        {
            RN();
        }
        else if (input == "ASP")
        {
            ASP();
        }
        else if (input == "RSP")
        {
            RSP();
        }
        else if (input == "RT")
        {
            RT();
        }
        else if (input == "PL")
        {
            PL();
        }
        else if (input == "PLS")
        {
            PLS();
        }
        else if (input == "AG")
        {
            AG();
        }
        else if (input == "EXP")
        {
            EXP();
        }
        else if (input == "HELP")
        {
            HELP();
        }
        else
        {
            cout << "Invalid input" <<endl<<endl;
        }
    }
    cout << "You have exited Dotify." << endl;
}

//Reads in 3 strings which are checked by DotifyManager object to see if song already exists. If it does not, it's added
//to the library. Appropriate message is outputted regarding the input.
void Dotify::AS()
{
    string name, artist, album;
    cout << "What is the name of the song you'd like to purchase?" << endl;
    getline(cin, name);
    cout << "Who is the artist?" << endl;
    getline(cin, artist);
    cout << "Which album does it belong to?" << endl;
    getline(cin, album);

    if (core.libraryContainsSong(name, artist, album))
    {
        cout << core.getFromLibrary(core.getSongID(name,artist,album))->printAssist()
        << ", already exists in your library." << endl;
        cout << endl;
    }
    else
    {
        core.addToLibrary(name, artist, album);
        cout << core.getFromLibrary(core.getSongID(name,artist,album))->printAssist()
        << ", purchased successfully to your library." << endl;
        cout << endl;
    }
}

//A songwrapper pointer is removed from the library and all playlists that contain the specified ID number, given the ID
//is valid. Error checking is performed in case a non int input is given for the ID by the user.
void Dotify::RS()
{
    int id;
    cout << "What is the identifier of the song you'd like to remove from your library?" << endl;
    cin >> id;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid input" << endl<<endl;
        return;
    }
    if (core.libraryContainsID(id))
    {
        core.removeSongFromAll(id);
        cout << endl;
    }
    else
    {
        cout << "No song with the identifier #"<<id<<" exists in your library." << endl << endl;
    }
    cin.ignore(256, '\n');
}

//A song is played by reading in 2 ints; the identifier and the number of times to play it. Error checking is done via
// cin.fail() in case a non int is entered. There are several issues that can arise with this function. If the ID is invalid,
//if the number of plays is negative, or if either of the ints get a non int input. In any case, the song is played 0 times if the
//number of plays is invalid.
void Dotify::PLY()
{
    int id, plays;
    cout << "What is the identifier of the song you'd like to listen to? " << endl;
    cin >> id;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid input" << endl<<endl;
        return;
    }

    if (!core.libraryContainsID(id))
        {cin.ignore(256,'\n'); cout << "No song with the identifier #"<<id<<" exists in your library." << endl << endl;}
    else
    {
        cout << "How many times would you like to play this song? " << endl;
        cin >> plays;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(256,'\n');
            cout << core.getFromLibrary(id)->printAssist() << ", played successfully 0 times "
            << "(" << core.getFromLibrary(id)->getNumberPlays() << " plays -> " << core.getFromLibrary(id)->getNumberPlays()
            <<" plays)." <<endl<<endl;

        }
        else if (plays <= 0)
        {
            cin.ignore(256,'\n');
            cout << core.getFromLibrary(id)->printAssist() << ", played successfully 0 times "
            << "(" << core.getFromLibrary(id)->getNumberPlays() << " plays -> " << core.getFromLibrary(id)->getNumberPlays()
            <<" plays)." <<endl<<endl;
        }
        else
        {
            cin.ignore(256,'\n');
            cout << core.getFromLibrary(id)->printAssist() << ", played successfully "<<plays<<" times "
            << "(" << core.getFromLibrary(id)->getNumberPlays() << " plays -> " << core.getFromLibrary(id)->getNumberPlays()+plays
            <<" plays)." <<endl<<endl;

            core.playSong(id, plays);
        }
    }
}

//Takes in a string that determines by which criteria the songs in the library will be printed, assuming the input is valid
void Dotify::LB()
{
    if (core.librarySize()==0) {cout << "You have no songs in your library."<<endl<<endl;}
    else
    {
        string category;
        cout << "What category should the songs be ordered by? (NAME/ARTIST/ALBUM/PLAYS)" << endl;
        getline(cin,category);
        if (category=="NAME" or category=="ARTIST" or category=="ALBUM" or category=="PLAYS")
        {
            core.printLibrary(category);
            cout << endl;
        }
        else
        {
            cout << "Invalid category"<<endl<<endl;
        }
    }
}

//A string is given by the user, and a playlist by that name is created if it does not already exist.
void Dotify::AP()
{
    string title;
    cout << "What is the title of the playlist you'd like to create?" << endl;
    getline(cin, title);
    if (core.containsPlaylist(title)) {cout << "\""<<title<<"\""<< " playlist already exists."<<endl<<endl;}
    else
    {
        core.createNewPlaylist(title);
        cout << "\""<<title<<"\""<< " playlist created successfully." << endl << endl;
    }
}

//The name of a playlist is specified as a string by the user and if it exists, it is removed. If not, an error is outputted.
void Dotify::RP()
{
    string title;
    cout << "What is the title of the playlist you'd like to remove?" << endl;
    getline(cin, title);
    if (!core.containsPlaylist(title)) {cout << "\""<<title<<"\""<< " playlist does not exist."<<endl<<endl;}
    else
    {
        core.removeAPlaylist(title);
        {cout << "\""<<title<<"\""<< " playlist removed successfully."<<endl<<endl;}
    }
}

//The name of a playlist is specified by the user. If it does not exist, the function ends. If it does exist, the user is prompted for
//another input. If that new input is not the name of an already existing playlist, the existing playlist is assigned that name.
void Dotify::RN()
{
    string title, newTitle;
    cout << "What is the title of the playlist you'd like to rename?" << endl;
    getline(cin, title);
    if (!core.containsPlaylist(title)) {cout << "\""<<title<<"\""<< " playlist does not exist."<<endl<<endl;}
    else
    {
        cout << "What is the new title that you'd like to rename it to?" << endl;
        getline(cin, newTitle);
        if (core.containsPlaylist(newTitle)) {cout << "\""<<newTitle<<"\""<< " playlist already exists."<<endl<<endl;}
        else
        {
            cout << "\""<<title<<"\""<<" renamed successfully to "<<"\""<<newTitle<<"\"." << endl << endl;
            core.renameAPlaylist(title, newTitle);
        }
    }
}

//A playlist name and id number is inputted by the number. If the string is not the name of an existing playlist, the program
//ends. If it is the name of one, the user is prompted for the ID # of a song. If the input for that is not valid, the function ends.
//If it's an int that is not assigned to an existing song, the function ends. If the int is the ID of an existing song, the song
//is added to the specified playlist.
void Dotify::ASP()
{
    string playlist; int id;
    cout << "What is the title of the playlist you'd like to add the song to?" << endl;
    getline(cin, playlist);
    if (!core.containsPlaylist(playlist)) {cout << "\""<<playlist<<"\""<< " playlist does not exist."<<endl<<endl;}
    else
    {
        cout << "What is the identifier of the song to add to the playlist?" << endl;
        cin >> id;
        cin.get();
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input" << endl<<endl;
            return;
        }
        if (!core.libraryContainsID(id)) {cout << "No song with identifier #"<<id<<" exists in your library."<<endl<<endl;}
        else if (core.playlistContainsSong(playlist,id))
        {
            cout << "\""<<playlist<<"\""
            <<" already contains "<<core.getFromLibrary(id)->printAssist() <<"."<<endl<<endl;
        }
        else
        {
            core.addSongToPlaylist(playlist,id);
            cout << core.getFromLibrary(id)->printAssist() <<", added successfully to playlist "<< "\""<<playlist<<"\"." <<endl<<endl;
        }
    }
}

//The name of a playlist and ID # of a song are given by the user. If both are valid inputs, the song with that ID # is removed
//from the specified playlist, but it's kept in the library.
void Dotify::RSP()
{
    string title; int id;
    cout << "What is the title of the playlist that you'd like to remove the the song from?" << endl;
    getline(cin,title);
    if (!core.containsPlaylist(title)) {cout << "\""<<title<<"\""<< " playlist does not exist."<<endl<<endl;}
    else
    {
        cout << "What is the identifier of the song to remove from the playlist?" << endl;
        cin >> id;
        cin.get();
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input" << endl<<endl;
            return;
        }
        if (!core.playlistContainsSong(title, id)) {cout << "No song with identifier #"<<id<<" exists in this playlist."<<endl<<endl;}
        else
        {
            core.removeSongFromPlaylist(title, id);
            cout << core.getFromLibrary(id)->printAssist() <<", removed successfully from playlist "<< "\""<<title<<"\"." <<endl<<endl;
        }
    }
}

//The name of a playlist is inputted by the user. If it exists, the user is asked for an rating between 1 and 5. If it's a
//valid rating, that playlist is assigned that rating.
void Dotify::RT()
{
    string title; int rating;
    cout << "What is the title of the playlist you'd like to rate?" << endl;
    getline(cin,title);
    if (!core.containsPlaylist(title)) {cout << "\""<<title<<"\""<< " playlist does not exist."<<endl<<endl;}
    else
    {
        cout << "What rating would you like to give this playlist? (1 to 5)" << endl;
        cin >> rating;
        cin.get();
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input" << endl<<endl;
            return;
        }
        if (rating <=0 or rating >5) {cout << "\""<<rating<<"\""<<" is not a valid rating."<<endl<<endl;}
        else
        {
            core.changePlaylistRating(title, rating);
            cout << "\""<<title<<"\""<< " playlist rated successfully as a "<<rating<<"."<<endl<<endl;
        }
    }
}

//A string is inputted and if it is valid, all of the songs within that playlist are displayed.
void Dotify::PL()
{
    string title;
    cout << "What is the title of the playlist that you'd like to display?" << endl;
    getline(cin,title);
    if (!core.containsPlaylist(title)) {cout << "\""<<title<<"\""<< " playlist does not exist."<<endl<<endl;}
    else
    {
        if(core.playlistSize(title)==0) {cout << "\""<<title<<"\""<<" playlist has no songs."<<endl<<endl;}
        else
        {
            core.printSongsInPlaylist(title);
            cout << endl;
        }
    }
}

//If there are existing playlists, they are displayed alongside their rating and number of songs they have.
void Dotify::PLS()
{
    if (core.noPlaylists()) {cout << "You have no playlists."<<endl;}
    else {core.printPlaylists();}
    cout << endl;
}

//First, the type of autogenerate is specified. If it is valid type, the name/artist/album by which a playlist is created ias asked.
//All songs matching that description are added to a newly created playlist.
void Dotify::AG()
{
    string category, query;
    cout << "What is the category you'd like to autogenerate a playlist with? (NAME/ARTIST/ALBUM/MAGIC)" << endl;
    getline(cin,category);
    if (category=="NAME")
    {
        cout << "What is the song name you'd like to autogenerate a playlist from?"<<endl;
        getline(cin, query);
        if (!core.containsPlaylist(query))
        {
            core.autogenerateName(query);
            cout << "\"" << query << "\"" << " playlist autogenerated successfully." << endl << endl;
        }
        else
        {
            cout << "\""<<query<<"\""<< " playlist already exists."<<endl<<endl;
        }
    }
    else if (category=="ARTIST")
    {
        cout << "What is the song artist you'd like to autogenerate a playlist from?"<<endl;
        getline(cin, query);
        if (!core.containsPlaylist(query))
        {
            core.autogenerateArtist(query);
            cout << "\"" << query << "\"" << " playlist autogenerated successfully." << endl << endl;
        }
        else
        {
            cout << "\""<<query<<"\""<< " playlist already exists."<<endl<<endl;
        }
    }
    else if (category=="ALBUM")
    {
        cout << "What is the song album you'd like to autogenerate a playlist with?"<<endl;
        getline(cin, query);
        if (!core.containsPlaylist(query))
        {
            core.autogenerateAlbum(query);
            cout << "\"" << query << "\"" << " playlist autogenerated successfully." << endl << endl;
        }
        else
        {
            cout << "\""<<query<<"\""<< " playlist already exists."<<endl<<endl;
        }
    }
    else if (category=="MAGIC")
    {
        if (!core.containsPlaylist("AUTOGENERATED"))
        {
            core.autogenerateMagic();
            cout << "\"" << "AUTOGENERATED" << "\"" << " playlist autogenerated successfully." << endl << endl;
        }
        else
        {
            cout << "\""<<"AUTOGENERATED"<<"\""<< " playlist already exists."<<endl<<endl;
        }
    }
    else
    {
        cout << "\""<<category<<"\""<<" is not a valid criterion to autogenerate a playlist with."<<endl<<endl;
    }
}

//All songs in the library and all playlist are written out to their respective files which the user specifies the names of
void Dotify::EXP()
{
    string library, playlist;
    cout << "What is the name of the file you'd like to export your library to?" << endl;
    getline(cin, library);
    cout << "What is the name of the file you'd like to export your playlists to?" << endl;
    getline(cin, playlist);
    core.exportLibrary(library);
    core.exportPlaylists(playlist);
    cout << "Library and playlists exported successfully!" <<endl<<endl;
}

//The help menu is displayed to the user
void Dotify::HELP()
{
    cout << "AS: Purchases a new song to your library" << endl;
    cout << "RS: Removes a specific song from your library" << endl;
    cout << "AP: Creates an empty playlist" << endl;
    cout << "RP: Removes a specific playlist" << endl;
    cout << "RN: Renames a specific playlist" << endl;
    cout << "AG: Autogenerates a playlist based on song name, artist, album, or magic" << endl;
    cout << "ASP: Adds a specific song from your library to a playlist" << endl;
    cout << "RSP: Removes a specific song from a playlist" << endl;
    cout << "LB: Displays all the songs in your library" << endl;
    cout << "PLS: Displays all the playlists by highest rating" << endl;
    cout << "PL: Displays all the songs in a specific playlist in the order added" << endl;
    cout << "RT: Rates a specific playlist from 1 to 5" << endl;
    cout << "PLY: Plays a specific song in your library a specified number of times" << endl;
    cout << "EXP: Exports the song library and playlists to files" << endl;
    cout << "HELP: Displays this help menu" << endl;
    cout << "EXIT: Exits the program" << endl<< endl;
}

//This calls core's load function to add songs to the library and playlists from given files(s)
void Dotify::load(int argc, char*argv[])
{
    core.load(argc, argv);
}
