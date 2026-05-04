#pragma once
#include <string>
#include "Monster.h"

class Slime : public Monster {
public:
	Slime(std::string name, std::string dropItemName, int dropItemPrice, int hp = 30, int power = 20, int defense = 10);		// »ý¼ºÀÚ
	void attack(Player* player) override;
};
