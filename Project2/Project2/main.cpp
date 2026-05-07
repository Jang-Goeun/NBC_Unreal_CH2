#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include "Player.h"
#include "Warrior.h" 
#include "Magician.h" 
#include "Archer.h"   
#include "Thief.h"  
#include "Monster.h"
#include "Slime.h"
#include "Item.h"
#include "Potion.h"
#include "RewardItem.h"

using namespace std;

// 포션 레시피 재료 정보 구조체
struct Ingredient {
    string name;
    int count;
};

// 포션 레시피 구조체
struct PotionRecipe {
    string name;
    vector<Ingredient> ingredients;

    void PrintRecipe() const {
        for (size_t i = 0; i < ingredients.size(); ++i) {
            cout << ingredients[i].name << " x" << ingredients[i].count;
            if (i < ingredients.size() - 1) cout << ", ";
        }
    }
};

vector<unique_ptr<Item>> inventory;                // 인벤토리
vector<PotionRecipe> potionRecipe;      // 포션 레시피

// 상태 정보 입력 메서드 
// - 입력 유효성 검사 진행
// - 모두 50보다 클 때만 입력 루프 탈출
// @param inputStat1: 첫번째 입력 스탯 요소 이름
// @param inputStat2: 두번째 입력 스탯 요소 이름
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

/* 인벤토리 관련 메서드*/
// 아이템 추가 메서드
// 1. 인벤토리에 같은 이름을 가진 아이템이 있는지 확인
// 2. 아이템이 이미 있다면: 수량만 증가
// 3. 아이템이 없다면: 새로운 객체 생성하여 추가
// 3-1. isPotion일 경우 포션 클래스 타입으로 아니라면 리워드아이템 클래스 타입으로
void addItem(string name, string effectName, int effectValue, int price, int count, bool isPotion) {
    
    auto it = std::find_if(inventory.begin(), inventory.end(), [&](const std::unique_ptr<Item>& item) {
        return item->getName() == name;
        });

    if (it != inventory.end()) {
        (*it)->addCount(count);
    }
    else if(isPotion) {
        inventory.push_back(std::make_unique<Potion>(name, effectName, effectValue, price, count));
    }
    else {
        inventory.push_back(std::make_unique<RewardItem>(name, effectName, effectValue, price, count));
    }
}

/* 전투 관련 메서드*/

// 플레이어 공격 처리 메서드
// - 몬스터가 죽으면 true 반환
bool handlePlayerAttack(Player* player, Monster* monster) {
    int damage = player->attack(monster);

    cout << monster->getName() << " HP: " << monster->getHp() << " -> ";
    monster->setHp(monster->getHp() - damage);
    cout << monster->getHp() << (monster->getHp() <= 0 ? " (Dead)\n" : "") << endl;

    return monster->getHp() <= 0;
}

// 몬스터 공격 처리 메서드
void handleMonsterAttack(Monster* monster, Player* player) {
    cout << "\n--- " << monster->getName() << " Turn ---" << endl;

    // 데미지 계산 로직
    int damage = monster->attack(player);

    cout << player->getName() << " HP: " << player->getHp() << " -> ";
    player->setHp(player->getHp() - damage);
    cout << player->getHp() << (player->getHp() <= 0 ? " (Dead)\n" : "") << endl;
}

// 아이템 메뉴 및 사용 처리 메서드
// - 아이템을 실제 사용했을 경우에만 true(턴 소모) 반환
bool handleItemMenu(Player* player) {
    if (inventory.empty()) {
        cout << "Inventory is empty!" << endl;
        return false; // 턴 소모 안 함
    }

    // 인벤토리 출력
    cout << "\n[ Inventory ]" << endl;
    for (int i = 0; i < inventory.size(); ++i) {
        cout << i + 1 << ". ";
        inventory[i]->printInfo(); // 아이템 이름, 수량 등 출력
    }

    int choice;
    cout << "Choose: ";
    cin >> choice;

    // 아이템 사용 처리
    if (choice > 0 && choice <= inventory.size()) {
        // useItem은 수량이 0이 되면 true를 반환함
        if (inventory[choice - 1]->useItem(player)) {
            inventory.erase(inventory.begin() + (choice - 1));
        }
        return true; // 아이템 사용 성공 -> 턴 종료
    }

    cout << "Action canceled." << endl;
    return false; // 취소했으므로 턴 종료 안 함
}

