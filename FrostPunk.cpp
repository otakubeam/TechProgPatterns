#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include "FrostPunk.hpp"

void Building::SwitchState() {
    isWorking = !isWorking;
}

bool Building::IsWorking() const {
    return isWorking;
}

Building* Factory::build(BuildingTypes type) {
    switch (type) {
    case BuildingTypes::Heater:
        return new Heater;
    case BuildingTypes::HuntersHut:
        return new HuntersHut;
    }
}

CompositeNode::CompositeNode(Building* a) : structure(a) {}

void CompositeNode::SwitchState() {
    if (structure != nullptr) {
        structure->SwitchState();
    } else {
        for (auto node : children) {
            node->SwitchState();
        }
    }
}

void CompositeNode::Add(CompositeNode* ptr) {
    children.insert(ptr);
}

void CompositeNode::Remove(CompositeNode* ptr) {
    children.erase(ptr);
}

void CompositeNode::PrintInfo() const {
    std::cout << this << ": { ";
    for (auto node : children) {
        node->PrintInfo();
        std::cout << ", ";
    }
    std::cout << '}';
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
    overallHeat -= frost;

    if (overallFood <= population) {
        population = overallFood;
        overallFood = 0;
    } else {
        overallFood -= population;
        if (overallHeat >= population) {
            population += population / 20;
        }
    }


    if (overallHeat <= 0 || population <= 0) {
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
    CompositeNode* node = new CompositeNode(buildings.back());
    buildingsStructure.push_back(node);

    if (buildingsStructure.size() > 10) {
        while (buildingsStructure.size() != 1) {
            buildingsStructure[0]->Add(buildingsStructure.back());
            buildingsStructure.pop_back();
        }
        buildingsStructure[0]->PrintInfo();
    }

    for (int i = 0; i < buildings.size(); i++) {
        if (buildings[i]->IsWorking()) {
            buildings[i]->Perform();
        }
    }
}

void WolfPack::Load() {
    char a;
    std::cout << "Enter a series of 1 and 0, followed by 'b'" << std::endl;
    while (std::cin >> a) {
        if (a == 'b') break;
        if (a == '1') {
            actions.push_back(&AttackHeaters);
        } else {
            actions.push_back(&AttackHunters);
        }
    }
}

void WolfPack::Act() {
    if (state < actions.size() && !broken) {
        actions[state]();
        int t = rand();
        broken = (t % 100) > 20 ? false : true;
        state++;
    }
}

void AttackHeaters() {
    std::cout << "Wolfs attack heaters" << std::endl;
    City::GetInstance().AddHeat(-10);
}

void AttackHunters() {
    std::cout << "Wolfs attack hunters" << std::endl;
    City::GetInstance().AddHeat(-5);
}

void City::AddHeat(int dif) {
    overallHeat += dif;
}

void City::AddFood(int dif) {
    overallFood += dif;
}

int City::GetPopulation() {
    return population;
}

int City::GetHeat() {
    return overallHeat;
}

int City::GetFood() {
    return overallFood;
}

bool City::IsAlive() {
    return population > 0;
}

void Building::Perform() {
    if (Decorator != nullptr) {
        (*Decorator)();
    }
    Work();
}

void Heater::Work() {
    City::GetInstance().AddHeat(4);
}

void Diet() {
    City::GetInstance().AddFood(1);
}

void HuntersHut::Work() {
    int forage = rand() % 8;
    std::cout << "Hunters return with " << forage << " rations of food\n";
    City::GetInstance().AddFood(forage);
}

