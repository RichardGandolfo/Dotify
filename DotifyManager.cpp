#include "DotifyManager.h"

//Function determines if a playlist exists based onthe name key provided using an iterator
bool DotifyManager::containsPlaylist(string name)
{
    unordered_map<string, Playlist>::iterator it = allPlaylists.find(name);
    if (it==allPlaylists.end()) {return false;}
    return true;
}

//Given a string, a temporary Playlist object is filled with the string's data and is added tp the map
bool DotifyManager::createNewPlaylist(string name)
{
    Playlist temp;
    temp.renamePlaylist(name);
    allPlaylists[name]=temp;
    return true;
}

//Given a string, a playlist that has that key is removed from the map
bool DotifyManager::removeAPlaylist(string title)
{
    allPlaylists.erase(title);
    return true;
}

//A new key with the new name is created and takes the old playlist object as its value, the old one is erased from the map
//Both maps are updated
bool DotifyManager::renameAPlaylist(string oldTitle, string newTitle)
{
    allPlaylists[newTitle]=allPlaylists[oldTitle];
    allPlaylists[newTitle].renamePlaylist(newTitle);
    allPlaylists.erase(oldTitle);
    return true;
}

//Playlist with the key of the string adds a songwrapper pointer to its underlying data structure
bool DotifyManager::addSongToPlaylist(string name, int identifier)
{
    allPlaylists[name].addToPlaylist(allSongs.getSong(identifier));
    return true;
}

//Given a name, the value of that name key removed the songwrapper pointer with the given ID from its data structure
bool DotifyManager::removeSongFromPlaylist(string name, int identifier)
{
    allPlaylists[name].removeFromPlaylist(identifier);
    return true;
}

//Rating of playlist with that name key is changed to the given int
bool DotifyManager::changePlaylistRating(string name, int rating)
{
    allPlaylists[name].updateRating(rating);
    return true;
}

//All songs in a given playlist are printed
void DotifyManager::printSongsInPlaylist(string name)
{
    allPlaylists[name].printSongs();
}

//All existing playlists are printed in highest rated order
void DotifyManager::printPlaylists()
{
    vector<Playlist> temp;
    fillVector(temp);
    sortPlaylists(temp);
    for (int i=0; i<temp.size(); i++)
    {
        cout <<i+1<<". "<<temp[i].formatPlaylistInfo() <<endl;
    }
}

//A song with the given ID # is taken out of the library and all playlists that contain it, names of playlists that had the song
//removed are stored in a vector for printing
bool DotifyManager::removeSongFromAll(int identifier)
{
    vector<string> removedPlaylists;
    unordered_map<string, Playlist>::iterator it;
    for (it=allPlaylists.begin(); it!=allPlaylists.end(); it++)
    {
        if(it->second.containsSong(identifier))
        {
            removedPlaylists.push_back("\""+it->first+"\"");
            it->second.removeFromPlaylist(identifier);
        }
    }

    if(!removedPlaylists.empty())
    {
        cout <<allSongs.getSong(identifier)->printAssist()<<", has been removed successfully from your library and from playlists "
        <<makeListRemovedPlaylists(removedPlaylists)<<endl;
    }
    else
    {
            cout <<allSongs.getSong(identifier)->printAssist()<<", has been removed successfully from your library."<<endl;
    }
    allSongs.removeFromList(identifier);
    return true;
}

bool DotifyManager::playSong(int identifier, int timesToPlay)
{
    return allSongs.playSong(identifier, timesToPlay);
}

void DotifyManager::printLibrary(string criteria)
{
    allSongs.displayList(criteria);
}

//Based on input, a playlist is created with all songs that have the same name as the input
bool DotifyManager::autogenerateName(string query)
{
    createNewPlaylist(query);
    for (int i=1; i<allSongs.getNext(); i++)
    {
        if (allSongs.checkContainsKey(i))
        {
            if (allSongs.getSong(i)->getName()==query)
            {
                allPlaylists[query].addToPlaylist(allSongs.getSong(i));
            }
        }
    }
}

//Based on input, a playlist is created with all songs that have the same artist as the input
bool DotifyManager::autogenerateArtist(string query)
{
    createNewPlaylist(query);
    for (int i=1; i<allSongs.getNext(); i++)
    {
        if (allSongs.checkContainsKey(i))
        {
            if (allSongs.getSong(i)->getArtist()==query)
            {
                allPlaylists[query].addToPlaylist(allSongs.getSong(i));
            }
        }
    }
}

