#include "Library.h"

Library::~Library()
{
    //destructor deletes all pointers in map by iterating over it
    unordered_map<unsigned int,SongWrapper*>::iterator it;
    for (it=masterList.begin(); it!=masterList.end(); it++)
    {
        delete it->second;
    }
}

//A check is done to see if the potential song already exists, usually done in O(1) due to the 2nd helper map.
//If it does not already contain the song, new is used to create a new songwrapper object which is filled with
//the passed arguments. The data is updated in both the masterlist and helper maps. Next position is updated
bool Library::addToList(string name, string artist, string album)
{
    if (checkContainsSong(name,artist,album)) {return false;}
    SongWrapper * maker;
    maker = new SongWrapper(name, artist, album);
    maker -> setID(nextPosition);
    masterList[nextPosition]=maker;
    masterListHelper[name+artist+album]=nextPosition;
    nextPosition++;
    return true;
}

//Direct add function allows songwrappers to be created and added with an already existing ID, used by load function.
void Library::directAdd(string name, string artist, string album, int plays, int id)
{
    SongWrapper * maker;
    maker = new SongWrapper(name, artist, album);
    maker->setID(id);
    for(int i=0; i<plays; i++)
    {
        maker->incrementPlays();
    }
    masterList[id]=maker;
    masterListHelper[name+artist+album]=id;
}

//If the map contains the int key, the wrapper pointer is deleted from both maps and then the key is erased
bool Library::removeFromList(unsigned int target)
{
    if (!checkContainsKey(target)) {return false;}
    masterListHelper.erase(masterList[target]->FullDetails());
    delete masterList[target];
    masterList[target]=NULL;
    masterList.erase(target);
    return true;
}

//Map's values are all transferred to a vector and then based on the given criteria, the vector is sorted appropriately.
//The vector is then outputted by calling each wrapper's format function.
void Library::displayList(string criteria)
{
    vector<SongWrapper*> temp;
    fillVector(temp);
    if (criteria=="NAME" or criteria=="name")
    {
        sortName(temp);
    }
    else if (criteria=="ARTIST" or criteria=="artist")
    {
        sortArtist(temp);
    }
    else if (criteria=="ALBUM" or criteria=="album")
    {
        sortAlbum(temp);
    }
    else if (criteria=="PLAYS" or criteria=="plays")
    {
        sortPlays(temp);
    }
    for (int i=0; i<temp.size(); i++)
    {
        cout << i+1 <<". "<<temp[i]->formatForPrint() << endl;
    }
}

//A songwrapper's int numplays is increased by the user's specified number
bool Library::playSong(unsigned int identifier, unsigned int timesPlay)
{
    if (!checkContainsKey(identifier)) {return false;}
    if (timesPlay < 0) {return false;}
    for (int i=1; i<=timesPlay; i++)
    {
        masterList[identifier] -> incrementPlays();
    }
    return true;
}

SongWrapper* Library::getSong(unsigned int identifier)
{
    if (checkContainsKey(identifier)) {return masterList[identifier];}
}

bool Library::checkContainsSong(string name, string artist, string album)
{
    unordered_map<string, unsigned int>::iterator it=masterListHelper.find(name+artist+album);
    if (it==masterListHelper.end()) {return false;}
    else {return true;}
}

bool Library::checkContainsKey(unsigned int pos)
{
    unordered_map<unsigned int,SongWrapper*>::iterator it=masterList.find(pos);
    if (it==masterList.end()) {return false;}
    else {return true;}
}

void Library::fillVector(vector<SongWrapper*>& temp)
{
    unordered_map<unsigned int,SongWrapper*>::iterator it;
    for (it=masterList.begin(); it!=masterList.end(); it++)
    {
        temp.push_back(it->second);
    }
}

//Remaining functions all use the STL sort function to sort a given vector of songwrapper pointers
//based on a given criteria

bool Library::sortName(vector<SongWrapper*>& temp)
{
    sort(temp.begin(), temp.end(), [](SongWrapper*first, SongWrapper*second)
    {return first->getName() < second->getName();});
}

bool Library::sortArtist(vector<SongWrapper*>& temp)
{
    sort(temp.begin(), temp.end(), [](SongWrapper*first, SongWrapper*second)
    {return first->getArtist() < second->getArtist();});
}

bool Library::sortAlbum(vector<SongWrapper*>& temp)
{
    sort(temp.begin(), temp.end(), [](SongWrapper*first, SongWrapper*second)
    {return first->getAlbum() < second->getAlbum();});
}

bool Library::sortPlays(vector<SongWrapper*>&temp)
{
    sort(temp.begin(), temp.end(), [](SongWrapper*first, SongWrapper*second)
    {return first->getNumberPlays() > second->getNumberPlays();});
}
