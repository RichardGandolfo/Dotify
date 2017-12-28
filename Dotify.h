#ifndef DOTIFY_H
#define DOTIFY_H

#include "DotifyManager.h"

//Outermost class which contains an instance of DotifyManager. Contains private helper functions where
//each corresponds to a valid command. They execute commands given by the user .
class Dotify
{
    private:
        DotifyManager core;
        void AS();
        void RS();
        void PLY();
        void LB();
        void AP();
        void RP();
        void RN();
        void ASP();
        void RSP();
        void RT();
        void PL();
        void PLS();
        void AG();
        void EXP();
        void HELP();

    public:
        //Run function executes the infinite loop which constantly reads in commands,
        //the user can end at any time. Load takes the arguments given to main which
        //add songs to the library and playlists from the specified files.
        void run();
        void load(int argc, char*argv[]);
};

#endif // DOTIFY_H
