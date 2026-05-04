#include "Player.h"
#include "Monster.h"
#include <iostream>

using namespace std;

// 생성자 구현
Player::Player(string name, int* stat, int level, int hpPotion, int mpPotion) {
    this->name = name;
    this->hp = stat[0];
    this->mp = stat[1];
    this->power = stat[2];
    this->defense = stat[3];
    this->level = level;
    this->hpPotion = hpPotion;
    this->mpPotion = mpPotion;
}

// printPlayerStatus 메서드
void Player::printPlayerStatus() {
    cout << "------------------------------------" << endl;
    cout << "Name: " << getName() << "| Job: " << getJob() << "| Lv." << getLevel() << endl;
    cout << "HP: " << getHp() << "| MP: " << getMp() << "| Attack: " << getPower() << "| Defense: " << getDefense() << endl;
    cout << "------------------------------------" << endl;
}

// 캐릭터 능력치를 업그레이드하는 메서드
// - Player* player: 플레이어
// - bool* isGameStart
void Player::upgradeCharacter(Player* player) {
    bool isGameStart = false;

    // 스탯 관리 메뉴
    cout << "\n\n< Stat management >" << endl;
    cout << "* You received " << player->getHpPotion() << " HP Potions and " << player->getMpPotion() << " MP Potions." << endl;
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
            if (player->getHpPotion() == 0)
                cout << "There is no HP potion." << endl;
            else {
                player->setHpPotion(player->getHpPotion() - 1);
                cout << "* HP increased by 20. (HP Potion used: " << player->getHpPotion() << " left)." << endl;
                player->setHp(player->getHp() + 20);
            }
            break;

            // 2. MP 20 증가
        case 2:
            if (player->getMpPotion() == 0)
                cout << "There is no MP potion." << endl;
            else {
                player->setMpPotion(player->getMpPotion() - 1);
                cout << "* MP increased by 20. (MP Potion used: " << player->getMpPotion() << " left)." << endl;
                player->setMp(player->getMp() + 20);
            }
            break;

            // 3. Attack 2배 증가
        case 3:
            cout << "* Attack power doubled." << endl;
            player->setPower(player->getPower() * 2);
            break;

            // 4. Defense 2배 증가
        case 4:
            cout << "* Defense power doubled." << endl;
            player->setDefense(player->getDefense() * 2);
            break;

            // 5. 사용자 정보 출력
        case 5:
            player->printPlayerStatus();
            break;

            // 예외. 없는 선택지 선택
        default:
            cout << "You have selected an option that does not exist.\nPlease select again." << endl;
            break;
        }
    }
}