#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Warrior.h" 
#include "Magician.h" 
#include "Archer.h"   
#include "Thief.h"  
#include "Monster.h"
#include "Slime.h"

using namespace std;

// 인벤토리 구조체
struct Item {
    string name;
    int price; 
    void PrintInfo() const { cout << name << " " << "(" << price << "G)" << endl; }
};

vector<Item> inventory;     // 인벤토리

// 상태 정보 입력 메서드 
// - 입력 유효성 검사 진행
// - 모두 50보다 클 때만 입력 루프 탈출
// - string inputStat1: 첫번째 입력 스탯 요소 이름
// - string inputStat2: 두번째 입력 스탯 요소 이름
void inputStat(int* stat, string inputStat1, string inputStat2) {
    int stat1, stat2;
    while (true) {
        cout << "Enter " << inputStat1 << " and " << inputStat2 << ": ";
        cin >> stat1 >> stat2;

        if (stat1 > 50 && stat2 > 50) break;
        else cout << inputStat1 << " or " << inputStat2 << " is too low. Try again." << endl;
    }

    if (inputStat1 == "HP") {
        stat[0] = stat1; stat[1] = stat2;
    }
    else {
        stat[2] = stat1; stat[3] = stat2;
    }
}

// 전투 메서드 
// - 플레이어 승리 시 true 반환
// - 몬스터 승리 시 false 반환
// - Player* player: 플레이어
// - Monster* monster: 전투 몬스터
bool battle(Player* player, Monster* monster) {
    string playerName = player->getName();
    string monsterName = monster->getName();
    bool battleResult = true;

    // 전투 시작 멘트 출력
    cout << "\n[ Battle Start! ] " << playerName << "(" << player->getJob() << ") vs " << monsterName << endl << endl;

    // 전투 진행 while문(둘 중 하나가 죽을 때까지)
    while (player->getHp() > 0 && monster->getHp() > 0) {
        // Player Turn
        cout << "--- " << playerName << " Turn --- " << endl;
        player->attack(monster);

        // 플레이어 공격 데미지 계산
        int monsterDamage = player->getPower() - monster->getDefense();
        monsterDamage = (monsterDamage <= 0) ? 1 : monsterDamage;    // 데미지가 0 이하이면 1로 고정
        
        cout << monsterName << " HP: " << monster->getHp() << " -> ";
        monster->setHp(monster->getHp() - monsterDamage);
        cout << monster->getHp();
        
        // 몬스터 사망
        if (monster->getHp() <= 0) {
            cout << " (Dead)" << endl << endl;
            continue;
        }

        cout << endl;

        // Monster Turn
        cout << "--- " << monsterName << " Turn-- - " << endl;
        monster->attack(player);

        // 몬스터 공격 데미지 계산
        int playerDamage = monster->getPower() - player->getDefense();
        playerDamage = (playerDamage <= 0) ? 1 : playerDamage;    // 데미지가 0 이하이면 1로 고정

        cout << playerName << " HP: " << player->getHp() << " -> ";
        player->setHp(player->getHp() - playerDamage);
        cout << player->getHp();

        // 플레이어 사망
        if (player->getHp() <= 0) {
            cout << " (Dead)" << endl << endl;
            battleResult = false;
            continue;
        }

        cout << endl;
    }

    return battleResult;
}

// 전투 결과 출력 메서드 
// 승리 시 결과 출력 후 아이템 저장
// - battleResult: 전투 결과
// - Player* player: 플레이어
// - Monster* monster: 전투 몬스터
void battleResultPrint(bool battleResult, Monster* monster, Player* player) {
    if (battleResult) {
        cout << "★ Victory!" << endl;
        cout << "  -> Got: " << monster->getDropItemName() << "!" << endl;
        cout << "  -> Saved to inventory." << endl << endl;

        // 인벤토리에 아이템 추가
        Item droppedItem = { monster->getDropItemName(), monster->getDropItemPrice() };
        inventory.push_back(droppedItem);
    }
    else {
        cout << "★ Defeat.." << endl;
        cout << "  -> " << player->getName() << " was attacked by " << monster->getName() << " and died." << endl;
        cout << "Please try again!" << endl << endl;
    }
}

