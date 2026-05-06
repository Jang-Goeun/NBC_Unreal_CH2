#include "Monster.h"
#include "Player.h"
#include <iostream>

using namespace std;

// 생성자 구현
Monster::Monster(string name, string dropItemName, int dropItemPrice, int hp, int power, int defense) {
    this->name = name;
    this->dropItemName = dropItemName;
    this->dropItemPrice = dropItemPrice;
    this->hp = hp;
    this->power = power;
    this->defense = defense;
}