
#include "../include/G_main.hpp"
#include "../lib/Util.h"

int main() {
    int typingSpeed = Util::DEFAULF_SPEED, countdown = Util::DEFAULT_COUNTDOWN;
    G_main::g_main(typingSpeed, countdown);

    return 0;
}