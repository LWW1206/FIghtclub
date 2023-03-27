#include <iostream>
#include <vector>
#include <string.h>
#include <ctime>

using namespace std;

enum spell {criting = 1, boosting = 2};
enum spell2 {healing = 1, debuffing = 2};

class character {
protected:
    string name;
    int spell_1;
    int spell_2;
    int health;
    int attack;
    int totalwins;
    int totalloses;

public:
    character(string s, int s1, int s2, int h, int att, int t_w, int t_l):
        name(s), spell_1(s1), spell_2(s2), health(h), attack(att), totalwins(t_w), totalloses(t_l) {
        //cout << "character " << s << "been made " << endl ;
        }

    static character* copymyself(character &vec){
        character* character_ptr = new character(vec.name, vec.spell_1, vec.spell_2, vec.health, vec.attack, vec.totalwins, vec.totalloses);
        return character_ptr;
    }

    virtual void print() {
        cout << "*******************************************************" << endl;
        cout << "Name: " << name << endl;
        cout << "Spell1: " << spell_1 << endl;
        cout << "Spell2: " << spell_2 << endl;
        cout << "Health: " << health << endl;
        cout << "Attack: " << attack << endl;
        cout << "Totalwins: " << totalwins << endl;
        cout << "Totalloses: " << totalloses << endl;
        cout << "*******************************************************" << endl;
    }

    void printstat(){
        cout << "Name: " << name << endl;
        cout << "Health: " << health << endl;
        cout << "Attack: " << attack << endl;
    }

    string getname(){return this -> name;}
    void setatt(int x) {this -> attack = x; }
    int getspell_1(){ return this -> spell_1;}
    int getspell_2() { return this -> spell_2;}
    int getattack() { return this -> attack;}
    void boostatt() {this->attack++;}
    void debuff() {this->attack--;}
    int gethealth() {return this->health;}
    void sethealth(int value) {this->health = value;}
    void win(){this->totalwins++;}
    void lose(){this->totalloses++;}

    virtual ~character() {
    //cout << "Character " << name << " is being destructed." << endl;
}

};

class decisiontree{
public:
    void eventhandler(character* ptr){
        int currhealth = ptr->gethealth();
        if (currhealth < 50){
            cout << "Current HP is under 50, Character will now regain 2 HP per round! " << endl;
            ptr->sethealth(currhealth + 2);
        }
        if(currhealth < 20){
            cout << "Current HP is under 20, Character will now also get +2 ATK per round! " << endl;
            ptr->setatt(ptr->getattack() + 2);
        }
    }
};

class suzy: public character {
public:
    suzy(string s, int s1, int s2, int h, int att, int t_w, int t_l): character(s, s1, s2, h, att, t_w, t_l) {}

    ~suzy() {
    //cout << "destructed in suzy class." << endl;
}

};

class claude: public character {
public:
    claude(string s, int s1, int s2, int h, int att, int t_w, int t_l): character(s, s1, s2, h, att, t_w, t_l) {}

    ~claude() {
    //cout << "destructed in claude class." << endl;
}
};

class player: public character {
public:
    void setname(string input){this -> name = input;}
    void setskill_1(int input){this -> spell_1 = input; }
    void setskill_2(int input){this -> spell_2 = input; }
    void setloadout(int value1, int value2){this -> health = value1; this -> attack = value2; }
    void makechar(){
        string s;
        int input;
        cout << "Give your character a name!" << endl;
        cin >> s;
        setname(s);
        cout << "Which Skill_1 would you like to have?" << endl << "1 = criting, 2 = boosting" << endl;
        cin >> input;
        if (input == 1){
            setskill_1(1);
        }
        if (input == 2) {
            setskill_1(2);
        }
        cout << "Which Skill_2 would you like to have?" << endl << "1 =healing, 2 = debuffing" << endl;
        cin >> input;
        if (input == 1){
            setskill_2(1);
        }
        if (input == 2) {
            setskill_2(2);
        }
        cout << "Choose a more offensive or defensive loadout" << endl << "1 = 80 HP -- 12 ATK; 2 = 100 HP -- 10 ATK" << endl;
        cin >> input;
        if (input == 1){
            setloadout(80, 12);
        }
        if (input == 2){
            setloadout(100, 10);
        }
    }

