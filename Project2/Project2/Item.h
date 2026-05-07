#pragma once
#include <string>

class Player;

class Item {
protected:
    std::string name;
    std::string effectName;
    int effectValue;
    int price;
    int count;

public:
    Item(std::string name, int count = 1);           // 생성자
    virtual ~Item() {}

    // getter
    std::string getName() { return this->name; }
    std::string getEffectName() { return this->effectName; }
    int getEffectValue() { return this->effectValue; }
    int getPrice() { return this->price; }
    int getCount() { return this->count; }

    // setter 
    void setName(std::string name) { this->name = name; }
    void setEffectName(std::string effectName) { this->effectName = effectName; }
    void settEffectValue(int peffectValuerice) { this->effectValue = effectValue; }
    void settPrice(int price) { this->price = price; }
    void setCount(int count) { this->count = count; }

    void addCount(int val);

    void printInfo();
    virtual bool useItem(Player* player) = 0;
};
