#include "RewardItem.h"
#include "Player.h"
#include <iostream>

using namespace std;

/*
 * @brief 생성자
 */
RewardItem::RewardItem(string name, string effectName, int effectValue, int price, int count) : Item(name, count)
{
    this->effectName = effectName;
    this->effectValue = effectValue;
    this->price = price;
}

/*
 * @brief useItem()
 * @return 잔여 아이템이 없을 경우 true / 있으면 false
 */
bool RewardItem::useItem(Player* player)
{
    cout << "* " << name << " used! " << effectName << " restored by " << effectValue << " (" << player->getHp() << " -> ";
    player->setHp(min(player->getHp() + effectValue, player->getMaxHp()));
    cout << player->getHp() << ")" << endl << endl;
    --count;

    return (count <= 0);
}
