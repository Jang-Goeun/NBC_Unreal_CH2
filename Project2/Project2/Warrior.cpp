#include "Warrior.h"
#include "Monster.h"
#include <iostream>

using namespace std;

// 생성자 구현
Warrior::Warrior(string name, int* stat, int level, int exp, int maxExp) : Player(name, stat, level, exp, maxExp) {
    this->job = "Warrior";
    this->defense += 30; // 방어력 +30
}

// attack(Monster* monster) 메서드 구현
int Warrior::attack(Monster* monster) {
    // 플레이어 공격 데미지 계산
    int monsterDamage = power - monster->getDefense();
    monsterDamage = (monsterDamage <= 0) ? 1 : monsterDamage;    // 데미지가 0 이하이면 1로 고정

    cout << "[Warrior] Swings sword! -> " << monsterDamage << " damage to " << monster->getName() << "!" << endl;

    return monsterDamage;
}

// attack() 메서드 구현
void Warrior::attack() {
    cout << "Swings sword!" << endl;
}
