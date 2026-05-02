#include "Warrior.h"
#include <iostream>

using namespace std;

// 생성자 구현
Warrior::Warrior(string name, int* stat, int level, int hpPotion, int mpPotion) : Player(name, stat, level, hpPotion, mpPotion) {
    this->job = "Warrior";
    this->defense += 30; // 방어력 +30
}

// attack() 메서드 구현
void Warrior::attack() {
    cout << "Swings a massive sword with great force!" << endl;
}