// 메인 메뉴 메서드
void showMainMenu() {
    int menuChoice;
    bool isValidSelection = false;

    cout << "\n=== Main Menu ===" << endl;
    cout << "1. Enter Dungeon" << endl;
    cout << "2. Check Inventory" << endl;
    cout << "0. Quit" << endl << endl;

    cout << "Choice: ";
    cin >> menuChoice;

    while (!isValidSelection) {
        switch (menuChoice) {
            // 게임 종료
            case 0:
                isValidSelection = !isValidSelection;
                break;
            // 던전 입장
            case 1:
                isValidSelection = !isValidSelection;
                break;

            // 인벤토리 확인
            case 2:
                cout << "[ Inventory (" << inventory.size() << "/ 10) ]" << endl;
                
                for (int i = 1; i <= inventory.size(); i++) {
                    cout << i << ". ";
                    inventory[i - 1].PrintInfo();
                }

                isValidSelection = !isValidSelection;
                break;

            // 이외의 숫자 선택
            default:
                cout << "Invalid choice. Please select again!" << endl;
                cout << "Choice: ";
                cin >> menuChoice;
                break;
        }
    }
}

int main() {
    // 변수 선언
    string name;                // 캐릭터 이름
    int stat[4] = { 0 };		// 캐릭터 스탯 { "HP", "MP", "공격력", "방어력" }
    Player* player = nullptr;   // 플레이어  

    // 게임 프롤로그 시작 
    cout << "===========================================" << endl;
    cout << "   [ Dungeon Escape Text RPG ]" << endl;
    cout << "===========================================" << endl;

    // 플레이어 정보 입력
    cout << "Enter your hero's name: ";
    cin >> name;
    cout << endl;

    inputStat(stat, "HP", "MP");
    inputStat(stat, "Attack", "Defense");
    cout << endl;

    // 직업 선택
    int jobChoice;
    bool isValidSelection = false;

    cout << "\n< Job Selection >" << endl;
    cout << name << ", choose your job!" << endl;
    cout << "1. Warrior   2. Magician   3. Archer   4. Thief" << endl;
    cout << "Choice: ";
    cin >> jobChoice;

    // 직업 할당
    while (!isValidSelection) {
        switch (jobChoice) {
            case 1: 
                cout << "* You became a Warrior! (Defense +30)" << endl;
                player = new Warrior(name, stat);
                isValidSelection = !isValidSelection;
                break;
            case 2:
                cout << "* You became a Mage! (MP +30)" << endl;
                player = new Magician(name, stat);
                isValidSelection = !isValidSelection;
                break;
            case 3:
                cout << "* You became a Archer! (Attack +30)" << endl;
                player = new Archer(name, stat);
                isValidSelection = !isValidSelection;
                break;
            case 4:
                cout << "* You became a Thief! (Attack +30)" << endl;
                player = new Thief(name, stat);
                isValidSelection = !isValidSelection;
                break;
            default:
                cout << "Invalid choice. Please select again!" << endl;
                cout << "Choice: ";
                cin >> jobChoice;
                break;
        }
    }

    // 기본 공격 메시지와 플레이어 정보 출력
    player->attack();
    player->printPlayerStatus(); 

    // 포션 사용 
    player->upgradeCharacter(player);

    // 전투 시작(1단계 기본 몬스터 슬라임과 전투)
    Monster* monster = new Slime("Slime", "Slime Jelly", 30);
    bool battleResult = battle(player, monster);

    // 전투 결과 출력
    battleResultPrint(battleResult, monster, player);

    // 메인 메뉴 
    showMainMenu();

    // 프로그램 종료 전 메모리 해제
    if (player != nullptr) {
        delete player;
        player = nullptr;
    }

    if (monster != nullptr) {
        delete monster;
        monster = nullptr;
    }

    return 0;
}
