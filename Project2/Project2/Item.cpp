#include "Item.h"
#include "Player.h"
#include <iostream>

using namespace std;

/*
 * @brief 생성자
 */
Item::Item(string name, int count)
{
    this->name = name;
    this->count = count;
}

/*
 * @brief printInfo 메서드
 */
void Item::printInfo() { cout << name << " " << "(" << price << "G) x" << count << endl; }

/*
 * @brief addCount 메서드
 */
void Item::addCount(int val) { count += val; }
