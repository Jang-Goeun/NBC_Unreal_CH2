#include "Magician.h"
#include "Monster.h"
#include <iostream>

using namespace std;

// 생성자 구현
Magician::Magician(string name, int* stat, int level, int exp, int maxExp) : Player(name, stat, level, exp, maxExp) {
    this->job = "Magician";
    this->mp += 30;  // 마나 + 30
}

// attack(Monster* monster) 메서드 구현
int Magician::attack(Monster* monster) {
    // 플레이어 공격 데미지 계산
    int monsterDamage = power - monster->getDefense();
    monsterDamage = (monsterDamage <= 0) ? 1 : monsterDamage;    // 데미지가 0 이하이면 1로 고정

    cout << "[Mage] Fires fireball! -> " << monsterDamage << " damage to " << monster->getName() << "!" << endl;

    return monsterDamage;
}

// attack() 메서드 구현
void Magician::attack() {
    cout << "Fires fireball!" << endl;
}
