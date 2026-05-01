#include <string>
#include <iostream>

using namespace std;

const int SIZE = 4;

// 상태 정보 출력 메서드
void printStatus(string name, int stat[]) {
	cout << "====================================" << endl;
	cout << "  " << name << "'s Stats" << endl;
	cout << "====================================" << endl;
	cout << "HP: " << stat[0] << "    MP: " << stat[1] << endl;
	cout << "Attack: " << stat[2] << "    Defense: " << stat[3] << endl;
	cout << "====================================" << endl;
}

// 상태 정보 입력 메서드
// - 입력 유효성 검사 진행
// - 모두 50보다 클 때만 입력 루프 탈출
// - string inputStat1: 첫번째 입력 스탯 요소 이름
// - string inputStat2: 두번째 입력 스탯 요소 이름
void inputStat(int* stat, string inputStat1, string inputStat2) {
	int stat1, stat2; // 입력받을 스탯 값 저장

	// 스택 입력 반복문
	while (true) {
		cout << "Enter " << inputStat1 << " and " << inputStat2 << ": ";
		cin >> stat1 >> stat2;

		if (stat1 > 50 && stat2 > 50)
			break;
		else
			cout << inputStat1 << " or " << inputStat2 << " is too low. Try again." << endl;
	}

	// HP와 MP 저장
	if (inputStat1 == "HP") {  
		stat[0] = stat1;
		stat[1] = stat2;
	}
	// Attack과 Defense 저장
	else {
		stat[2] = stat1;
		stat[3] = stat2;
	}
}

int main() {
	// 변수 선언
	string name;				// 캐릭터 이름
	int stat[SIZE] = { 0 };		// 캐릭터 스탯 { "HP", "MP", "공격력", "방어력" }
	int HPPotion = 5;			// HP 포션 5개
	int MPPotion = 5;			// MP 포션 5개
	bool isGameStart = false;	// 게임 시작/종료 플래그


	// 게임 시작 
	cout << "===========================================" << endl;
	cout << "   [ Dungeon Escape Text RPG ]" << endl;
	cout << "===========================================" << endl;

	// 캐릭터 정보 입력
	cout << "Enter your hero's name: ";
	cin >> name;
	cout << endl;

	inputStat(stat, "HP", "MP");
	inputStat(stat, "Attack", "Defense");
	cout << endl;

	// 캐릭터 정보 출력
	printStatus(name, stat);

	// 스탯 관리 메뉴
	cout << "\n* You received " << HPPotion << " HP Potions and " << MPPotion << " MP Potions." << endl;
	cout << "============================================" << endl;
	cout << "< Character Upgrade >" << endl;
	cout << "1. HP UP    2. MP UP    3. Attack x2" << endl;
	cout << "4. Defense x2  5. Show Stats  0. Start Game" << endl;
	cout << "============================================" << endl;

	while (!isGameStart) {
		int choice = -1; // 사용자 선택사항 저장 변수
		cout << "Choose: ";
		cin >> choice;

		switch (choice) {
			case 0:	
				cout << "Starting the game!\n" << endl;
				isGameStart = true;
				break;
			case 1:
				if (HPPotion == 0)
					cout << "There is no HP potion." << endl;
				else {
					cout << "* HP increased by 20. (HP Potion used: " << --HPPotion << " left)." << endl;
					stat[0] += 20;
				}
				break;

			case 2:
				if (MPPotion == 0)
					cout << "There is no MP potion." << endl;
				else {
					cout << "* MP increased by 20. (MP Potion used: " << --MPPotion << " left)." << endl;
					stat[1] += 20;
				}
				break;

			case 3:
				cout << "* Attack power doubled." << endl;
				stat[2] *= 2;
				break;

			case 4:
				cout << "* Defense power doubled." << endl;
				stat[3] *= 2;
				break;

			case 5:
				printStatus(name, stat);
				break; 

			default:
				cout << "You entered an incorrect choice." << endl;
				break;
			}
		}

	return 0;
}