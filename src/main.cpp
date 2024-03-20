
#include "../include/G_main.hpp"
#include "../include/Config.hpp"

int main() {
    Config conf = Config();
    G_main::g_main(conf);

    return 0;
}