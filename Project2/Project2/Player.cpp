#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include <iostream>
#include <algorithm>
#include <conio.h>

using namespace std;

/*
 * @brief 생성자 구현
 */
Player::Player(string name, int* stat, int level, int exp, int maxExp, int maxHp)
{
    this->name = name;
    this->hp = stat[0];
    this->mp = stat[1];
    this->power = stat[2];
    this->defense = stat[3];
    this->level = level;
    this->exp = exp;
    this->maxExp = maxExp;
    this->maxHp = maxHp;
}

/*
 * @brief printPlayerStatus 메서드
 */
void Player::printPlayerStatus()
{
    cout << "-------------------------------------------" << endl;
    cout << "Name: " << name << "| Job: " << job << "| Lv." << level << "| Exp: " << exp << endl;
    cout << "HP: " << hp << "| MP: " << mp << "| Attack: " << power << "| Defense: " << defense << endl;
    cout << "-------------------------------------------" << endl;
}

/*
 * @brief 캐릭터 능력치를 업그레이드하는 메서드 
 */
void Player::upgradeCharacter(Item* hpPotion, Item* mpPotion)
{
    bool isGameStart = false;
    int hpPotionCount = (hpPotion != nullptr) ? hpPotion->getCount() : 0;
    int mpPotionCount = (mpPotion != nullptr) ? mpPotion->getCount() : 0;

    // 스탯 관리 메뉴
    while (!isGameStart)
    {
        int choice = -1;

        // 화면 지우기
        cout << "\nPress any key..";
        _getch();
        std::cout << "\033[2J\033[1;1H";

        cout << "< Stat management >" << endl;
        cout << "* You received " << hpPotionCount << " HP Potions and " << mpPotionCount << " MP Potions." << endl;
        cout << "===================================================" << endl;
        cout << "< Character Upgrade Options >" << endl;
        cout << "1. HP UP    2. MP UP    3. Attack x2" << endl;
        cout << "4. Defense x2  5. Show Stats  0. Go to Main Menu" << endl;
        cout << "===================================================" << endl;
        cout << "Choose: ";
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1;
        }

        switch (choice)
        {
            // 0. 게임 시작
            case 0:
            {
                isGameStart = true;
                break;
            }
            // 1. HP 20 증가
            case 1:
            {
                if (hpPotion == nullptr || hpPotionCount == 0) cout << "There is no HP potion." << endl;
                else
                {
                    cout << "* HP increased by " << hpPotion->getEffectValue() << ". (HP Potion used: " << --hpPotionCount << " left)." << endl;
                    hpPotion->setCount(hpPotionCount);
                    hp = min(hp + hpPotion->getEffectValue(), maxHp);
                }
                break;
            }
            // 2. MP 20 증가
            case 2:
            {
                if (mpPotion == nullptr || mpPotionCount == 0) cout << "There is no MP potion." << endl;
                else
                {
                    cout << "* MP increased by " << mpPotion->getEffectValue() << ". (MP Potion used: " << --mpPotionCount << " left)." << endl;
                    mpPotion->setCount(mpPotionCount);
                    mp += mpPotion->getEffectValue();
                }
                break;
            }
            // 3. Attack 2배 증가
            case 3:
            {
                cout << "* Attack power doubled." << endl;
                power *= 2;
                break;
            }
            // 4. Defense 2배 증가
            case 4:
            {
                cout << "* Defense power doubled." << endl;
                defense *= 2;
                break;
            }
            // 5. 사용자 정보 출력
            case 5:
            {
                cout << endl;
                printPlayerStatus();
                break;
            }
            // 예외. 없는 선택지 선택
            default:
            {
                cout << "You have selected an option that does not exist.\nPlease select again." << endl;
                break;
            }
        }
    }
}
