#pragma once
#include "Player.h"

class Thief : public Player {
public:
	Thief(std::string name, int* stat, int level = 1, int hpPotion = 5, int mpPotion = 5);		// »ý¼ºÀÚ
	void attack() override;
};
