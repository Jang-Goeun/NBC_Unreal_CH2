#pragma once
#include <string>

class Player;

class Monster {
protected:
	std::string name, dropItemName;
	int hp, power, defense, dropItemPrice;

public:
	// 생성자
	Monster(std::string name, std::string dropItemName, int dropItemPrice, int hp = 30, int power = 20, int defense = 10);
	virtual ~Monster() {}								// 가상 소멸자
	
	// getter
	std::string getName() { return this->name; }
	std::string getDropItemName() { return this->dropItemName; }
	int getHp() { return this->hp; }
	int getPower() { return this->power; }
	int getDefense() { return this->defense; }
	int getDropItemPrice() { return this->dropItemPrice; }

	// setter
	void setName(std::string name) { this->name = name; }
	void setDropItemName(std::string dropItemName) { this->dropItemName = dropItemName; }
	void setHp(int hp) { this->hp = hp; }
	void setPower(int power) { this->power = power; }
	void setDefense(int defense) { this->defense = defense; }
	void setDropItemPrice(int dropItemPrice) { this->dropItemPrice = dropItemPrice; }

	virtual void attack(Player* player) = 0;							// 순수 가상 함수(공격)
};