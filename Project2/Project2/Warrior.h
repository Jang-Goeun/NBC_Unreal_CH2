#pragma once
#include "Player.h"

class Warrior : public Player {
public:
	Warrior(std::string name, int* stat, int level = 1, int hpPotion = 5, int mpPotion = 5);		// »ý¼ºÀÚ
	void attack() override;
};
