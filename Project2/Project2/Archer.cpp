#include "Archer.h"
#include "Monster.h"
#include <iostream>

using namespace std;

// 생성자 구현
Archer::Archer(string name, int* stat, int level, int hpPotion, int mpPotion) : Player(name, stat, level, hpPotion, mpPotion) {
    this->job = "Archer";
    this->power += 30;  // 공격력 + 30
}

// attack(Monster* monster) 메서드 구현
void Archer::attack(Monster* monster) {
    cout << "Fires a sharp arrow with deadly precision!" << endl;
    cout << power << " damage to " << monster->getName() << endl;
}

// attack() 메서드 구현
void Archer::attack() {
    cout << "Fires a sharp arrow with deadly precision!" << endl;
}