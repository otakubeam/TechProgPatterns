#include <vector>
#include <random>
#include <deque>
#include <set>

class Building {
public:
    void Perform();
    virtual void Work() = 0;
    void (*Decorator)() = nullptr;
    bool IsWorking() const;
    void SwitchState();
private:
    bool isWorking = true;
};

enum class BuildingTypes {
    Heater,
    HuntersHut
};

class CompositeNode {
public:
    CompositeNode() = default;
    CompositeNode(Building*);
    void SwitchState();
    void Add(CompositeNode*);
    void Remove(CompositeNode*);
    void PrintInfo() const;
private:
    Building* structure = nullptr;
    std::set<CompositeNode*> children;
};

class WolfPack {
public:
    void Load();
    void Act();
private:
    int state = 0;
    bool broken = false;
    std::vector<void (*)()> actions;
};

void AttackHeaters();
void AttackHunters();

class City {
public:
    City(const City&) = delete;
    void operator=(const City&) = delete;

    static City& GetInstance();
    void PrintInfo();
    void NextTurn();
    void AddHeat(int);
    void AddFood(int);
    int GetPopulation();
    int GetHeat();
    int GetFood();
    bool IsAlive();
private:
    City() {}

    std::vector<CompositeNode*> buildingsStructure;
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

