#pragma once
#include "Item.h"

class Potion : public Item {
public:
    Potion(std::string name, std::string effectName, int effectValue, int price, int count = 1);		// 생성자
    bool useItem(Player* player) override;
};

