#include "Slime.h"
#include "Player.h"
#include <iostream>

using namespace std;

// 생성자 구현
Slime::Slime(string name, string dropItemName, int dropItemPrice, int hp, int power, int defense, int expReward) : Monster(name, dropItemName, dropItemPrice, hp, power, defense, expReward) {
    this->name = name;
    this->dropItemName = dropItemName;
    this->dropItemPrice = dropItemPrice;
    this->hp = hp;
    this->power = power;
    this->defense = defense;
    this->expReward = expReward;
}

// attack() 메서드 구현
void Slime::attack(Player* player) {
    cout << "Throws poisoned daggers with lightning speed!" << endl;
    cout << power << " damage to " << player->getName() << endl;
}
