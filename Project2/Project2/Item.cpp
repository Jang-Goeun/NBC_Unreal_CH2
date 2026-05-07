#include "Item.h"
#include "Player.h"
#include <iostream>

using namespace std;

// 생성자 구현
Item::Item(string name, int count) {
    this->name = name;
    this->count = count;
}

// printInfo 메서드
void Item::printInfo() {
    cout << name << " " << "(" << price << "G) x" << count << endl;
}
