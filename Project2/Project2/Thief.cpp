#include "Thief.h"
#include "Monster.h"
#include <iostream>

using namespace std;

/*
 * @brief 생성자
 */
Thief::Thief(string name, int* stat, int level, int exp, int maxExp) : Player(name, stat, level, exp, maxExp)
{
    this->job = "Thief";
    this->power += 30;  // 공격력 + 30
}

/*
 * @brief attack(Monster* monster) 메서드
 */
int Thief::attack(Monster* monster)
{
    int monsterDamage = (power - monster->getDefense()) / 5;
    monsterDamage = (monsterDamage <= 0) ? 1 : monsterDamage;    // 데미지가 0 이하이면 1로 고정

    cout << "[Thief] Stabs dagger! -> " << monsterDamage << " damage to " << monster->getName() << "! (x5)" << endl;

    return monsterDamage * 5;
}

/*
 * @brief attack() 메서드
 */
void Thief::attack()
{
    cout << "Stabs dagger!" << endl;
}
