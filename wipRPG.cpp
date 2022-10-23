#include <iostream>
#include <string>
#include <cstdlib>
#include <array>
using namespace std;

class Enemies {
    private:
        string enemyList[2] = 
            {"2->Rat->10->Scratch->1->10->1->Bite->2->5->1->end", "2->Bat->12->Bite->2->5->1->Screech->1->3->2->end"};
        //List contains number of attacks, name, hp, attack name, attack damage
        //probability to miss for each attack, and probability to crit (deal double damage) for each attack

        string name;
        int hp;
        int attackCount;
        string* attackArray = new string[16];

    public:
        void setName(string n){
            name = n;
        }
        string getName(){
            return name;
        }

        void setHP(int i) {
            hp = i;
        }
        int getHP(){
            return hp;
        }

        void setAttackCount(int a){
            attackCount = a;
        }
        int getAttackCount(){
            return attackCount;
        }

        void setAttackArray(string info, int index){
            attackArray[index] = info;
        }

        string getAttackArray(int index){
            return attackArray[index];
        }

        string* setEnemy(int playerLevel) {
            srand((unsigned) time(NULL));
            int enemyIndexRange = 2; //With more enemies later, it'll be calculated with more math
            string enemyIndex = enemyList[rand() % enemyIndexRange];
            const int infoArraySize = 4 + (((int)enemyIndex[0]) * 4);

            string* enemyInfo = new string[infoArraySize];
            string delimiter = "->";
            size_t position;
            
            int i = 0;
            while((position = enemyIndex.find(delimiter)) != string::npos){
                enemyInfo[i] = enemyIndex.substr(0, position);
                enemyIndex.erase(0, position + delimiter.length());
                i++;
            }

            return enemyInfo;
        }
};

class Player {
    private:
        int xp;
        int level;
        string* actionInfo = new string[4];
        int hp;
        string* output = new string[2];

    public:
        void setXP(int x){
            xp = x;
        }
        int getXP() {
            return xp;
        }

        void setLevel(int l){
            level = l;
        }
        int getLevel(){
            return level;
        }

        //Each action contains name, damage probability to miss, and probability to crit
        void setActionInfo(string action, int index) {
            actionInfo[index] = action;
        }
        string getActionInfo(int index){
            return actionInfo[index];
        }

        void setHP(int h) {
            hp = h;
        }
        int getHP(){
            return hp;
        }

        void setOutput(string damage, string status) {
            output[0] = damage;
            output[1] = status;
        }
};

