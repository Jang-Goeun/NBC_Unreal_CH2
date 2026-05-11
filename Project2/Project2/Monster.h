#pragma once
#include <string>

class Player;

class Monster
{
protected:
	std::string name, dropItemName, attackComment;
	int hp, power, defense, dropItemPrice, expReward;

public:
	// 생성자
	Monster(std::string name, std:: string attackComment, std::string dropItemName, int dropItemPrice, int hp = 30, int power = 20, int defense = 10, int expReward = 30);
	virtual ~Monster() {}								// 가상 소멸자
	
	// getter
	std::string getName() { return this->name; }
	std::string getAttackComment() { return this->attackComment; }
    std::string getDropItemName() { return this->dropItemName; }
	int getHp() { return this->hp; }
	int getPower() { return this->power; }
	int getDefense() { return this->defense; }
    int getDropItemPrice() { return this->dropItemPrice; }
    int getExpReward() { return this->expReward; }

	// setter
	void setName(std::string name) { this->name = name; }
    void setAttackComment(std::string attackComment) { this->attackComment = attackComment; }
	void setDropItemName(std::string dropItemName) { this->dropItemName = dropItemName; }
	void setHp(int hp) { this->hp = hp; }
	void setPower(int power) { this->power = power; }
	void setDefense(int defense) { this->defense = defense; }
	void setDropItemPrice(int dropItemPrice) { this->dropItemPrice = dropItemPrice; }
    void setExpReward(int expReward) { this->expReward = expReward; }

	virtual int attack(Player* player) = 0;							// 순수 가상 함수(공격)
};
