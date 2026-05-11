#include "Orc.h"
#include "Player.h"
#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * @brief 생성자 구현
 */
Orc::Orc(string name, string attackComment, string dropItemName, int dropItemPrice, int hp, int power, int defense, int expReward) : Monster(name, attackComment, dropItemName, dropItemPrice, hp, power, defense, expReward)
{
    this->name = name;
    this->attackComment = attackComment;
    this->dropItemName = dropItemName;
    this->dropItemPrice = dropItemPrice;
    this->hp = hp;
    this->power = power;
    this->defense = defense;
    this->expReward = expReward;
}

/*
 * @brief attack() 메서드 구현
 */
int Orc::attack(Player* player)
{
    int damage = power - player->getDefense();
    int minDamage = (power * 0.1) + (rand() % 4);

    if (damage < minDamage) { damage = minDamage; }

    cout << "[" << name << "] " << attackComment << " -> " << damage << " damage to " << player->getName() << "!" << endl;

    return damage;
}