class Battle {
    private:
        int playerLevel;
        int playerXP;
        void battleLoop(Player player) {
            int enemyCount = rand() % 4 + 1;
            Enemies* enemies = new Enemies[enemyCount];
            
            cout << "Zoo wee mama! ";
            for(int i = 0; i < enemyCount; i++) {
                string* enemyInfo = enemies[i].setEnemy(playerLevel);
                enemies[i].setName(enemyInfo[1]);
                enemies[i].setHP(stoi(enemyInfo[2]));
                enemies[i].setAttackCount(stoi(enemyInfo[0]));
                int x = enemies[i].getAttackCount()*4;
                for(int j = 0; j < x; j++){
                    enemies[i].setAttackArray(enemyInfo[j+3], j);
                }
                cout << enemies[i].getName();
                if(i < enemyCount-2 && enemyCount > 2){
                    cout << ", ";
                }
                if(i == enemyCount-2){
                    cout << " and ";
                }
            }
            cout << " blocks your way!\n";
            cout << "What would you like to do?\n";
            
            while(enemyCount > 0 && player.getHP() > 0) {
                cout << "\n1. Attack\n2. Spells\n3. Items\n4. Run\n(Your HP: " << player.getHP() << ")\n";
                int actionChoice;
                cin >> actionChoice;

                switch(actionChoice) {
                    case 1:
                        cout << "\n1. " << player.getActionInfo(0) << "\n";
                        int attackChoice;
                        cin >> attackChoice;

                        switch(attackChoice) {
                            case 1:
                                player.setOutput(player.getActionInfo(1), "");
                                int missChance = rand() % 100 + 1;
                                int critChance = rand() % 100 + 1;
                                for(int i = 0; i < enemyCount; i++){
                                    cout << "\n" << i+1 << ". " << enemies[i].getName() << "(HP: " << enemies[i].getHP() << ")";
                                }
                                cout << "\n";

                                int enemyChoice;
                                cin >> enemyChoice;

                                switch(enemyChoice) {
                                    case 1:
                                        if(missChance >= stoi(player.getActionInfo(2))) {
                                            if(critChance <= stoi(player.getActionInfo(3))) {
                                                cout << "Holy guacamole! You hit " << enemies[0].getName() << " for " << (stoi(player.getActionInfo(1))*2) <<  " damage!\n";
                                                enemies[0].setHP(enemies[0].getHP() - stoi(player.getActionInfo(1))*2);
                                            } else {
                                                cout << "You hit " << enemies[0].getName() << " for " << stoi(player.getActionInfo(1)) <<  " damage!\n";
                                                enemies[0].setHP(enemies[0].getHP() - stoi(player.getActionInfo(1)));
                                            }
                                        } else {
                                            cout << "Oh no! You missed!\n";
                                        }

                                        if(enemies[0].getHP() <= 0){
                                            cout << "You defeated " << enemies[0].getName() << "!\n";

                                            for(int i=0;i < enemyCount - 1;i++) {
                                                enemies[i] = enemies[i+1];
                                            }
                                            enemyCount--;
                                        }

                                        break;
                                    case 2:
                                        if(enemies[1].getName() != ""){
                                            if(missChance >= stoi(player.getActionInfo(2))) {
                                            if(critChance <= stoi(player.getActionInfo(3))) {
                                                cout << "Holy guacamole! You hit " << enemies[1].getName() << " for " << (stoi(player.getActionInfo(1))*2) <<  " damage!\n";
                                                enemies[1].setHP(enemies[1].getHP() - stoi(player.getActionInfo(1))*2);
                                            } else {
                                                cout << "You hit " << enemies[1].getName() << " for " << stoi(player.getActionInfo(1)) <<  " damage!\n";
                                                enemies[1].setHP(enemies[1].getHP() - stoi(player.getActionInfo(1)));
                                            }
                                            } else {
                                                cout << "Oh no! You missed!\n";
                                            }

                                            if(enemies[1].getHP() <= 0){
                                                cout << "You defeated " << enemies[1].getName() << "\n";

                                                for(int i=1;i < enemyCount - 1;i++) {
                                                    enemies[i] = enemies[i+1];
                                                }

                                                enemyCount--;
                                            }
                                        }
                                        break;
                                    case 3:
                                        if(enemies[2].getName() != ""){
                                            if(missChance >= stoi(player.getActionInfo(2))) {
                                            if(critChance <= stoi(player.getActionInfo(3))) {
                                                cout << "Holy guacamole! You hit " << enemies[2].getName() << " for " << (stoi(player.getActionInfo(1))*2) <<  " damage!\n";
                                                enemies[2].setHP(enemies[2].getHP() - stoi(player.getActionInfo(1))*2);
                                            } else {
                                                cout << "You hit " << enemies[2].getName() << " for " << stoi(player.getActionInfo(1)) <<  " damage!\n";
                                                enemies[2].setHP(enemies[2].getHP() - stoi(player.getActionInfo(1)));
                                            }
                                            } else {
                                                cout << "Oh no! You missed!\n";
                                            }

                                            if(enemies[2].getHP() <= 0){
                                                cout << "You defeated " << enemies[2].getName() << "\n";

                                                for(int i=1;i < enemyCount - 1;i++) {
                                                    enemies[i] = enemies[i+1];
                                                }

                                                enemyCount--;
                                            }
                                        }
                                        break;
                                    case 4:
                                        if(enemies[3].getName() != ""){
                                            if(missChance >= stoi(player.getActionInfo(2))) {
                                            if(critChance <= stoi(player.getActionInfo(3))) {
                                                cout << "Holy guacamole! You hit " << enemies[3].getName() << " for " << (stoi(player.getActionInfo(1))*2) <<  " damage!\n";
                                                enemies[3].setHP(enemies[3].getHP() - stoi(player.getActionInfo(1))*2);
                                            } else {
                                                cout << "You hit " << enemies[3].getName() << " for " << stoi(player.getActionInfo(1)) <<  " damage!\n";
                                                enemies[3].setHP(enemies[3].getHP() - stoi(player.getActionInfo(1)));
                                            }
                                            } else {
                                                cout << "Oh no! You missed!\n";
                                            }

                                            if(enemies[3].getHP() <= 0){
                                                cout << "You defeated " << enemies[3].getName() << "\n";

                                                for(int i=1;i < enemyCount - 1;i++) {
                                                    enemies[i] = enemies[i+1];
                                                }

                                                enemyCount--;
                                            }
                                        }
                                        break;
                                }
                                break;
                        }
                        break;
                }

                for(int i = 0; i < enemyCount; i++) {
                    int chosenAttack = rand() % enemies[i].getAttackCount();
                    int missChance = rand() % 100 + 1;
                    int critChance = rand() % 100 + 1;

                    cout << "\n" << enemies[i].getName() << " uses " << enemies[i].getAttackArray(chosenAttack*4) << "\n";

                    if(missChance >= stoi(enemies[i].getAttackArray((chosenAttack*4) + 2))) {
                        if(critChance <= stoi(enemies[i].getAttackArray((chosenAttack*4) + 3))) {
                            cout << "Bummer! It hits you for " << stoi(enemies[i].getAttackArray((chosenAttack*4) + 1))*2 <<  " damage!\n";
                            player.setHP(player.getHP() - (stoi(enemies[i].getAttackArray((chosenAttack*4) + 1))*2));
                        } else {
                            cout << "It hits for " << stoi(enemies[i].getAttackArray((chosenAttack*4) + 1)) <<  " damage!\n";
                            player.setHP(player.getHP() - stoi(enemies[i].getAttackArray((chosenAttack*4) + 1)));
                        }
                    } else {
                        cout << enemies[i].getName() << " missed! Lucky you!\n";
                    }
                }
            }

            if(enemyCount <= 0){
                endBattle(player, 'w');
            }
            if(player.getHP() <= 0){
                endBattle(player, 'l');
            }
            
        }

