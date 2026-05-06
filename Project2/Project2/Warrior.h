#pragma once
#include "Player.h"

class Warrior : public Player {
public:
	Warrior(std::string name, int* stat, int level = 1, int hpPotion = 5, int mpPotion = 5);		// 생성자
	void attack(Monster* monster) override;
	void attack() override;
};
