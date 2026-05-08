#pragma once
#include "Player.h"

class Thief : public Player
{
public:
	Thief(std::string name, int* stat, int level = 1, int exp = 0, int maxExp = 100);		// 생성자
    int attack(Monster* monster) override;
    void attack() override;
};