//Based on input, a playlist is created with all songs that have the same album as the input
bool DotifyManager::autogenerateAlbum(string query)
{
    createNewPlaylist(query);
    for (int i=1; i<allSongs.getNext(); i++)
    {
        if (allSongs.checkContainsKey(i))
        {
            if (allSongs.getSong(i)->getAlbum()==query)
            {
                allPlaylists[query].addToPlaylist(allSongs.getSong(i));
            }
        }
    }
}

//The top 15 played songs are found and then 5 are randomly selected by using the shuffle function of a vector.
//Then a function to find similar songs is called on each of the 5 in the vector to compile one playlist.
bool DotifyManager::autogenerateMagic()
{
   createNewPlaylist("AUTOGENERATED");
   vector<SongWrapper*> temp;
   fillVector(temp);
   sortByPlays(temp);
   if (temp.size()>5) {random_shuffle(temp.begin(), temp.end());}
   for (int i=0; i<temp.size(); i++)
   {
       if(i > 4) {break;}
       cout << temp[i]->formatForAutogen()<<". ";
       findSimilarSongs(temp[i]);
   }
}

//All songs in the library are written out to a file of the specified name using an ofstream by calling each individual
//SongWrapper pointer's format function
void DotifyManager::exportLibrary(string file)
{
    ofstream librarysaver;
    librarysaver.open(file);
    for (int i=1; i<allSongs.getNext(); i++)
    {
        if (allSongs.checkContainsKey(i))
        {
            librarysaver << allSongs.getSong(i)->formatForLibrary() << endl;
        }
    }
    librarysaver.close();
}

//Same logic as exportLibrary
void DotifyManager::exportPlaylists(string file)
{
    ofstream playlistsaver;
    playlistsaver.open(file);
    unordered_map<string, Playlist>::iterator it;
    for (it=allPlaylists.begin(); it!=allPlaylists.end(); it++)
    {
        playlistsaver << it->first << "|" << it->second.getRating() << "|" << it->second.getNumberOfSongs() << endl;
        for (int i=1; i<it->second.getNext(); i++)
        {
              if (it->second.containsOrder(i))
              {
                playlistsaver << it->second.getSong(i)->formatForPlaylist() << endl;
              }
        }
    }
    playlistsaver.close();
}

//Helper function for autogenerate by magic. A random number from 1 to 3 is chosen. Based on that number, similar songs are found in the
//library from one of the three criteria of name, artist, or album.
void DotifyManager::findSimilarSongs(SongWrapper*current)
{
    int x = (rand()%3)+1;
    int counter = 0;
    bool found = false;
    if (x==1)
    {
        cout << "Similar songs by NAME:" << endl;
        for (int i=1; i<allSongs.getNext(); i++)
        {
            if (counter==3) {break;}
            if (allSongs.checkContainsKey(i))
            {
                if (allSongs.getSong(i)->getName()==current->getName() and allSongs.getSong(i)->FullDetails() != current->FullDetails())
                {
                    cout << "   " << allSongs.getSong(i)->formatForAutogen() << endl;
                    allPlaylists["AUTOGENERATED"].addToPlaylist(allSongs.getSong(i));
                    counter++;
                }
            }
        }
        if (counter==0) {cout <<"   (No similar songs found)"<<endl;}
    }

    else if (x==2)
    {
        cout << "Similar songs by ARTIST:" << endl;
        for (int i=1; i<allSongs.getNext(); i++)
        {
            if (counter==3) {break;}
            if (allSongs.checkContainsKey(i))
            {
                if (allSongs.getSong(i)->getArtist()==current->getArtist() and allSongs.getSong(i)->FullDetails() != current->FullDetails())
                {
                    cout << "   " << allSongs.getSong(i)->formatForAutogen() << endl;
                    allPlaylists["AUTOGENERATED"].addToPlaylist(allSongs.getSong(i));
                    counter++;
                }
            }
        }
        if (counter==0) {cout <<"   (No similar songs found)"<<endl;}
    }

    else if (x==3)
    {
        cout << "Similar songs by ALBUM:" << endl;
        for (int i=1; i<allSongs.getNext(); i++)
        {
            if (counter==3) {break;}
            if (allSongs.checkContainsKey(i))
            {
                if (allSongs.getSong(i)->getAlbum()==current->getAlbum() and allSongs.getSong(i)->FullDetails() != current->FullDetails())
                {
                    cout << "   " << allSongs.getSong(i)->formatForAutogen() << endl;
                    allPlaylists["AUTOGENERATED"].addToPlaylist(allSongs.getSong(i));
                    counter++;
                }
            }
        }
        if (counter==0) {cout <<"   (No similar songs found)"<<endl;}
    }
}

