#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include <iostream>

using namespace std;

// 생성자 구현
Player::Player(string name, int* stat, int level, int exp, int maxExp) {
    this->name = name;
    this->hp = stat[0];
    this->mp = stat[1];
    this->power = stat[2];
    this->defense = stat[3];
    this->level = level;
    this->exp = exp;
    this->maxExp = maxExp;
}

// printPlayerStatus 메서드
void Player::printPlayerStatus() {
    cout << "------------------------------------" << endl;
    cout << "Name: " << name << "| Job: " << job << "| Lv." << level << "| Exp: " << exp << endl;
    cout << "HP: " << hp << "| MP: " << mp << "| Attack: " << power << "| Defense: " << defense << endl;
    cout << "------------------------------------" << endl;
}

// 캐릭터 능력치를 업그레이드하는 메서드
// - bool* isGameStart
void Player::upgradeCharacter(unique_ptr<Item>& hpPotion, unique_ptr<Item>& mpPotion) {
    bool isGameStart = false;
    int hpPotionCount = hpPotion->getCount();
    int mpPotionCount = mpPotion->getCount();


    // 스탯 관리 메뉴
    cout << "\n\n< Stat management >" << endl;
    cout << "* You received " << hpPotionCount << " HP Potions and " << mpPotionCount << " MP Potions." << endl;
    cout << "============================================" << endl;
    cout << "< Character Upgrade Options >" << endl;
    cout << "1. HP UP    2. MP UP    3. Attack x2" << endl;
    cout << "4. Defense x2  5. Show Stats  0. Start Game" << endl;
    cout << "============================================" << endl;


    while (!isGameStart) {
        int choice = -1; // 사용자 선택사항 저장 변수
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            // 0. 게임 시작
        case 0:
            isGameStart = true;
            break;

            // 1. HP 20 증가
        case 1:
            if (hpPotionCount == 0)
                cout << "There is no HP potion." << endl;
            else {
                cout << "* HP increased by 20. (HP Potion used: " << --hpPotionCount << " left)." << endl;
                hpPotion->setCount(hpPotionCount);
                hp += 20;
            }
            break;

            // 2. MP 20 증가
        case 2:
            if (mpPotionCount == 0)
                cout << "There is no MP potion." << endl;
            else {
                cout << "* MP increased by 20. (MP Potion used: " << --mpPotionCount << " left)." << endl;
                mpPotion->setCount(mpPotionCount);
                mp += 20;
            }
            break;

            // 3. Attack 2배 증가
        case 3:
            cout << "* Attack power doubled." << endl;
            power += 2;
            break;

            // 4. Defense 2배 증가
        case 4:
            cout << "* Defense power doubled." << endl;
            defense += 2;
            break;

            // 5. 사용자 정보 출력
        case 5:
            printPlayerStatus();
            break;

            // 예외. 없는 선택지 선택
        default:
            cout << "You have selected an option that does not exist.\nPlease select again." << endl;
            break;
        }
    }
}
