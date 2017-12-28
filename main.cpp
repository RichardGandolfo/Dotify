#include <iostream>
#include "Dotify.h"

//Instance of Dotify that calls its load function first and then executes run until the user ends the program.
int main(int argc, char*argv[])
{
   Dotify app;
   app.load(argc, argv);
   app.run();
}