//Helper function that stores the names of all the playlists a given song was removed from, assists in printing
string DotifyManager::makeListRemovedPlaylists(vector<string> removedPlaylists)
{
    string allRemoved="";
    for (int i=0; i<removedPlaylists.size(); i++)
    {
        if (i!=removedPlaylists.size()-1)
        {
            allRemoved+=removedPlaylists[i]+", ";
        }
        else
        {
            allRemoved+=removedPlaylists[i]+".";
        }
    }
    return allRemoved;
}

//Helper function that fills a vector with playlist objects by iterating over map
void DotifyManager::fillVector(vector<Playlist>& temp)
{
    unordered_map<string, Playlist>::iterator it;
    for (it=allPlaylists.begin(); it!=allPlaylists.end(); it++)
    {
        temp.push_back(it->second);
    }
}

//Helper function that fills a vector with SongWrapper pointers by iterating over library object
void DotifyManager::fillVector(vector<SongWrapper*>& temp)
{
    for (int i=1; i<allSongs.getNext(); i++)
    {
        if (allSongs.checkContainsKey(i))
        {
            temp.push_back(allSongs.getSong(i));
            if (temp.size()==15) {break;}
        }
    }
}

//Sorts vector from most to least song plays
void DotifyManager::sortByPlays(vector<SongWrapper*>& temp)
{
    sort(temp.begin(), temp.end(), [](SongWrapper*first, SongWrapper*second)
    {return first->getNumberPlays() > second->getNumberPlays();});
}

//Sorts vector based on highest rated songs first, and then alphabetically
void DotifyManager::sortPlaylists(vector<Playlist>& temp)
{
    sort(temp.begin(), temp.end(), [](Playlist first, Playlist second)
    {
        if(first.getRating()!=second.getRating())return first.getRating() > second.getRating();
        else {return first.getTitle()<second.getTitle();}
    });
}

