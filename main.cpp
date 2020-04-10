#include "FrostPunk.hpp"

int main() {

    while (City::GetInstance().IsAlive()) {
        City::GetInstance().NextTurn();
    }

    return 0;
}
