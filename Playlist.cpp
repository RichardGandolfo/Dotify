#include "Playlist.h"
#include <sstream>

//Helper converts an int to string for print formatting
string Playlist::to_string(int number)
{
    string result;
    ostringstream convert;
    convert << number;
    result=convert.str();
    return result;
}

//If a songwrapper with the same ID number exists, it will not be added. Otherwise, both maps create a new key with the given
//data and are assigned a pointer for the main subset, and subsetHelper takes an ID to help provide constant access time.
bool Playlist::addToPlaylist(SongWrapper*temp)
{
    if (containsSong(temp->getID())) {return false;}
    subset[nextPosition]=temp;
    subsetHelper[subset[nextPosition]->getID()]=nextPosition;
    nextPosition++;
    return true;
}

//If a playlist contains a songwrapper pointer with the same ID as the specified, its key is erased but the value is not deleted
//since it may still be used in the library/
bool Playlist::removeFromPlaylist(int identifier)
{
    if (!containsSong(identifier)) {return false;}
    subsetHelper.erase(identifier);
    map<unsigned int, SongWrapper*>::iterator it;
    for (it=subset.begin(); it!=subset.end(); it++)
    {
        if (it->second->getID()==identifier)
        {
            subset.erase(it->first);
            break;
        }
    }
    return true;
}

//All songs contained in the map of the playlist are printed by having the wrapper in each position call its formatForPrint
void Playlist::printSongs()
{
    int i=1;
    map<unsigned int, SongWrapper*>::iterator it;
    for (it=subset.begin(); it!=subset.end(); it++)
    {
        cout<< i <<". "<<it->second->formatForPrint()<<endl;
        i++;
    }
}

//The 2 remaining helper functions are used to find if a key exists in the map, based on order number in the
//playlist based on order number for the first function and ID # for the second function

bool Playlist::containsOrder(int order)
{
    map<unsigned int, SongWrapper*>::iterator it = subset.find(order);
    if (it == subset.end()) {return false;}
    else {return true;}
}

bool Playlist::containsSong(int identifier)
{
    unordered_map<unsigned int, unsigned int>::iterator it = subsetHelper.find(identifier);
    if (it==subsetHelper.end()) {return false;}
    return true;
}
