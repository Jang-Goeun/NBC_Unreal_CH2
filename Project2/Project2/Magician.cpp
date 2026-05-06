#include "Magician.h"
#include "Monster.h"
#include <iostream>

using namespace std;

// 생성자 구현
Magician::Magician(string name, int* stat, int level, int hpPotion, int mpPotion) : Player(name, stat, level, hpPotion, mpPotion) {
    this->job = "Magician";
    this->mp += 30;  // 마나 + 30
}

// attack(Monster* monster) 메서드 구현
void Magician::attack(Monster* monster) {
    cout << "Casts a blazing Fireball at the enemy!" << endl;
    cout << power << " damage to " << monster->getName() << endl;
}

// attack() 메서드 구현
void Magician::attack() {
    cout << "Casts a blazing Fireball at the enemy!" << endl;
}