        void endBattle(Player player, char endCondition) {
            Battle battle;
            char playAnswer;
            switch(endCondition) {
                case 'w':
                    cout << "Nice one! All the enemies were defeated. Would you like to keep going? (y/n)\n";
                    cin >> playAnswer;
                    switch(playAnswer){
                        case 'y':
                            cout << "\nHave Fun!\n";
                            battle.battleLoop(player);
                            break;
                        case 'n':
                            cout << "\nBye!";
                            break;
                    }
                    break;
                case 'l':
                    cout << "Oh no! Looks like you were defeated. Would you like to try again? (y/n)\n";
                    cin >> playAnswer;
                    switch(playAnswer){
                        case 'y':
                            cout << "\nHave Fun!\n";
                            battle.gameStart();
                            break;
                        case 'n':
                            cout << "\nBye!";
                            break;
                    }
            }
        }

    public:
        void gameStart(){
            Player player;
            player.setLevel(1);
            player.setXP(0);
            player.setActionInfo("Bash", 0);
            player.setActionInfo("4", 1);
            player.setActionInfo("1", 2);
            player.setActionInfo("1", 3);
            player.setHP(20);
            //add player classes later? (fighter, mage, etc.)
            battleLoop(player);
        }
};

int main() {
    cout << "Welcome to WIP RPG: The RPG where I don't know how to finish this.\n";
    cout << "Would you like to know the rules? (y/n)\n";

    char rulesAnswer;
    cin >> rulesAnswer;
    Battle battle;

    switch(rulesAnswer){
        case 'y':
            cout << "\nIn this game, you are given an unlimited amount of fights until you lose or give up.\n";
            cout << "You can attack with weapons, conjure spells, use items, or run!\n";
            cout << "You can choose from menus by typing the number into the command line\n";
            cout << "For example:\n1. Attack\n2. Spells\n3. Items\n4. Run\n";
            cout << "Here, typing 1 will let you attack, typing 2 let's you pick spells, etc.\n";
            cout << "Are you ready to play? (y/n)\n";
            char playAnswer;
            cin >> playAnswer;
            switch(playAnswer){
                case 'y':
                    cout << "\nHave Fun!\n";
                    battle.gameStart();
                    return 0;
                    break;
                case 'n':
                    cout << "\nBye!";
                    return 0;
                    break;
                default:
                    cout << "\nI'm assuming that's a no. Bye!";
                    return 0;
                    break;
            }
            break;
        case 'n':
            cout << "\nHave Fun!\n";
            battle.gameStart();
            return 0;
            break;
        default:
            cout << "\nI'm assuming that's a no. Bye!";
            return 0;
            break;
    }
    
}