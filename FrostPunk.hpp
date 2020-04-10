#include <vector>
#include <random>

class Building {
public:
    virtual void Work() = 0;
};

enum class BuildingTypes {
    Heater,
    HuntersHut
};

class City {
public:
    City(const City&) = delete;
    void operator=(const City&) = delete;

    static City& GetInstance();
    void PrintInfo();
    void NextTurn();
    void AddHeat(int);
    void AddFood(int);
    bool IsAlive();
private:
    City() {}

    std::vector<Building*> buildings;
    std::mt19937 rand;
    int overallHeat = 100;
    int population = 15;
    int overallFood = 50;
    int frost = 5;
    int daysPassed = 0;
};


class Heater : public Building {
public:
    void Work();
};

class HuntersHut : public Building {
public:
    void Work();
};

class Factory {
public:
    static Building* build(BuildingTypes type);
};

