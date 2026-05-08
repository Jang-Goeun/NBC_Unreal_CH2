#pragma once
#include <string>
#include <memory>

class Monster;
class Item;

class Player
{
protected:
	std::string name, job;
	int level, hp, mp, power, defense, exp, maxExp, maxHp;

public:
	Player(std::string name, int* stat, int level = 1, int exp = 0, int maxExp = 100, int maxHp = 100);		// 생성자
	virtual ~Player() {}								// 가상 소멸자

	// getter
	std::string getName() { return this->name; }
	std::string getJob() { return this->job; }
	int getLevel() { return this->level; }
	int getHp() { return this->hp; }
    int getMaxHp() { return this->maxHp; }
	int getMp() { return this->mp; }
	int getPower() { return this->power; }
	int getDefense() { return this->defense; }
    int getExp() { return this->exp; }
    int getMaxExp() { return this->maxExp; }

	// setter 
	void setName(std::string name) { this->name = name; }
	void setJob(std::string job) { this->job = job; }
	void setLevel(int level) { this->level = level; }
	void setHp(int hp) { this->hp = hp; }
    void setMaxHp(int maxHp) { this->maxHp = maxHp; }
	void setMp(int mp) { this->mp = mp; }
	void setPower(int power) { this->power = power; }
	void setDefense(int defense) { this->defense = defense; }
    void setExp(int exp) { this->exp = exp; }
    void setMaxExp(int maxExp) { this->maxExp = maxExp; }


	void printPlayerStatus();							// 상태 출력 메서드
	virtual int attack(Monster* monster) = 0;			// 순수 가상 함수(전투 공격)
	virtual void attack() = 0;							// 순수 가상 함수(공격 메시지)
    void upgradeCharacter(std::unique_ptr<Item>& hpPotion, std::unique_ptr<Item>& mpPotion);                            // 플레이어 능력치 업그레이드 메서드
};
