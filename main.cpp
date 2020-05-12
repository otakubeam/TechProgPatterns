#include "FrostPunk.hpp"
#include <iostream>

int main() {
    WolfPack w;
    w.Load();
    while (City::GetInstance().IsAlive()) {
        w.Act();
        City::GetInstance().NextTurn();
    }
    std::cout << "U r ded" << std::endl;

    return 0;
}