    player():character("void", 0, 0, 0, 0, 0, 0) {
        makechar();
    }
    ~player() {
    //cout << "Character " << name << " is being destructed in player class." << endl;
}
};

class game {
    public:
        int team_size;
        character* char1;
        character* char2;
        bool status;
        bool bot;

        game(): status(true), bot(false) {}

        ~game () {
        // cout << "game destructed" << endl;
        }

};

void attack(character* ptr, character* enemyptr){
    int dmg = ptr->getattack();
    enemyptr->sethealth( enemyptr->gethealth() - dmg);
}

void crit(character* ptr, character* enemyptr){   // not permanent only valid for one round
    int actual_attack = ptr->getattack();
    int dmg = actual_attack * 2;
    ptr->setatt(dmg);
    attack(ptr, enemyptr);
    ptr->setatt(actual_attack);
    cout << "Character crit the enemy for 200% of its normal ATK (not permanent)" << endl;
}

void boost_(character* ptr, character* enemyptr){ // permanent valid forever
    ptr->boostatt();
    attack(ptr, enemyptr);
    cout << "Characters ATK permanently increased by one and attack Enemy" << endl;
}

void debuff(character* ptr){ // permanent valid forever
    ptr->debuff();
    cout << "Enemy Characters Attack has been permanently decreased by 1" << endl;
}

void healing_(character* ptr){  // not permanent only valid for one round
    int currhealth = ptr->gethealth();
    ptr->sethealth(currhealth + 5);
    cout << "Characters HP: +5" << endl;
}

bool checkgamestatus(game* newgame){
    int h1 = newgame->char1->gethealth();
    int h2 = newgame->char2->gethealth();
    if (h1 <= 0){
        cout << "Character 1 has lost!" << endl;
        newgame->char1->lose();
        newgame->char2->win();
       return false;
    }
    else if (h2 <= 0){
        cout << "Character 2 has lost!" << endl;
        newgame->char2->lose();
        newgame->char1->win();
        return false;
    }
    return true;
}

int return_num(int x) {
    return rand () % x;
}

void playgame(game* newgame){
    decisiontree dt;
    //cout << "in here 1" << endl;
    string name1 = newgame->char1->getname();
    //cout << "in here 2" << endl;
    string name2 = newgame->char2->getname();
    //cout << "in here 3" << endl;
    int char1_s1 = newgame->char1->getspell_1();
    int char1_s2 = newgame->char1->getspell_2();
    int char2_s1 = newgame->char2->getspell_1();
    int char2_s2 = newgame->char2->getspell_2();
    do {
        int input;
        cout << "Which Skill do you want to use; Character: " << name1 << endl;
        cout << "Your character has " << "Spell_1(1): " << ((char1_s1 == criting) ? "criting" : "boosting") << " -- "
        << "Spell_2(2): " << ((char1_s2 == healing) ? "healing" : "debuffing") << endl;
        cin >> input;
        if (input == 1)
            (char1_s1 == criting) ? crit(newgame->char1, newgame->char2) : boost_(newgame->char1, newgame->char2);
        else if(input == 2)
            (char1_s2 == healing) ? healing_(newgame->char1) : debuff(newgame->char2);

        if(checkgamestatus(newgame)!= true){
            newgame->status = false;
            break;
        }
        dt.eventhandler(newgame->char1);
        newgame->char1->printstat();
        cout << "----------------------------------------------------------------------------------------------"<< endl;

        if(newgame->bot == true){
            cout << "the computer will play for you" << endl;
            input = return_num(2) +1;
        }
        else{
          cout << "Which Skill do you want to use; Character: " << name2 << endl;
            cout << "Your character has " << "Spell_1(1): " << ((char2_s1 == criting) ? "criting" : "boosting") << " -- "
            << "Spell_2(2): " << ((char2_s2 == healing) ? "healing" : "debuffing") << endl;
            cin >> input;
        }
        if(input == 1)
            (char2_s1 == criting) ? crit(newgame->char2, newgame->char1) : boost_(newgame->char2, newgame->char1);
        else if(input == 2)
            (char2_s2 == healing) ? healing_(newgame->char2) : debuff(newgame->char1);

        if(checkgamestatus(newgame)!= true){
            newgame->status = false;
            break;
        }
        dt.eventhandler(newgame->char2);
        newgame->char2->printstat();
        cout << "----------------------------------------------------------------------------------------------" << endl;

    }while(newgame->status == true);

    cout << "Statistics of the Characters" << endl;
    newgame->char1->print();
    newgame->char2->print();
}

