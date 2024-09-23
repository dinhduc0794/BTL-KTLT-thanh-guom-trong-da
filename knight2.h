#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

//function
bool isPrime(int n);
bool isPythagoras(int n);
//check knight type
bool checkPaladin(int hp);
bool checkLancelot(int hp);
bool checkDragon(int hp);
bool checkNormal(int hp);

//class
class BaseItem;
class BaseKnight;
class ArmyKnight;
class BaseOpponent;
class Events;
class BaseBag;

class Events{
private:
    int e;
    int* eventCode;
public:
    Events(const string file_event);
    ~Events();
    int count() const{return e;}  //so luong su kien
    int get_eventCode(int i) const{return eventCode[i];}    //ma su kien thu i
};

class BaseOpponent{
public:
    int eventID;
    int baseDamage;
    int opgil;
    int levelO;
};
class MadBear:public BaseOpponent{
public:
    MadBear(int i);
};
class Bandit:public BaseOpponent{
public:
    Bandit(int i);
};
class LordLupin:public BaseOpponent{
public:
    LordLupin(int i);
};  
class Elf:public BaseOpponent{
public:
    Elf(int i);
};
class Troll:public BaseOpponent{
public:
    Troll(int i);
};
class Tornbery:public BaseOpponent{
public:
    Tornbery(int i);
};
class QueenOfCards:public BaseOpponent{
public:
    QueenOfCards(int i);
};
class NinaDeRings:public BaseOpponent{
public:
    NinaDeRings();
};
class DurianGarden:public BaseOpponent{
public:
    DurianGarden();
};
class OmegaWeapon:public BaseOpponent{ 
public:
    OmegaWeapon();
};
class Hades:public BaseOpponent{
public:
    Hades();
};
class Ultimecia:public BaseOpponent{
public:
    Ultimecia();
};

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };

class BaseKnight {
protected:
    int id;
    int maxhp;
    int hp;
    int level;
    int gil;
    int antidote;
    int phoenixdownI;
    KnightType knightType;
    BaseBag * bag;
    float knightBaseDamage;
    int damage;
public:
    int gilDu = 0;
    //tao va in thong so knight
    BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    //getter lay gia tri 
    int getId(){return id;}
    int getMaxHp(){return maxhp;}
    int getHp(){return hp;}
    int getLevel(){return level;}
    int getGil(){return gil;}
    int getAntidote(){return antidote;}
    int getPhoenixdownI(){return phoenixdownI;}
    KnightType getKnightType(){return knightType;}
    BaseBag * getBag(){return bag;}
    //setter thay doi gia tri
    void setHp(int hp){this->hp = hp;}
    void setLevel(int level){this->level = level;}
    void setGil(int gil){this->gil = gil;}
    //setter cho tung su kien
    void setHp_1to5(BaseOpponent * opponent);
    void setGil_1to5(BaseOpponent * opponent);
    void levelUp();
    void nhan2Gil();
    void chia2Gil();
    void setHpGil_8();
    void setHptoMaxHp();
    void maxLevelmaxGil();
    void revival();
};

class Paladin:public BaseKnight{
public:
    Paladin(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~Paladin();
};
class Lancelot:public BaseKnight{
public:
    Lancelot(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~Lancelot();
};
class Dragon:public BaseKnight{
public:
    Dragon(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~Dragon();
};
class Normal:public BaseKnight{
public:
    Normal(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~Normal();
};

class ArmyKnights {
private:
    int n_knights;
    BaseKnight *knight; //moi quan he has-a, not ke thua
    bool wonOmegaWeapon = 0;
    bool wonHades = 0;
    bool palaShield = 0;
    bool lancSpear = 0;
    bool guinHair = 0;
    bool excaSword = 0;
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const{return n_knights;}    //so luong knight
    BaseKnight * lastKnight() const{return &knight[n_knights-1];}
    void truyenGilDu();
    void fightUltimecia(BaseKnight *knight);

    //method check so huu vat pham dac biet
    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    //method in ket qua
    void printInfo() const;
    void printResult(bool win) const;
};

enum ItemType {ANTIDOTE = 0, PHOENIXDOWNI, PHOENIXDOWNII, PHOENIXDOWNIII, PHOENIXDOWNIV};

class BaseItem {
public:
    //giong struct node trong dslk
    ItemType name;  //data cua item hien tai
    BaseItem *next; //con tro luu dia chi cua item ke tiep
    BaseItem* makeBItem(ItemType itemType);    //make node
    //2 method thuan ao, khong the su dung, chi co the su dung cac phuong thuc ke thua
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};

class Antidote:public BaseItem{
public: 
    Antidote();
    bool canUse (BaseKnight * knight){return 1;};
    void use (BaseKnight * knight){return;};
};
class PhoenixDownI:public BaseItem{
public:
    PhoenixDownI(); 
    bool canUse (BaseKnight * knight);
    void use (BaseKnight * knight);
};
class PhoenixDownII:public BaseItem{
public:
    PhoenixDownII();
    bool canUse (BaseKnight * knight);
    void use (BaseKnight * knight);
};
class PhoenixDownIII:public BaseItem{
public:
    PhoenixDownIII();
    bool canUse (BaseKnight * knight);
    void use (BaseKnight * knight);
};
class PhoenixDownIV:public BaseItem{
public:
    PhoenixDownIV();
    bool canUse (BaseKnight * knight);
    void use (BaseKnight * knight);
};

class BaseBag:public BaseKnight{
public:
    BaseItem* head = NULL;
    BaseKnight* knight;
    ItemType itemType;
    BaseItem* makeBItem(ItemType itemType); //make_node
    virtual bool insertFirst(BaseItem * item) = 0;  //add item
    virtual BaseItem * get(ItemType itemType) = 0;  //lay dia chi item can tim, doi cho voi head, xoa item
    int count() const;  //dem so luong vat pham
    string listItem() const; //danh sach item
    string toString() const;
    void usePhoenixDown(BaseKnight* knight);    //su dung phoenixdown bat ki de hoi mau
    void getPoisoned(BaseKnight* knight);   //trung doc va su dung antidote
};
class PaladinBag:public BaseBag{
public:
    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    PaladinBag(int phoenixdownI, int antidote);
};
class LancelotBag:public BaseBag{
public: 
    int limOfLanBag = 16;   //so luong item toi da
    bool insertFirst(BaseItem * item); 
    BaseItem * get(ItemType itemType);  
    LancelotBag(int phoenixdownI, int antidote);
};
class DragonBag:public BaseBag{
public:
    int limOfDraBag = 14; //so luong item toi da  
    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    DragonBag(int phoenixdownI, int antidote);
};
class NormalBag:public BaseBag{
public:
    int limOfNorBag = 19;
    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    NormalBag(int phoenixdownI, int antidote);
};

class KnightAdventure{
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__