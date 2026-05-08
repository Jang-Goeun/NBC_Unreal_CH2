#pragma once
#include <string>
#include "Monster.h"

class Slime : public Monster
{
public:
	Slime(std::string name, std::string dropItemName, int dropItemPrice, int hp = 30, int power = 20, int defense = 10, int expReward = 30);		// 생성자
	int attack(Player* player) override;
};
