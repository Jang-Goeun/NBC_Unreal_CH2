#include "Thief.h"
#include "Monster.h"
#include <iostream>

using namespace std;

// 생성자 구현
Thief::Thief(string name, int* stat, int level, int hpPotion, int mpPotion, int exp, int maxExp) : Player(name, stat, level, hpPotion, mpPotion, exp, maxExp) {
    this->job = "Thief";
    this->power += 30;  // 공격력 + 30
}

// attack(Monster* monster) 메서드 구현
int Thief::attack(Monster* monster) {
    // 플레이어 공격 데미지 계산
    int monsterDamage = (power - monster->getDefense()) / 5;
    monsterDamage = (monsterDamage <= 0) ? 1 : monsterDamage;    // 데미지가 0 이하이면 1로 고정

    cout << "[Thief] Stabs dagger! -> " << monsterDamage << " damage to " << monster->getName() << "! (x5)" << endl;

    return monsterDamage * 5;
}

// attack() 메서드 구현
void Thief::attack() {
    cout << "Stabs dagger!" << endl;
}
