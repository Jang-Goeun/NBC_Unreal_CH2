#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <memory>
#include <conio.h>
#include <ctime>
#include "Player.h"
#include "Warrior.h" 
#include "Magician.h" 
#include "Archer.h"   
#include "Thief.h"  
#include "Monster.h"
#include "Slime.h"
#include "Goblin.h"
#include "Orc.h"
#include "Slime.h"
#include "Item.h"
#include "Potion.h"
#include "RewardItem.h"
#include "Inventory.h"

using namespace std;

// 포션 레시피 재료 정보 구조체
struct Ingredient
{
    string name;
    int count;
};

// 포션 레시피 구조체
struct PotionRecipe
{
    string name;
    vector<Ingredient> ingredients;

    void PrintRecipe() const
    {
        for (size_t i = 0; i < ingredients.size(); ++i)
        {
            cout << ingredients[i].name << " x" << ingredients[i].count;
            if (i < ingredients.size() - 1) cout << ", ";
        }
    }
};

// 전역 변수 선언
Inventory<Item*> playerInventory(30);
vector<PotionRecipe> potionRecipe;      // 포션 레시피
vector<Monster*> slimeCastle;
vector<Monster*> goblinCastle;
vector<Monster*> orcCastle;
int slimeProgress = 0, goblinProgress = 0, orcProgress = 0; // 각 성의 진행 단계를 저장하는 변수 (0: 일반, 1: 중간, 2: 보스)

// @brief 콘솔 창 정리 메서드
void clearScreen()
{
    cout << "\nPress any key..";
    _getch();
    system("cls");
}

/*
 * @brief 상태 정보 입력 메서드
 *  입력 유효성 검사 진행
 *  모두 50보다 클 때만 입력 루프 탈출
 * @param inputStat1: 첫번째 입력 스탯 요소 이름
 * @param inputStat2: 두번째 입력 스탯 요소 이름
 */
void inputStat(int* stat, string inputStat1, string inputStat2)
{
    int stat1, stat2;

    while (true)
    {
        cout << "Enter " << inputStat1 << " and " << inputStat2 << "(50~100): ";
        if (!(cin >> stat1 >> stat2))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter numbers." << endl;
            continue;
        }

        if (stat1 >= 50 && stat2 >= 50 && stat1 <= 100 && stat2 <= 100) { break; }
        else if ((stat1 > 100 && stat2 < 50) || (stat1 < 50 && stat2 > 100)) { cout << "The number is outside the input range. Try again." << endl; }
        else if (stat1 <  50 || stat2 < 50) { cout << inputStat1 << " or " << inputStat2 << " is too low. Try again." << endl; }
        else if (stat1 > 100 || stat2 > 100) { cout << inputStat1 << " or " << inputStat2 << " is too high. Try again." << endl; }
    }

    if (inputStat1 == "HP") { stat[0] = stat1; stat[1] = stat2; }
    else { stat[2] = stat1; stat[3] = stat2; }
}

// 레벨 및 게임 종료 관련 메서드
/*
 * @brief 레벨 업 메서드
 */
void levelUp(Player* player)
{
    player->setLevel(player->getLevel() + 1);
    int currentLv = player->getLevel();
    int bonusATK = 0, bonusDEF = 0;

    // 구간별 차등 보상
    if (currentLv <= 5) { bonusATK = 3; bonusDEF = 2;; }
    else if (currentLv <= 10) { bonusATK = 5; bonusDEF = 3; }
    else { bonusATK = 8; bonusDEF = 5; }

    // 5레벨마다 특별 보너스
    if (currentLv % 5 == 0)
    {
        bonusATK += 5;
        cout << "★ Special Breakthrough Bonus!" << endl;
        cout << "-> Attack +5" << endl;
    }

    player->setPower(player->getPower() + bonusATK);
    player->setDefense(player->getDefense() + bonusDEF);
    player->setHp(player->getMaxHp()); // 레벨업 시 체력 
    cout << "\n... Level up condition met" << endl;
    cout << "Level Up! Lv." << currentLv << endl;
    cout << "-> Attack +" << bonusATK << ", defense +" << bonusDEF  << ", HP(Fully Restored!)\n" << endl;
}

// 인벤토리 관련 메서드
/*
 * @brief 아이템 추가 메서드
 * @param  isPotion: true - 포션 클래스 타입 / false - 리워드 아이템 클래스 타입
 */
