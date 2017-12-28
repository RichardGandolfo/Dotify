#include "SongWrapper.h"
#include <sstream>

//Helper function converts an int into a string to assist in print formatting.
string SongWrapper::to_string(int number)
{
    string result;
    ostringstream convert;
    convert << number;
    result=convert.str();
    return result;
}
