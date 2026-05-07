#include "Potion.h"
#include "Player.h"
#include <iostream>
#include <algorithm>

using namespace std;

// 생성자 구현
Potion::Potion(string name, string effectName, int effectValue, int price, int count) : Item(name, count) {
    this->effectName = effectName;
    this->effectValue = effectValue;
    this->price = price;
}

// useItem() 메서드 구현
// 잔여 아이템이 없을 경우 true 반환
bool Potion::useItem(Player* player) {
    int currentStat = (effectName == "HP") ? player->getHp() : player->getMp();

    cout << "* " << name << " used! " << effectName << " restored by " << effectValue << " (" << currentStat << " -> ";
    if (effectName == "HP") {
        player->setHp(min(currentStat + effectValue, player->getMaxHp()));
        currentStat = player->getHp(); // 업데이트된 수치 반영
    }
    else {
        player->setMp(currentStat + effectValue);
        currentStat = player->getMp();
    }

    cout << currentStat << ")" << endl << endl;

    return (--count <= 0);
}
