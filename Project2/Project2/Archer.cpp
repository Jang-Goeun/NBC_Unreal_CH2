#include "Archer.h"
#include "Monster.h"
#include <iostream>

using namespace std;

// 생성자 구현
Archer::Archer(string name, int* stat, int level, int exp, int maxExp) : Player(name, stat, level, exp, maxExp) {
    this->job = "Archer";
    this->power += 30;  // 공격력 + 30
}

// attack(Monster* monster) 메서드 구현
int Archer::attack(Monster* monster) {
    // 플레이어 공격 데미지 계산
    int monsterDamage = (power - monster->getDefense()) / 3;
    monsterDamage = (monsterDamage <= 0) ? 1 : monsterDamage;    // 데미지가 0 이하이면 1로 고정

    cout << "[Archer] Shoots arrow! -> " << monsterDamage << " damage to " << monster->getName() << "! (x3)" << endl;

    return monsterDamage * 3;
}

// attack() 메서드 구현
void Archer::attack() {
    cout << "Shoots arrow!" << endl;
}
