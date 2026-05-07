#include "RewardItem.h"
#include "Player.h"
#include <iostream>

using namespace std;

// 생성자 구현
RewardItem::RewardItem(string name, string effectName, int effectValue, int price, int count) : Item(name, count) {
    this->effectName = effectName;
    this->effectValue = effectValue;
    this->price = price;
}

// useItem() 메서드 구현
void RewardItem::useItem(Player* player) {
    cout << "* " << name << " used! " << effectName << " restored by " << effectValue << " (" << player->getHp() << " -> ";
    player->setHp(player->getHp() + 50);
    cout << player->getHp() << ")" << endl << endl;
}
