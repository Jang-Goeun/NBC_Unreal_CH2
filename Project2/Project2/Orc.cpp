#include "Orc.h"
#include "Player.h"
#include <iostream>

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
    damage = (damage <= 0) ? 1 : damage;

    cout << "[" << name << "] " << attackComment << " -> " << damage << " damage to " << player->getName() << "!" << endl;

    return damage;
}
