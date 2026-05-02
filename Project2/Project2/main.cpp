#include <iostream>
#include <string>
#include "Player.h"
#include "Warrior.h" 
#include "Magician.h" 
#include "Archer.h"   
#include "Thief.h"  

using namespace std;

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

int main() {
    // 변수 선언
    string name;                // 캐릭터 이름
    int stat[4] = { 0 };		// 캐릭터 스탯 { "HP", "MP", "공격력", "방어력" }
    Player* player = nullptr; 

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

    // 프로그램 종료 전 메모리 해제
    if (player != nullptr) {
        delete player;
        player = nullptr;
    }

    return 0;
}