//Executes based on how many arguments are provided via additional library/playlist files
void DotifyManager::load(int argc, char*argv[])
{
    ifstream LS, PS;

    //If only the executable, then nothing to load
    if(argc==1)
    {
        cout << "No library file provided." << endl;
        cout << "No playlists file provided." << endl;
        cout << endl;
    }
    else if (argc==2)
    {
        //checks if file is valid after opening
        LS.open(argv[1]);
        if (!LS.good())
        {
            cout << "Could not load library from "<<"\""<<argv[1]<<"\""<<". Skipping."<<endl;
        }
        else if (LS.good())
        {
            cout << "Loading library from "<<"\""<<argv[1]<<"\""<<"."<<endl;
        }
        cout << "No playlists file provided. " << endl;

        string full;
        int nextPosition=0;
        //breaks entire line into components of name artist album number of plays and ID #
        while (getline(LS,full))
        {
            string name="", artist="", album="", strplays="", strID="";
            int plays, id;
            int i=0;
            for (i; i<full.length(); i++)
            {
                if (full[i]=='|')
                {
                    i++;
                    break;
                }
                name+=full[i];
            }
            for (i; i<full.length(); i++)
            {
                if (full[i]=='|')
                {
                    i++;
                    break;
                }
                artist+=full[i];
            }
            for (i; i<full.length(); i++)
            {
                if (full[i]=='|')
                {
                    i++;
                    break;
                }
                album+=full[i];
            }
            for (i; i<full.length(); i++)
            {
                if (full[i]=='|')
                {
                    i++;
                    break;
                }
                strplays+=full[i];
            }
            for (i; i<full.length(); i++)
            {
                strID+=full[i];
            }

            istringstream(strplays) >> plays;
            istringstream(strID) >> id;
            //adds song to library
            allSongs.directAdd(name,artist,album,plays,id);
            //Tracks the biggest ID so a valid ID can be used when manually adding
            if (id>nextPosition){nextPosition=id;}
        }
        //updates highest ID #
        allSongs.changeNext(nextPosition+1);
    }
    else if (argc==3)
    {
        //checks if both library and playlists files are valid before proceeding
        LS.open(argv[1]);
        if (!LS.good())
        {
            cout << "Could not load library from "<<"\""<<argv[1]<<"\""<<". Skipping."<<endl;
        }
        else if (LS.good())
        {
            cout << "Loading library from "<<"\""<<argv[1]<<"\""<<"."<<endl;
        }
        PS.open(argv[2]);
        if (!PS.good())
        {
            cout << "Could not load playlists from "<<"\""<<argv[2]<<"\""<<". Skipping."<<endl;
        }
        else if (PS.good())
        {
            cout << "Loading playlists from "<<"\""<<argv[2]<<"\""<<"."<<endl;
        }

        string full;
        int nextPosition=0;
        //reads in whole line as string and then breaks into separate name artist album plays and ID #
        //by iterating over string and stopping at | characters
        while (getline(LS,full))
        {
            string name="", artist="", album="", strplays="", strID="";
            int plays, id;
            int i=0;
            for (i; i<full.length(); i++)
            {
                if (full[i]=='|')
                {
                    i++;
                    break;
                }
                name+=full[i];
            }
            for (i; i<full.length(); i++)
            {
                if (full[i]=='|')
                {
                    i++;
                    break;
                }
                artist+=full[i];
            }
            for (i; i<full.length(); i++)
            {
                if (full[i]=='|')
                {
                    i++;
                    break;
                }
                album+=full[i];
            }
            for (i; i<full.length(); i++)
            {
                if (full[i]=='|')
                {
                    i++;
                    break;
                }
                strplays+=full[i];
            }
            for (i; i<full.length(); i++)
            {
                strID+=full[i];
            }

            istringstream(strplays) >> plays;
            istringstream(strID) >> id;
            //adds each individual song to library
            allSongs.directAdd(name,artist,album,plays,id);
            if (id>nextPosition){nextPosition=id;}
        }
        allSongs.changeNext(nextPosition+1);

        string playlist;
        //Outer loops reads in and detects when a line describes a playlist rather than song,
        //then breaks up string accordingly based on | separator
        while (getline(PS, playlist))
        {
            string title="", strRating="", strnumSongs="";
            int i=0, rating, numSongs;
            for (i; i<playlist.length(); i++)
            {
                if (playlist[i]=='|')
                {
                    i++;
                    break;
                }
                title+=playlist[i];
            }
            for (i; i<playlist.length(); i++)
            {
                if (playlist[i]=='|')
                {
                    i++;
                    break;
                }
                strRating+=playlist[i];
            }
            for (i; i<playlist.length(); i++)
            {
                strnumSongs+=playlist[i];
            }
            istringstream(strRating) >> rating;
            istringstream(strnumSongs) >> numSongs;
            createNewPlaylist(title);
            changePlaylistRating(title,rating);
            string song;
            //This loop executes by reading in a number of lines equal to the number of songs
            //specified in playlist line, and breaks up each line into individual strings
            for (int x=0; x<numSongs; x++)
            {
                getline(PS,song);
                int j=0;
                string name="", artist="", album="";
                for (j; j<song.length(); j++)
                {
                    if (song[j]=='|')
                    {
                        j++;
                        break;
                    }
                    name+=song[j];
                }
                for (j; j<song.length(); j++)
                {
                    if (song[j]=='|')
                    {
                        j++;
                        break;
                    }
                    artist+=song[j];
                }
                for (j; j<song.length(); j++)
                {
                    album+=song[j];
                }
                //If library does not contain the current song, it can not be added to the playlist
                if (!allSongs.checkContainsSong(name,artist,album))
                {
                    cout << "Could not find song in library: " << "\"" << song << "\"" <<endl;
                }
                //If library contains the song, it's added to its respective playlist
                else if (allSongs.checkContainsSong(name,artist,album))
                {
                    addSongToPlaylist(title,allSongs.getNumberFromDetails(name,artist,album));
                }
            }
        }
    }
}