// 전투 메서드
// - 플레이어 승리 시 true 반환
// - 몬스터 승리 시 false 반환
// @param player: 전투를 수행할 플레이어 객체
// @param monster: 전투 대상 몬스터 객체
bool battle(Player* player, Monster* monster) {
    string playerName = player->getName();
    string monsterName = monster->getName();

    cout << "\n\n[ Battle Start! ] " << playerName << "(" << player->getJob() << ") vs " << monsterName << endl;

    // 전투 루프: 둘 중 하나가 사망할 때까지 반복
    while (player->getHp() > 0 && monster->getHp() > 0) {
        int action;
        bool turnEnd = false; // 플레이어가 행동을 완료했는지 체크

        cout << "\n--- " << playerName << " Turn ---" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Use Item" << endl;
        cout << "Choose: ";
        cin >> action;

        if (action == 1) {
            // 플레이어 공격 실행 및 몬스터 사망 여부 확인
            if (handlePlayerAttack(player, monster)) {
                return true; // 몬스터 사망 시 즉시 플레이어 승리 반환
            }
            turnEnd = true;
        }
        else if (action == 2) {
            // 아이템 메뉴 실행 (아이템 사용 시에만 턴 종료)
            turnEnd = handleItemMenu(player);
        }
        else {
            cout << "Invalid choice. Please select again!" << endl;
        }

        // 플레이어가 행동을 마쳤고, 몬스터가 살아있다면 몬스터 반격
        if (turnEnd && monster->getHp() > 0) {
            handleMonsterAttack(monster, player);
        }

        // 플레이어 사망 시 루프 종료 후 false 반환 (while 조건문에서 걸러짐)
    }

    return player->getHp() > 0;
}

// 전투 결과 출력 메서드 
// 승리 시 결과 출력 후 아이템 저장 & exp 증가
// @param battleResult: 전투 결과
// @param player: 플레이어
// @param monster: 전투 몬스터
void battleResultPrint(bool battleResult, Monster* monster, Player* player) {
    if (battleResult) {
        // 결과 출력
        cout << "★ Victory!" << endl;
        cout << "  -> Got: " << monster->getDropItemName() << "!" << endl;
        cout << "  -> Saved to inventory." << endl;

        // exp 증가
        player->setExp(player->getExp() + monster->getExpReward());
        cout << "  -> +" << monster->getExpReward() << " EXP! (EXP: " << player->getExp() << "/" << player->getMaxExp() << ")" << endl;

        // 레벨업
        if (player->getExp() >= player->getMaxExp()) {
            cout << "\n... Level up condition met" << endl;
            cout << "  -> Level Up! Lv." << player->getLevel() << " -> Lv.";
            player->setLevel(player->getLevel() + 1);
            cout << player->getLevel() << endl;
            cout << "  -> HP +10, MP +5, Attack +5" << endl;
            player->setHp(min(player->getHp() + 10, player->getMaxHp()));
            player->setMp(player->getMp() + 5);
            player->setPower(player->getPower() + 5);
            player->setExp(player->getExp() - player->getMaxExp());
        }

        // 인벤토리에 아이템 추가
        addItem(monster->getDropItemName(), "HP", 30, monster->getDropItemPrice(), 1, false);
    }
    else {
        cout << "★ Defeat.." << endl;
        cout << "  -> " << player->getName() << " was attacked by " << monster->getName() << " and died." << endl;
        cout << "Please try again!" << endl;
    }
}

/* 포션 제작소 관련 메서드*/
// 전체 레시피 출력 메서드
void ShowAllRecipes() {
    if (potionRecipe.empty()) {
        cout << "The recipe book is empty..." << endl << endl;
        return;
    }

    for (auto& r : potionRecipe) {
        cout << "-> " << r.name << ": ";
        r.PrintRecipe();
        cout << endl;
    }

    cout << endl;
}

// 이름이 일치하는 레시피 출력 메서드
void SearchByName(string name) {

    bool found = false;

    for (auto& r : potionRecipe) {
        if (name == r.name) {
            cout << "-> " << name << ": ";
            r.PrintRecipe();
            cout << endl;
            found = true;
            break;
        }
    }

    // 찾지 못했을 경우
    if(!found)
        cout << "No potion found with that name." << endl;

    cout << endl;
}

// 키워드 재료를 포함한 레시피 전부 출력 메서드
void SearchByIngredient(string ingredient) {

    bool found = false;
    int count = 0;

    for (auto& r : potionRecipe) {
        for (auto& i : r.ingredients) {
            if (ingredient == i.name) {
                cout << "-> " << r.name << " (";
                r.PrintRecipe();
                cout << ")" << endl;
                found = true;
                count++;
                break;
            }
        }
    }

    // 찾지 못했을 경우
    if (!found)
        cout << "No potion found with that ingredient." << endl;
    // 찾았을 경우
    else
        cout << "Found " << count << " recipes." << endl;

    cout << endl;
}

