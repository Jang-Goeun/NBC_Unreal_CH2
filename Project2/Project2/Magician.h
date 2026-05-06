#pragma once
#include "Player.h"

class Magician : public Player {
public:
	Magician(std::string name, int* stat, int level = 1, int hpPotion = 5, int mpPotion = 5, int exp = 0, int maxExp = 100);		// 생성자
    int attack(Monster* monster) override;
    void attack() override;
};
