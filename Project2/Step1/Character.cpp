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

int main() {
	string name;				// 캐릭터 이름
	int stat[SIZE] = { 0 };		// 캐릭터 스탯 { "HP", "MP", "공격력", "방어력" }

	// 게임 시작
	cout << "===========================================" << endl;
	cout << "   [ Dungeon Escape Text RPG ]" << endl;
	cout << "===========================================" << endl;

	// 캐릭터 이름 입력
	cout << "Enter your hero's name: ";
	cin >> name;
	cout << endl;

	// 캐릭터 스택 정보 입력
	cout << "Enter HP and MP: ";
	cin >> stat[0] >> stat[1];
	cout << "Enter Attack and Defense: ";
	cin >> stat[2] >> stat[3];
	cout << endl;

	// 캐릭터 정보 출력 메서드 호출
	printStatus(name, stat);

	return 0;
}