void addItem(string name, string effectName, int effectValue, int price, int count, bool isPotion)
{
    Item* newItem = nullptr;
    if (isPotion) newItem = new Potion(name, effectName, effectValue, price, count);
    else newItem = new RewardItem(name, effectName, effectValue, price, count);
    playerInventory.AddItem(newItem);
}

/*
 * @brief 아이템 메뉴 및 사용 처리 메서드
 * @return 아이템 사용 여부(아이템 사용 시 true - 턴 종료) 
 */
bool handleItemMenu(Player* player)
{
    if(playerInventory.GetSize() == 0)
    {
        cout << "Inventory is empty!" << endl;
        return false;
    }

    // 인벤토리 출력
    playerInventory.PrintAllItems();

    int choice;
    cout << "Choose (Only Potions are usable): ";
    cin >> choice;

    int index = choice - 1;
    Item* selectedItem = playerInventory.GetItem(index);

    // 아이템 선택 처리
    if (selectedItem != nullptr)
    {
        // Potion 클래스인지 확인 
        Potion* potion = dynamic_cast<Potion*>(selectedItem);

        if (potion != nullptr)
        {
            if (selectedItem->useItem(player))
            {
                delete selectedItem;
                playerInventory.RemoveItem(index);
            }
            playerInventory.UpdateTotalCount();
            return true;
        }
        else
        {
            cout << "\nThis item is not a potion and cannot be used here!" << endl;
        }
    }
    else
    {
        cout << "\nAction canceled or invalid selection." << endl;
    }
    
    clearScreen();
    return false; // 아이템 사용 취소 또는 포션 아님 - 턴 종료 안 함
}

// 포션 제작소 관련 메서드
/*
 * @brief 전체 레시피 출력 메서드
 */
void showAllRecipes()
{
    if (potionRecipe.empty())
    {
        cout << "The recipe book is empty..." << endl << endl;
        return;
    }

    for (auto& r : potionRecipe)
    {
        cout << "-> " << r.name << ": ";
        r.PrintRecipe();
        cout << endl;
    }
}

/*
 * @brief 이름이 일치하는 레시피 출력 메서드
 */
void searchByName(string name)
{

    bool found = false;

    for (auto& r : potionRecipe)
    {
        if (name == r.name)
        {
            cout << "-> " << name << ": ";
            r.PrintRecipe();
            cout << endl;
            found = true;
            break;
        }
    }

    // 찾지 못했을 경우
    if (!found) cout << "No potion found with that name." << endl;

    clearScreen();
}

/*
 * @brief 키워드 재료를 포함한 레시피 전부 출력 메서드
 */
