#ifndef G_MAIN_HXX
#define G_MAIN_HXX

#include <fstream>      // Used for file input and output

#include "../include/Gui.hpp"
#include "../include/Config.hpp"


// header file for Gui.cpp
class G_main {
    public:
    static int g_main();
    static int g_main(Config& conf);
};

#endif // G_GMAIN_HXX
