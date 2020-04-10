#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include "FrostPunk.hpp"

Building* Factory::build(BuildingTypes type) {
    switch (type) {
    case BuildingTypes::Heater:
        return new Heater;
    case BuildingTypes::HuntersHut:
        return new HuntersHut;
    }
}

City& City::GetInstance() {
    static City instance;
    return instance;
}

void City::PrintInfo() {
    std::cout << "----------------------------------------\nThe city has survived for " << daysPassed << " days\n";
    std::cout << "Currently we have " << overallFood << " rations ";
    std::cout << "and " << population << " people\n";
    std::cout << "Warmth left: " << overallHeat << std::endl << std::endl;
}

void City::NextTurn() {

    if (overallFood <= population) {
        population = overallFood;
        overallFood = 0;
    } else {
        overallFood -= population;
        population += population / 10;
    }

    overallHeat -= frost;

    if (overallHeat <= 0 || population <= 0) {
        std::cout << "U r ded" << std::endl;
        return;
    }

    frost++;
    daysPassed++;
    PrintInfo();

    std::cout << "Wanna build?" << std::endl;
    std::cout << "0 for Heater, 1 for HuntersHut" << std::endl;
    int desiredBuildingIdx = 0;
    std::cin >> desiredBuildingIdx;
    BuildingTypes desiredBuilding;
    switch (desiredBuildingIdx) {
        case 0:
            desiredBuilding = BuildingTypes::Heater;
            break;
        case 1:
            desiredBuilding = BuildingTypes::HuntersHut;
            break;
        default:
            desiredBuilding = BuildingTypes::Heater;
    }
    Factory f;
    buildings.push_back(f.build(desiredBuilding));

    for (int i = 0; i < buildings.size(); i++) {
        buildings[i]->Work();
    }
}

void City::AddHeat(int dif) {
    overallHeat += dif;
}

void City::AddFood(int dif) {
    overallFood += dif;
}

bool City::IsAlive() {
    return population > 0;
}

void Heater::Work() {
    City::GetInstance().AddHeat(2);
}

void HuntersHut::Work() {
    int forage = rand() % 3;
    std::cout << "Hunters return with " << forage << " rations of food\n";
    City::GetInstance().AddFood(forage);
}

int main() {

    while (City::GetInstance().IsAlive()) {
        City::GetInstance().NextTurn();
    }

    return 0;
}
