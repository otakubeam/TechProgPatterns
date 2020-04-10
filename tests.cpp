#include <iostream>
#include <string>
#include <typeinfo>
#include "FrostPunk.hpp"

// проверяем, что фабрика делает то, что нужно
void TestFactory() {
    bool failed = false;
    if(typeid(*(Factory::build(BuildingTypes::Heater))) != typeid(Heater)) {
        std::cout << "TestFactory Heater fail" << std::endl;
        failed = true;
    }

    if (typeid(*(Factory::build(BuildingTypes::HuntersHut))) != typeid(HuntersHut)) {
        std::cout << "TestFactory HuntersHut fail" << std::endl;
        failed = true;
    }

    if (!failed) {
        std::cout << "TestFactory OK" << std::endl;
    }
}


void TestCity() {
    bool failed = false;


    int beforeAdding = City::GetInstance().GetFood();
    City::GetInstance().AddFood(50);
    if (beforeAdding + 50 != City::GetInstance().GetFood()) {
        std::cout << "TestCity GetFood fail" << std::endl;
        failed = true;
    }

    int prevFood = City::GetInstance().GetFood();
    int nextFoodExprected = prevFood - City::GetInstance().GetPopulation();
    City::GetInstance().NextTurn();
    if (City::GetInstance().GetFood() != nextFoodExprected) {
        std::cout << "TestCity NextTurnFood fail" << std::endl;
        failed = true;
    }

    Heater h;
    int prevHeat = City::GetInstance().GetHeat();
    h.Work();
    if (prevHeat + 2 != City::GetInstance().GetHeat()) {
        std::cout << "TestCity Heater fail" << std::endl;
        failed = true;
    }

    if (!failed) {
        std::cout << "TestCity OK" << std::endl;
    }
}


int main() {
    TestFactory();
    TestCity();

    return 0;
}