// 포션 제작소 메서드
void showAlchemyWorkshop() {
    int shopChoice;
    bool isValidSelection = false; // 0번 선택했을 경우만 True로 변경
    string searchKeyword;

    cout << "\n=== Potion Shop ===" << endl;
    cout << "1. Show all recipes" << endl;
    cout << "2. Search by potion name" << endl;
    cout << "3. Search by ingredient" << endl;
    cout << "0. Go back" << endl << endl;

    do {
        cout << "Choice: ";
        cin >> shopChoice;

        switch (shopChoice) {
            // 되돌아가기
            case 0:
                isValidSelection = true;
                break;

            // 전체 레시피 보기
            case 1:
                cout << "[ Potion Recipes ]" << endl;
                ShowAllRecipes();
                break;

            // 포션 이름으로 검색
            case 2:
                cout << "Search potion name: ";
                cin >> searchKeyword;
                SearchByName(searchKeyword);
                break;

            // 재료로 검색
            case 3:
                cout << "Search ingredient: ";
                cin >> searchKeyword;
                SearchByIngredient(searchKeyword);
                break;

            // 이외의 숫자 선택
            default:
                cout << "Invalid choice. Please select again!" << endl;
                break;
        }
    } while (!isValidSelection);
}

// 포션 수 변경(도전 과제1)
// 본인은 객체의 멤버변수로 포션을 저장해두어 해당 함수가 필요 없음
// 과제 수행을 위해 작성만 해둔 상태
// 포션 사용은 getter/setter로 진행 중
// 포인터를 쓰지 않고 매개변수만 넘겼을 때 값이 바뀌지 않는 이유를 설명: 
// -> 포인터를 사용하지 않으면 매개변수로 값을 넘길 때 값의 복사가 이루어지므로 원본에는 영향을 주지 않음.
//    따라서 포인터를 안쓰면 매개변수로 넘긴 값을 바꿔도 원본 값이 바뀌지 않음
/*
void setPotion(int count, int* p_HPPotion, int* p_MPPotion) {
    *p_HPPotion = count;
    *p_MPPotion = count;
}
*/


int main() {
    srand((unsigned int)time(NULL));

    // 변수 선언
    string name;                // 캐릭터 이름
    int stat[4] = { 0 };		// 캐릭터 스탯 { "HP", "MP", "공격력", "방어력" }
    Player* player = nullptr;   // 플레이어

    // 기본 포션 추가
    addItem("HP Potion", "HP", 50, 50, 5, true);
    addItem("MP Potion", "MP", 50, 50, 5, true);

    
    // 레시피 추가 
    potionRecipe.push_back({ "HP Potion", {{"Herb", 1}, {"Clear Water", 1}} });
    potionRecipe.push_back({ "StaminaPotion", {{"Herb", 1}, {"Berry", 1}} });

    // 게임 프롤로그 시작 
    cout << "===========================================" << endl;
    cout << "   [ Dungeon Escape Text RPG ]" << endl;
    cout << "===========================================" << endl;

    // 플레이어 정보 입력
    cout << "Enter your hero's name: ";
    getline(cin, name);
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

    // 메인
    bool isGameOver = false;

    while (!isGameOver) {
        int menuChoice;

        cout << "\n\n=== Main Menu ===" << endl;
        cout << "1. Enter Dungeon" << endl;
        cout << "2. Check Inventory" << endl;
        cout << "3. AlchemyWorkshop" << endl;
        cout << "4. UpgradeCharacter" << endl;
        cout << "0. Quit" << endl << endl;

        cout << "Choice: ";
        cin >> menuChoice;

        switch (menuChoice) {
            // 게임 종료
            case 0: {
                isGameOver = true;
                break;
            }
            // 던전 입장
            case 1: {
                Monster * monster = (rand() % 2 == 0) ? new Slime("Slime", "Slime Jelly", 30) : new Slime("King Slime", "Crown", 100, 60, 40 , 30, 50);
                battleResultPrint(battle(player, monster), monster, player);
                delete monster; 
                if (player->getHp() <= 0) isGameOver = true;
                break;
            }
            // 인벤토리 확인
            case 2: {
                int inventorySize = 0;

                // 아이템 총 개수 구하기
                for (int i = 0; i < inventory.size(); ++i) {
                    inventorySize += inventory[i]->getCount();
                }

                cout << "[ Inventory (" << inventorySize << "/100) ]" << endl;

                // 아이템 정보 출력
                for (int i = 1; i <= inventory.size(); ++i) {
                    cout << i << ". ";
                    inventory[i - 1]->printInfo();
                }
                break;
            }
            // 포션 제작소
            case 3: {
                showAlchemyWorkshop();

                cout << "\n=== Main Menu ===" << endl;
                cout << "1. Enter Dungeon" << endl;
                cout << "2. Check Inventory" << endl;
                cout << "3. AlchemyWorkshop" << endl;
                cout << "0. Quit" << endl << endl;
                break;
            }
            // 포션 사용
            case 4: {
                player->upgradeCharacter(inventory[0], inventory[1]);
                break;
            }
            // 이외의 숫자 선택
            default: {
                cout << "Invalid choice. Please select again!" << endl;
                break;
            }
        }
    }

    // 프로그램 종료 전 메모리 해제
    if (player != nullptr) {
        delete player;
        player = nullptr;
    }

    return 0;
}
