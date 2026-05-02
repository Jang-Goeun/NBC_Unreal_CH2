#pragma once
#include <string>

class Player {
protected:
	std::string name, job;
	int level, hp, mp, power, defense, hpPotion, mpPotion;

public:
	Player(std::string name, int* stat, int level = 1, int hpPotion = 5, int mpPotion = 5);		// 생성자
	virtual ~Player() {}								// 가상 소멸자

	// getter
	std::string getName() { return this->name; }
	std::string getJob() { return this->job; }
	int getLevel() { return this->level; }
	int getHp() { return this->hp; }
	int getMp() { return this->mp; }
	int getPower() { return this->power; }
	int getDefense() { return this->defense; }
	int getHpPotion() { return this->hpPotion; }
	int getMpPotion() { return this->mpPotion; }

	// setter 
	void setName(std::string name) { this->name = name; }
	void setJob(std::string job) { this->job = job; }
	void setLevel(int level) { this->level = level; }
	void setHp(int hp) { this->hp = hp; }
	void setMp(int mp) { this->mp = mp; }
	void setPower(int power) { this->power = power; }
	void setDefense(int defense) { this->defense = defense; }
	void setHpPotion(int hpPotion) { this->hpPotion = hpPotion; }
	void setMpPotion(int mpPotion) { this->mpPotion = mpPotion; }


	void printPlayerStatus();							// 상태 출력 메서드
	virtual void attack() = 0;							// 순수 가상 함수(공격)
	void upgradeCharacter(Player* player);              // 플레이어 능력치 업그레이드 메서드
};