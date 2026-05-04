#include "Thief.h"
#include "Monster.h"
#include <iostream>

using namespace std;

// 생성자 구현
Thief::Thief(string name, int* stat, int level, int hpPotion, int mpPotion) : Player(name, stat, level, hpPotion, mpPotion) {
    this->job = "Thief";
    this->power += 30;  // 공격력 + 30
}

// attack(Monster* monster) 메서드 구현
void Thief::attack(Monster* monster) {
    cout << "Throws poisoned daggers with lightning speed!" << endl;
    cout << power << " damage to " << monster->getName() << endl;
}

// attack() 메서드 구현
void Thief::attack() {
    cout << "Throws poisoned daggers with lightning speed!" << endl;
}