void make_char(vector <player> &vect, int &cnt){
    player* newplayer = new player;
    vect.push_back(*newplayer);
    vect[cnt].print();
    cnt++;
}

void show_char(vector <player> vect){
    cout << "You have made follwing characters, you can choose them as template: " << endl;
            vector<player>::iterator iter = vect.begin();
            for (; iter != vect.end(); iter++){
                (*iter).print();
            }
}

character* createteam(suzy* suzy_ptr, claude* claude_ptr, vector <player> vect, int &count){
    int input;
    while(1){
    cout << "Choose a character for the team, please be careful to only input something valid -- 1 = suzy; 2 = claude 3 = character made by you" << endl;
    cin >> input;
    if(input == 1 && count != 1) {
        count = 1;
        return suzy_ptr;
        break;
        }
    else if(input == 2 && count != 2) {
        count = 2;
        return claude_ptr;
        break;
    }
    else if(input == 3){
        show_char(vect);
        cout << "Choose a Character u have made, input their index number to chose them" << endl;
        cin >> input;
        //character copy1("base", 0, 0, 0, 0, 0, 0);
        return character::copymyself(vect[input]);
        break; //not needed
    }
    else{
       cout << "Dont choose a suzy or claude again/ Enter smt valid!" << endl;
        continue;
    }
    }
    return nullptr;
}

void menu(suzy* suzy_ptr, claude* claude_ptr, game* newgame, vector <player> vect) {
    int count = 0;
    newgame->char1 = createteam(suzy_ptr, claude_ptr, vect, count);
    newgame->char2 = createteam(suzy_ptr, claude_ptr, vect, count);

    newgame->char1->print();
    newgame->char2->print();
}

void reset (character* ptr, int health, int atk){
    ptr->sethealth(health);
    ptr->setatt(atk);
}

void activate_bot (game* ptr){
    string input;
    while(1){
    cout << "Do you want to play against the computer? enter: y(yes), n(no)" << endl;
    cin >> input;
    if(input[0] != 'y' && input[0] != 'n'){
        cout << "enter smt valid" << endl;
        continue;
    }
    else if (input[0] == 'y'){
       ptr->bot = true;
        break;
    }
    else
        break;
    }
}

int main() {
    srand(time(NULL));
    int player_cnt = 0;
    character character("base", 0, 0, 0, 0, 0, 0);
    suzy* suzy_ptr = new suzy("suzy", 1, 1, 80, 12, 0, 0);
    claude* claude_ptr = new claude("claude", 2, 2, 100, 10, 0 , 0);
    vector <player> player_vector;

    string input;
    game* game_ptr = new game;
    cout << "Welcome to fight club" << endl << "You can choose between predesigned characters(suzy, claude) or make a own character" << endl;
    cout << "The characters will battle each other until one of them has no more HP left" << endl << "After that you can decide to restart the game" << endl;
    do{
        cout << "To play a game press enter (p) to quit enter (x) to make a character enter (m) to show all playermade characters enter(s)" << endl;
        cin >> input;
        if(input[0] != 'p' && input[0] != 'x' && input[0] != 's' && input[0] != 'm'){
            cout << "please input a valid character" << endl;
            continue;
        }
        else if(input[0] == 'p'){
            reset(suzy_ptr, 80, 12);
            reset(claude_ptr, 100, 10);
            menu(suzy_ptr, claude_ptr, game_ptr, player_vector);
            activate_bot(game_ptr);
            cout << "The teams you have picked are: " << endl;
            game_ptr->char1->printstat();
            game_ptr->char2->printstat();
            playgame(game_ptr);
            game_ptr->status = true;
        }
        else if (input[0] == 'm'){
            make_char(player_vector, player_cnt);
        }
        else if (input[0] == 's'){
            show_char(player_vector);
        }
        else if (input[0] == 'x'){
           game_ptr->status = false;
            break;
        }
    }while(game_ptr->status == true);

    delete suzy_ptr;
    delete claude_ptr;
    delete game_ptr;

    return 0;
}