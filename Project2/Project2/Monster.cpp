#include "Monster.h"
#include "Player.h"
#include <iostream>

using namespace std;

/*
 * @brief 생성자
 */
Monster::Monster(string name, string dropItemName, int dropItemPrice, int hp, int power, int defense, int expReward)
{
    this->name = name;
    this->dropItemName = dropItemName;
    this->dropItemPrice = dropItemPrice;
    this->hp = hp;
    this->power = power;
    this->defense = defense;
    this->expReward = expReward;
}
