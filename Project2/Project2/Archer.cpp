#include "Archer.h"
#include "Monster.h"
#include <iostream>

using namespace std;

/*
 * @brief 생성자
 */
Archer::Archer(string name, int* stat, int level, int exp, int maxExp) : Player(name, stat, level, exp, maxExp)
{
    this->job = "Archer";
    this->power += 30;  // 공격력 + 30
}

/*
 * @brief attack(Monster* monster) 메서드
 */
int Archer::attack(Monster* monster)
{
    int monsterDamage = (power - monster->getDefense()) / 3;
    monsterDamage = (monsterDamage <= 0) ? 1 : monsterDamage;    // 데미지가 0 이하이면 1로 고정

    cout << "[Archer] Shoots arrow! -> " << monsterDamage << " damage to " << monster->getName() << "! (x3)" << endl;

    return monsterDamage * 3;
}

/*
 * @brief attack() 메서드
 */
void Archer::attack()
{
    cout << "Shoots arrow!" << endl;
}