void searchByIngredient(string ingredient)
{

    bool found = false;
    int count = 0;

    for (auto& r : potionRecipe)
    {
        for (auto& i : r.ingredients)
        {
            if (ingredient == i.name)
            {
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
    if (!found) cout << "No potion found with that ingredient." << endl;
    // 찾았을 경우
    else cout << "Found " << count << " recipes." << endl;

    clearScreen();
}

/*
 * @brief 포션 제작 메서드
 */
void craftingPotion(string potionName)
{
    bool found = false;
    PotionRecipe recipe;

    for (auto& r : potionRecipe)
    {
        // 1. 포션 레시피가 있는지 확인하기
        if (potionName == r.name)
        {
            found = true;
            recipe = r;

            // 2. 포션 레시피가 있다면 레시피 재료를 소유하고 있는지 확인하기
            for (auto& i : r.ingredients)
            {
                int itemIdx = playerInventory.FindItem(i.name);
                // 아이템이 없거나 수량이 부족한 경우
                if (itemIdx == -1 || playerInventory.GetItem(itemIdx)->getCount() < i.count)
                {
                    cout << "Not enough ingredients to make " << potionName << "." << endl;
                    return;
                }
            }

            break;
        }
    }

    // 3. 재료가 모두 있다면 포션 만들고 재료들 사용 진행
    // 3-1. 레시피를 찾지 못했을 경우
    if (!found)
    {
        cout << "No potion found with that name." << endl;
    }
    // 3-2. 레시피를 찾고, 아이템을 모두 보유 중인 경우
    else
    {
        cout << "\nStart making " << potionName << "!!" << endl;
        cout << "Used ";

        for (size_t i = 0; i < recipe.ingredients.size(); ++i)
        {
            cout << recipe.ingredients[i].count << " " << recipe.ingredients[i].name;
            if (i < recipe.ingredients.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "." << endl;

        // 재료 소모
        for (auto& i : recipe.ingredients)
        {
            int itemIdx = playerInventory.FindItem(i.name);
            Item* item = playerInventory.GetItem(itemIdx);

            item->setCount(item->getCount() - i.count);

            if (item->getCount() <= 0)
            {
                delete item;
                playerInventory.RemoveItem(itemIdx);
            }
        }

        // 포션 추가 (레시피 이름에 따라 능력치 설정)
        if (potionName == "HP Potion")
            addItem("HP Potion", "HP", 50, 50, 1, true);
        else if (potionName == "MP Potion")
            addItem("MP Potion", "MP", 50, 50, 1, true);

        playerInventory.UpdateTotalCount();
        cout << "Successfully crafted: " << potionName << "!" << endl;
    }
}

/*
 * @brief 포션 제작소 메서드
 */
void showAlchemyWorkshop()
{
    int shopChoice;
    bool isValidSelection = false; // 0번 선택했을 경우만 True로 변경
    string keyword;

    clearScreen();

    do
    {
        cout << "=== Potion Shop ===" << endl;
        cout << "1. Show all recipes" << endl;
        cout << "2. Search by potion name" << endl;
        cout << "3. Search by ingredient" << endl;
        cout << "4. Crafting a Potion" << endl;
        cout << "0. Go back\n" << endl;
        cout << "Choice: ";
        if (!(cin >> shopChoice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            shopChoice = -1;
        }
        cout << endl;

        switch (shopChoice)
        {
            // 되돌아가기
            case 0:
            {
                isValidSelection = true;
                clearScreen();
                break;
            }
            // 전체 레시피 보기
            case 1:
            {
                cout << "[ Potion Recipes ]" << endl;
                showAllRecipes();
                clearScreen();
                break;
            }
            // 포션 이름으로 검색
            case 2:
            {
                cout << "Search potion name: ";
                getline(cin >> ws, keyword);
                searchByName(keyword);
                break;
            }
            // 재료로 검색
            case 3:
            {
                cout << "Search ingredient: ";
                getline(cin >> ws, keyword);
                searchByIngredient(keyword);
                break;
            }
            // 포션 제작
            case 4:
            {
                cout << "Potion name to create: ";
                getline(cin >> ws, keyword);
                craftingPotion(keyword);
                clearScreen();
                break;
            }
            // 이외의 숫자 선택
            default:
            {
                cout << "Invalid choice. Please select again!" << endl;
                clearScreen();
                break;
            }
        }

    } while (!isValidSelection);
}

// 전투 관련 메서드
/*
 * @brief 플레이어 공격 처리 메서드
 * @return 몬스터가 죽으면 true 반환
 */
bool handlePlayerAttack(Player* player, Monster* monster)
{
    int damage = player->attack(monster);

    cout << monster->getName() << " HP: " << monster->getHp() << " -> ";
    monster->setHp(monster->getHp() - damage);
    cout << monster->getHp() << (monster->getHp() <= 0 ? " (Dead)" : "\n") << endl;

    return monster->getHp() <= 0;
}

/*
 * @brief 몬스터 공격 처리 메서드
 */
void handleMonsterAttack(Monster* monster, Player* player)
{
    cout << "--- " << monster->getName() << " Turn ---" << endl;

    int damage = monster->attack(player);

    cout << player->getName() << " HP: " << player->getHp() << " -> ";
    player->setHp(player->getHp() - damage);
    cout << player->getHp() << (player->getHp() <= 0 ? " (Dead)" : "") << endl;
}

/*
 * @brief 전투 메서드
 * @param player: 전투를 수행할 플레이어 객체
 * @param monster: 전투 대상 몬스터 객체
 * @return 플레이어 승리 시 true / 몬스터 승리 시 false
 */ 
bool battle(Player* player, Monster* monster)
{
    clearScreen();

    string playerName = player->getName();
    string monsterName = monster->getName();
    int round = 1;

    cout << "[ Battle Start! ] " << playerName << "(" << player->getJob() << ") vs " << monsterName << endl << endl;

    // 전투 루프: 둘 중 하나가 사망할 때까지 반복
    while (player->getHp() > 0 && monster->getHp() > 0)
    {
        int action;
        bool turnEnd = false;
        cout << "===============================" << endl;
        cout << "      [ " << round++ << " Round Start!! ]" << endl;
        cout << "===============================" << endl;
        cout << "\n--- " << playerName << " Turn ---" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Use Item" << endl;
        cout << "3. Crafting a Potion" << endl;
        cout << "Choose: ";

        // 입력 유효성 검사
        if (!(cin >> action))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input. Please enter a number (1-3)." << endl;
            continue;
        }

        cout << endl;

        while (!turnEnd)
        {
            // 전투
            if (action == 1)
            {
                if (handlePlayerAttack(player, monster)) return true;
                turnEnd = true;
            }
            // 아이템 사용 (아이템 사용 시에만 턴 종료)
            else if (action == 2) { turnEnd = handleItemMenu(player); }
            // 포션 제작
            else if (action == 3)
            {
                string keyword;
                showAllRecipes();

                cout << "Potion name to create: ";
                getline(cin >> ws, keyword);

                craftingPotion(keyword);
                turnEnd = true;

                cout << endl;
            }
            else { cout << "Invalid choice. Please select again!" << endl; }
        }

        // 몬스터 반격
        if (turnEnd && monster->getHp() > 0)
        {
            handleMonsterAttack(monster, player);
            clearScreen();
        }
    }

    return player->getHp() > 0;
}

/*
 * @brief 전투 결과 출력 메서드 
 * @param battleResult: 전투 결과
 * @param player: 플레이어
 * @param monster: 전투 몬스터
 * @return 플레이어 승리 시 true / 몬스터 승리 시 false
 */
void battleResultPrint(bool battleResult, Monster* monster, Player* player)
{
    if (battleResult)
    {
        // 결과 출력
        cout << "\n\n★ Victory!" << endl;
        cout << "  -> Got: " << monster->getDropItemName() << "!" << endl;
        cout << "  -> Saved to inventory." << endl;

        // exp 증가
        player->setExp(player->getExp() + monster->getExpReward());
        cout << "  -> +" << monster->getExpReward() << " EXP! (EXP: " << player->getExp() << "/" << player->getMaxExp() << ")" << endl;

        // 레벨업
        while (player->getExp() >= player->getMaxExp())
        {
            player->setExp(player->getExp() - player->getMaxExp());
            levelUp(player);
        }

        // 인벤토리에 아이템 추가
        addItem(monster->getDropItemName(), "", 0, monster->getDropItemPrice(), 1, false);
    }
    else
    {
        cout << "★ Defeat.." << endl;
        cout << "  -> " << player->getName() << " was attacked by " << monster->getName() << " and died." << endl;
        cout << "Please try again!" << endl;
    }
}

// 던전 관련 메서드
/*
 * @brief 던전 맵 선택 메서드
 * @param player: 플레이어
 * 맵 선택 및 전투 유지 or 메인으로 돌아가기 선택 진행
 */
void enterDungeon(Player* player)
{
    int castleChoice;
    bool isValid = false;

    // 던전 선택
    do
    {
        clearScreen();
        cout << "=== Select Castle ===" << endl;
        cout << "1. Slime Castle (Progress: " << slimeProgress << "/3)" << endl;
        cout << "2. Goblin Castle (Progress: " << goblinProgress << "/3)" << endl;
        cout << "3. Orc Castle (Progress: " << orcProgress << "/3)" << endl;
        cout << "0. Go Back" << endl;
        cout << "Choice: ";
        
        // 입력 유효성 검사
        if (!(cin >> castleChoice))
        {
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            cout << "\nInvalid input. Please enter a number (0-3)." << endl;
            continue;
        }

        // 범위 검사 (0~3 사이인지 확인)
        if (castleChoice >= 0 && castleChoice <= 3) { isValid = true; }
        else {
            cout << "\nInvalid selection. Please choose between 0 and 3." << endl;
            continue;
        }
    } while (!isValid);

    vector<Monster*>* selectedCastle = nullptr;
    int* currentProgress = nullptr;

    if (castleChoice == 1) { selectedCastle = &slimeCastle; currentProgress = &slimeProgress; }
    else if (castleChoice == 2) { selectedCastle = &goblinCastle; currentProgress = &goblinProgress; }
    else if (castleChoice == 3) { selectedCastle = &orcCastle; currentProgress = &orcProgress; }
    else if (castleChoice == 0) { return; }

    if (currentProgress == nullptr || selectedCastle == nullptr) { return; }

    if (*currentProgress >= 3)
    {
        cout << "\nThis castle is already conquered!" << endl;
        return;
    }

    // 성 내부 탐험
    while (*currentProgress < 3)
    {
        Monster * monster = (*selectedCastle)[*currentProgress];
        cout << "\n>>> Exploring... A " << monster->getName() << " appears!" << endl;

        if (battle(player, monster))
        {
            battleResultPrint(true, monster, player);
            (*currentProgress)++; 
            
            if (*currentProgress == 3)
            {
                cout << "\n★ CONQUERED! You defeated the Boss of this castle!" << endl;
                break;
            }

            clearScreen();

            // 더 탐험할지 선택
            int moveChoice;
            bool isMoveValid = false;

            do
            {
                cout << "[ Battle Won! ]" << endl;
                cout << "1. Keep Exploring (Next: " << (*selectedCastle)[*currentProgress]->getName() << ")" << endl;
                cout << "0. Go To Main" << endl;
                cout << "Choice: ";

                if (!(cin >> moveChoice))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input. Please enter 1 or 2." << endl;
                    continue;
                }

                if (moveChoice == 1 || moveChoice == 0) { isMoveValid = true; }
                else
                {
                    cout << "\nInvalid selection. Please choose 1 or 0." << endl;
                    clearScreen();
                }
            } while (!isMoveValid);

            if (moveChoice == 0)
            {
                cout << "\nGoing to Main..." << endl;
                break;
            }
        }
        else
        {
            battleResultPrint(false, monster, player);
            break; // 사망 시 루프 탈출
        }
    }
}

/*
 * @brief 기본 포션&레시피 추가
 */
void initDefaultData()
{
    potionRecipe.push_back({ "HP Potion", {{"Herb", 1}, {"Clear Water", 1}} });
    potionRecipe.push_back({ "MP Potion", {{"Herb", 1}, {"Berry", 1}} });
    addItem("HP Potion", "HP", 50, 50, 5, true);
    addItem("MP Potion", "MP", 50, 50, 5, true);
    addItem("Herb", "0", 0, 20, 1, false);
    addItem("Berry", "0", 0, 20, 1, false);
    addItem("Clear Water", "0", 0, 20, 1, false);
}

/*
 * @brief 몬스터 생성
 */
void initCastles()
{
    slimeCastle.push_back(new Slime("Green Slime", "tackles you!", "Clear Water", 20, 80, 55, 50, 40));
    slimeCastle.push_back(new Slime("Big Slime", "bounces on you!", "Herb", 40, 180, 65, 60, 80));
    slimeCastle.push_back(new Slime("King Slime", "spits sticky acid!", "Berry", 60, 450, 85, 75, 200));

    goblinCastle.push_back(new Goblin("Goblin Scout", "stabs with a dagger!", "Clear Water", 20, 70, 65, 55, 50));
    goblinCastle.push_back(new Goblin("Goblin Warrior", "kicks your shin!", "Herb", 40, 150, 75, 65, 120));
    goblinCastle.push_back(new Goblin("Goblin Shaman", "throws a sharp rock!", "Berry", 60, 400, 95, 80, 300));

    orcCastle.push_back(new Orc("Orc Grunt", "punches you hard!", "Clear Water", 20, 120, 70, 65, 60));
    orcCastle.push_back(new Orc("Orc Warrior", "slams you with a shield!", "Herb", 40, 250, 85, 75, 150));
    orcCastle.push_back(new Orc("Orc Warlord", "swings a heavy axe!", "Berry", 60, 800, 100, 90, 600));
}

// 포션 수 변경(도전 과제1)
/*
본인은 객체의 멤버변수로 포션을 저장해두어 해당 함수가 필요 없음
과제 수행을 위해 작성만 해둔 상태
포션 사용은 getter/setter로 진행 중
포인터를 쓰지 않고 매개변수만 넘겼을 때 값이 바뀌지 않는 이유를 설명: 
-> 포인터를 사용하지 않으면 매개변수로 값을 넘길 때 값의 복사가 이루어지므로 원본에는 영향을 주지 않음.
따라서 포인터를 안쓰면 매개변수로 넘긴 값을 바꿔도 원본 값이 바뀌지 않음

void setPotion(int count, int* p_HPPotion, int* p_MPPotion)
{
    *p_HPPotion = count;
    *p_MPPotion = count;
}
*/

int main()
{
    srand((unsigned int)time(NULL));

    // 변수 선언
    string name;                // 캐릭터 이름
    int stat[4] = { 0 };		// 캐릭터 스탯 { "HP", "MP", "공격력", "방어력" }
    Player* player = nullptr;   // 플레이어

    // 초기 데이터 추가
    initDefaultData();
    initCastles();

    // 1. 게임 프롤로그 시작 
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
    if (!(cin >> jobChoice))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        jobChoice = -1;
    }
    cout << endl;

    // 직업 할당
    while (!isValidSelection)
    {
        switch (jobChoice)
        {
            case 1:
            {
                cout << "* You became a Warrior! (Defense +30)" << endl;
                player = new Warrior(name, stat);
                isValidSelection = !isValidSelection;
                break;
            }
            case 2:
            {
                cout << "* You became a Mage! (MP +30)" << endl;
                player = new Magician(name, stat);
                isValidSelection = !isValidSelection;
                break;
            }
            case 3:
            {
                cout << "* You became a Archer! (Attack +30)" << endl;
                player = new Archer(name, stat);
                isValidSelection = !isValidSelection;
                break;
            }
            case 4:
            {
                cout << "* You became a Thief! (Attack +30)" << endl;
                player = new Thief(name, stat);
                isValidSelection = !isValidSelection;
                break;
            }
            default:
            {
                cout << "Invalid choice. Please select again!" << endl;
                cout << "Choice: ";
                if (!(cin >> jobChoice))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    jobChoice = -1;
                }
                break;
            }
        }
    }

    // 프롤로그 후 최종 플레이어 정보 출력
    player->attack();
    player->printPlayerStatus(); 

    clearScreen();

    // 2. 메인
    bool isGameOver = false;

    while (!isGameOver)
    {
        // 레벨 17 달성 시 게임 종료
        if (player->getLevel() >= 17)
        {
            cout << "===========================================" << endl;
            cout << "   YOU HAVE REACHED LEVEL 17!              " << endl;
            cout << "   ALL MONSTERS DEFEATED, PEACE RESTORED!  " << endl;
            cout << "   CONGRATULATIONS, GREAT HERO!            " << endl;
            cout << "===========================================" << endl;
            isGameOver = true;
            break;
        }
        int menuChoice;

        cout << "=== Main Menu ===" << endl;
        cout << "1. Enter Dungeon" << endl;
        cout << "2. Check Inventory" << endl;
        cout << "3. Sort Inventory" << endl;
        cout << "4. AlchemyWorkshop" << endl;
        cout << "5. UpgradeCharacter" << endl;
        cout << "0. Quit" << endl << endl;

        cout << "Choice: ";
        if (!(cin >> menuChoice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (menuChoice)
        {
            // 게임 종료
            case 0:
            {
                isGameOver = true;
                break;
            }
            // 던전 입장
            case 1:
            {
                enterDungeon(player);
                if (player->getHp() <= 0) isGameOver = true;
                clearScreen();
                break;
            }
            // 인벤토리 확인
            case 2:
            {
                playerInventory.PrintAllItems();
                clearScreen();
                break;
            }
            // 인벤토리 정렬
            case 3:
            {
                playerInventory.SortItems();
                clearScreen();
                break;
            }
            // 포션 제작소
            case 4:
            {
                showAlchemyWorkshop();
                break;
            }
            // 스탯 업그레이드
            case 5:
            {
                Item* hpPotion = playerInventory.GetItem(playerInventory.FindItem("HP Potion"));
                Item* mpPotion = playerInventory.GetItem(playerInventory.FindItem("MP Potion"));

                player->upgradeCharacter(hpPotion, mpPotion);
                playerInventory.UpdateTotalCount();

                int currentHpIdx = playerInventory.FindItem("HP Potion");
                if (currentHpIdx != -1)
                {
                    Item* item = playerInventory.GetItem(currentHpIdx);
                    if (item->getCount() <= 0)
                    {
                        delete item;
                        playerInventory.RemoveItem(currentHpIdx);
                    }
                }

                int currentMpIdx = playerInventory.FindItem("MP Potion");
                if (currentMpIdx != -1)
                {
                    Item* item = playerInventory.GetItem(currentMpIdx);
                    if (item->getCount() <= 0)
                    {
                        delete item;
                        playerInventory.RemoveItem(currentMpIdx);
                    }
                }

                clearScreen();
                break;
            }
            // 이외의 숫자 선택
            default:
            {
                cout << "Invalid choice. Please select again!" << endl;
                clearScreen();
                break;
            }
        }
    }

    // 3. 메모리 해제
    if (player != nullptr)
    {
        delete player;
        player = nullptr;
    }
    for (int i = 0; i < playerInventory.GetSize(); ++i)
        delete playerInventory.GetItem(i);

    return 0;
}
