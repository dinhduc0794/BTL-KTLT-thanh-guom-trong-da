#include "knight2.h"

bool isPrime(int n){
    if (n < 2){
        return 0;
    }
    for (int i = 2; i <= sqrt(n); i++){
        if (n % i == 0) return 0;
    }
    return 1;
}

bool isPythagoras(int n){
    if (n < 100 || n > 999) return 0;  
    int a, b, c;
    c = n % 10;
    n /= 10;
    b = n % 10;
    n /= 10;
    a = n;
    if (a*a + b*b == c*c || a*a + c*c == b*b || b*b + c*c == a*a) return 1;
    return 0;
}

/* * * BEGIN implementation of class Event * * */
Events::Events(const string file_events){
    ifstream file_in(file_events);
    //doc so luong su kien o dong 1
    file_in >> e;  
    //tao mang dong de luu ma su kien
    eventCode = new int[e];
    for (int i = 0; i < e; i++){
        file_in >> eventCode[i];
    }
}
Events::~Events(){
    delete[] eventCode;
}
/* * * END implementation of class Event * * */

/* * * BEGIN implementation of class BaseBag * * */
int BaseBag::count() const{
    int cnt = 0;
    BaseItem* p = head;
    while (p != NULL){
        ++cnt;
        p = p->next;
    }
    return cnt;
}
string BaseBag::listItem() const{
    string s = "";
    string typeString[5] = {"Antidote", "PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV"};
    BaseItem* p = head;
    while (p != NULL){
        s = s + typeString[p->name] + ",";
        p = p->next;
    }
    //xoa dau , o cuoi cung
    if (!s.empty() && s.back() == ','){
        s.erase(s.size() - 1);
    }  
    return s;
}
string BaseBag::toString() const{  
    string s("");
    s += "Bag[count=" 
        + to_string(count()) 
        + ";" 
        + listItem() 
        + "]";
    return s;
}
BaseItem* BaseBag::makeBItem(ItemType itemType){
    BaseItem* newItem = NULL;
    if (itemType == ANTIDOTE) 
        newItem = new Antidote;
    if (itemType == PHOENIXDOWNI)
        newItem = new PhoenixDownI;
    if (itemType == PHOENIXDOWNII)
        newItem = new PhoenixDownII;
    if (itemType == PHOENIXDOWNIII)
        newItem = new PhoenixDownIII;
    if (itemType == PHOENIXDOWNIV)
        newItem = new PhoenixDownIV;
    // newItem->name = itemType;
    // newItem->next = NULL;
    return newItem;
}
void BaseBag::usePhoenixDown(BaseKnight* knight){
    BaseItem* temp = head;
    //duyet dslk
    while (temp != NULL){
        //tim phoenixdown
        if (temp->name == PHOENIXDOWNI || temp->name == PHOENIXDOWNII || temp->name == PHOENIXDOWNIII || temp->name == PHOENIXDOWNIV){
            //neu co the su dung phoenix bat ki thi su dung luon
            if (temp->canUse(knight)){  
                temp->use(knight);
                knight->getBag()->get(temp->name);   //doi cho va xoa phoenix vua su dung
                break;
            }
        }
        temp = temp->next;
    }
}
void BaseBag::getPoisoned(BaseKnight* knight){
    //neu tim thay Antidote thi ko trung doc
    if (knight->getKnightType() == DRAGON || knight->getBag()->get(ANTIDOTE) != NULL) return; 
    //trung doc
    else{
        knight->setHp(knight->getHp() - 10);    //hp-10
        //item < 3 thi bag rong
        if (knight->getBag()->count() < 3) head = NULL;  
        //danh roi 3 item gan nhat
        else{
            for (int i = 0; i < 3; i++){
                head = head->next;
            }
        }
    }
}

//PALADIN BAG
bool PaladinBag::insertFirst(BaseItem * item){
    item->next = head;
    head = item;
    return 1;
}

BaseItem* PaladinBag::get(ItemType itemType) {
    BaseItem* found = nullptr; // Node chứa item cần tìm
    BaseItem* temp = head;     // Node chạy
    BaseItem* prev = nullptr;  // Node phía trước node chạy

    // Duyệt danh sách liên kết
    while (temp != nullptr) {
        // Tìm vật phẩm
        if (temp->name == itemType) {
            found = temp;
            break;
        }
        prev = temp;           // Node phía trước chuyển thành node hiện tại
        temp = temp->next;     // Node hiện tại chuyển thành node kế tiếp để duyệt danh sách
    }

    // Nếu tìm thấy vật phẩm
    if (found != nullptr) {
        // Nếu vật phẩm không ở đầu bag
        if (prev != nullptr) {
            prev->next = found->next;  // Cho node trước found trỏ vào node sau found
        } 
        // Nếu vật phẩm ở đầu bag
        else {
            head = found->next;  // Chuyển con trỏ head sang phần tử thứ hai
        }
        found->next = nullptr;  // Cắt liên kết của found khỏi danh sách
        //lim++         // Tăng số lượng đã xóa chỉ khi tìm thấy phần tử
    }

    return found;  // Trả về nullptr sau khi xóa phần tử
}

PaladinBag::PaladinBag(int phoenixdownI, int antidote){
    if (phoenixdownI > 0){
        for (int i = 0; i < phoenixdownI; i++){
            insertFirst(makeBItem(PHOENIXDOWNI));
        }
    }
    if (antidote > 0){
        for (int i = 0; i < antidote; i++){
            insertFirst(makeBItem(ANTIDOTE));
        }
    }
}

//LANCELOT BAG
bool LancelotBag::insertFirst(BaseItem * item){
    if (limOfLanBag <= 0) return 0;
    item->next = head;
    head = item;
    limOfLanBag--;
    return 1;
}
BaseItem* LancelotBag::get(ItemType itemType) {
    BaseItem* found = nullptr; // Node chứa item cần tìm
    BaseItem* temp = head;     // Node chạy
    BaseItem* prev = nullptr;  // Node phía trước node chạy

    // Duyệt danh sách liên kết
    while (temp != nullptr) {
        // Tìm vật phẩm
        if (temp->name == itemType) {
            found = temp;
            break;
        }
        prev = temp;           // Node phía trước chuyển thành node hiện tại
        temp = temp->next;     // Node hiện tại chuyển thành node kế tiếp để duyệt danh sách
    }

    // Nếu tìm thấy vật phẩm
    if (found != nullptr) {
        // Nếu vật phẩm không ở đầu bag
        if (prev != nullptr) {
            prev->next = found->next;  // Cho node trước found trỏ vào node sau found
        } 
        // Nếu vật phẩm ở đầu bag
        else {
            head = found->next;  // Chuyển con trỏ head sang phần tử thứ hai
        }
        
        found->next = nullptr;  // Cắt liên kết của found khỏi danh sách
        limOfLanBag++;          // Tăng số lượng đã xóa chỉ khi tìm thấy phần tử
    }

    return found;  // Trả về nullptr sau khi xóa phần tử
}

LancelotBag::LancelotBag(int phoenixdownI, int antidote){
    if (phoenixdownI > 0){
        for (int i = 0; i < phoenixdownI; i++){
            insertFirst(makeBItem(PHOENIXDOWNI));
        }
    }
    if (antidote > 0){
        for (int i = 0; i < antidote; i++){
            insertFirst(makeBItem(ANTIDOTE));
        }
    }
}

//DRAGON BAG
bool DragonBag::insertFirst(BaseItem * item){
    if (limOfDraBag <= 0) return 0;
    item->next = head;
    head = item;
    limOfDraBag--;
    return 1;
}
BaseItem* DragonBag::get(ItemType itemType) {
    BaseItem* found = nullptr; // Node chứa item cần tìm
    BaseItem* temp = head;     // Node chạy
    BaseItem* prev = nullptr;  // Node phía trước node chạy

    // Duyệt danh sách liên kết
    while (temp != nullptr) {
        // Tìm vật phẩm
        if (temp->name == itemType) {
            found = temp;
            break;
        }
        prev = temp;           // Node phía trước chuyển thành node hiện tại
        temp = temp->next;     // Node hiện tại chuyển thành node kế tiếp để duyệt danh sách
    }

    // Nếu tìm thấy vật phẩm
    if (found != nullptr) {
        // Nếu vật phẩm không ở đầu bag
        if (prev != nullptr) {
            prev->next = found->next;  // Cho node trước found trỏ vào node sau found
        } 
        // Nếu vật phẩm ở đầu bag
        else {
            head = found->next;  // Chuyển con trỏ head sang phần tử thứ hai
        }
        
        found->next = nullptr;  // Cắt liên kết của found khỏi danh sách
        limOfDraBag++;          // Tăng số lượng đã xóa chỉ khi tìm thấy phần tử
    }

    return found;  // Trả về nullptr sau khi xóa phần tử
}

DragonBag::DragonBag(int phoenixdownI, int antidote){
    if (phoenixdownI > 0){
        for (int i = 0; i < phoenixdownI; i++){
            insertFirst(makeBItem(PHOENIXDOWNI));
        }
    }
    if (antidote > 0){
        for (int i = 0; i < antidote; i++){
            insertFirst(makeBItem(ANTIDOTE));
        }
    }
}

//NORMAL BAG
bool NormalBag::insertFirst(BaseItem * item){
    if (limOfNorBag <= 0) return 0;
    item->next = head;
    head = item;
    limOfNorBag--;
    return 1;
}
BaseItem* NormalBag::get(ItemType itemType) {
    BaseItem* found = nullptr; // Node chứa item cần tìm
    BaseItem* temp = head;     // Node chạy
    BaseItem* prev = nullptr;  // Node phía trước node chạy

    // Duyệt danh sách liên kết
    while (temp != nullptr) {
        // Tìm vật phẩm
        if (temp->name == itemType) {
            found = temp;
            break;
        }
        prev = temp;           // Node phía trước chuyển thành node hiện tại
        temp = temp->next;     // Node hiện tại chuyển thành node kế tiếp để duyệt danh sách
    }

    // Nếu tìm thấy vật phẩm
    if (found != nullptr) {
        // Nếu vật phẩm không ở đầu bag
        if (prev != nullptr) {
            prev->next = found->next;  // Cho node trước found trỏ vào node sau found
        } 
        // Nếu vật phẩm ở đầu bag
        else {
            head = found->next;  // Chuyển con trỏ head sang phần tử thứ hai
        }
        
        found->next = nullptr;  // Cắt liên kết của found khỏi danh sách
        limOfNorBag++;          // Tăng số lượng đã xóa chỉ khi tìm thấy phần tử
    }

    return found;  // Trả về nullptr sau khi xóa phần tử
}

NormalBag::NormalBag(int phoenixdownI, int antidote){
    if (phoenixdownI > 0){
        for (int i = 0; i < phoenixdownI; i++){
            insertFirst(makeBItem(PHOENIXDOWNI));
        }
    }
    if (antidote > 0){
        for (int i = 0; i < antidote; i++){
            insertFirst(makeBItem(ANTIDOTE));
        }
    }
}

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseItem * * */
//ANTIDOTE
Antidote::Antidote(){
    this->name = ANTIDOTE;
    this->next = NULL;
}
//PHOENIXDOWNI
PhoenixDownI::PhoenixDownI(){
    this->name = PHOENIXDOWNI;
    this->next = NULL;
}
bool PhoenixDownI::canUse (BaseKnight * knight){
    return knight->getHp() <= 0;
}
void PhoenixDownI::use (BaseKnight * knight){
    knight->setHp(knight->getMaxHp());
}
//PHOENIXDOWNII
PhoenixDownII::PhoenixDownII(){
    this->name = PHOENIXDOWNII;
    this->next = NULL;
}
bool PhoenixDownII::canUse (BaseKnight * knight){
    return knight->getHp() < (knight->getMaxHp()/4);
}
void PhoenixDownII::use (BaseKnight * knight){
    knight->setHp(knight->getMaxHp());
}
//PHOENIXDOWNIII
PhoenixDownIII::PhoenixDownIII(){
    this->name = PHOENIXDOWNIII;
    this->next = NULL;
}
bool PhoenixDownIII::canUse (BaseKnight * knight){
    return knight->getHp() < (knight->getMaxHp()/3);
}
void PhoenixDownIII::use (BaseKnight * knight){
    if (knight->getHp() <= 0){
        knight->setHp(knight->getMaxHp()/3);
    }
    else{
        knight->setHp(knight->getHp() + knight->getMaxHp()/4);
    }
}
//PHOENIXDOWNIV
PhoenixDownIV::PhoenixDownIV(){
    this->name = PHOENIXDOWNIV;
    this->next = NULL;
}
bool PhoenixDownIV::canUse(BaseKnight * knight){
    return knight->getHp() < (knight->getMaxHp()/2);
}
void PhoenixDownIV::use (BaseKnight * knight){
    if (knight->getHp() <= 0){
        knight->setHp(knight->getMaxHp()/2);
    }
    else{
        knight->setHp(knight->getHp() + knight->getMaxHp()/5);
    }
}
/* * * END implementation of class BaseItem * * */

/* * * BEGIN implementation of class BaseKnight * * */

//check knight type
bool checkPaladin(int hp){
    if (isPrime(hp)) return true;
    return false;
}
bool checkLancelot(int hp){
    if (hp == 888) return true;
    return false;
}
bool checkDragon(int hp){
    if (isPythagoras(hp)) return true;
    return false;
}
bool checkNormal(int hp){
    if (checkPaladin(hp) || checkLancelot(hp) || checkDragon(hp)) return false;
    return true;
}

// PALADIN
Paladin::Paladin(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    this->id = id;
    this->maxhp = maxhp;
    this->hp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
    this->knightType = PALADIN;
    //tao bag phu hop va add phoenixdownI, antidote
    PaladinBag *bag = new PaladinBag(phoenixdownI, antidote);
    this->bag = bag;
}
Paladin::~Paladin(){
    if (bag) delete bag;
    bag = nullptr;
}
//LANCELOT
Lancelot::Lancelot(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    this->id = id;
    this->maxhp = maxhp;
    this->hp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
    this->knightType = LANCELOT;
    //tao bag phu hop va add phoenixdownI, antidote
    LancelotBag *bag = new LancelotBag(phoenixdownI, antidote);
    this->bag = bag;
}
Lancelot::~Lancelot(){
    if (bag) delete bag;
    bag = nullptr;
}
//DRAGON
Dragon::Dragon(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    this->id = id;
    this->maxhp = maxhp;
    this->hp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
    this->knightType = DRAGON;
    //tao bag phu hop va add phoenixdownI, antidote
    DragonBag *bag = new DragonBag(phoenixdownI, antidote);
    this->bag = bag;
}
Dragon::~Dragon(){
    if (bag) delete bag;
    bag = nullptr;
}
//NORMAL
Normal::Normal(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    this->id = id;
    this->maxhp = maxhp;
    this->hp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
    this->knightType = NORMAL;
    //tao bag phu hop va add phoenixdownI, antidote
    NormalBag *bag = new NormalBag(phoenixdownI, antidote);
    this->bag = bag;
}
Normal::~Normal(){
    if (bag) delete bag;
    bag = nullptr;
}

//tao knight
BaseKnight * BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    //check hp va tao knight phu hop
    if (checkPaladin(maxhp)) {
        Paladin *knight = new Paladin(id, maxhp, level, gil, antidote, phoenixdownI);
        return knight;
    }
    else if (checkLancelot(maxhp)){
        Lancelot *knight = new Lancelot(id, maxhp, level, gil, antidote, phoenixdownI);
        return knight;
    }
    else if (checkDragon(maxhp)){
        Dragon *knight = new Dragon(id, maxhp, level, gil, antidote, phoenixdownI);
        return knight;
    }
    else{
        Normal *knight = new Normal(id, maxhp, level, gil, antidote, phoenixdownI);
        return knight;
    }
}
//in
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s="";
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType] 
        + "]";
    return s;
}

//xu li su kien
void BaseKnight::setHp_1to5(BaseOpponent * opponent){
    hp = hp - opponent->baseDamage * (opponent->levelO - level);
}
void BaseKnight::setGil_1to5(BaseOpponent * opponent){
    gil += opponent->opgil;
    if (gil > 999) gil = 999;
}
void BaseKnight::levelUp(){
    this->level++;
    if (this->level > 10) this->level = 10;
}
void BaseKnight::nhan2Gil(){
    this->gil *= 2;
}
void BaseKnight::chia2Gil(){
    this->gil /= 2;
}
void BaseKnight::setHpGil_8(){
    if (this->knightType == PALADIN){
        if (this->hp < (this->maxhp)/3)
            this->hp += (this->maxhp)/5;
    }
    else{
        if (this->gil < 50) return;
        if (this->hp < (this->maxhp)/3){
            this->gil -= 50;
            this->hp += (this->maxhp)/5;
        }
    }
}
void BaseKnight::setHptoMaxHp(){
    this->hp = this->maxhp;
}
void BaseKnight::maxLevelmaxGil(){
    this->level = 10;
    this->gil = 999;
}
void BaseKnight::revival(){
    if (this->gil >= 100){
        this->hp = (this->maxhp)/2;
        this->gil -= 100;
    }
}

int UltimeciaHP = 5000;

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class BaseOpponent * * */
MadBear::MadBear(int i){
    eventID = 1;
    baseDamage = 10;
    opgil = 100;
    levelO = (i + eventID)%10 + 1;
}
Bandit::Bandit(int i){
    eventID = 2;
    baseDamage = 15;
    opgil = 150;
    levelO = (i + eventID)%10 + 1;
}
LordLupin::LordLupin(int i){
    eventID = 3;
    baseDamage = 45;
    opgil = 450;
    levelO = (i + eventID)%10 + 1;
}
Elf::Elf(int i){
    eventID = 4;
    baseDamage = 75;
    opgil = 750;
    levelO = (i + eventID)%10 + 1;
}
Troll::Troll(int i){
    eventID = 5;
    baseDamage = 95;
    opgil = 800;
    levelO = (i + eventID)%10 + 1;
}
Tornbery::Tornbery(int i){
    eventID = 6;
    levelO = (i + eventID)%10 + 1;
}
QueenOfCards::QueenOfCards(int i){
    eventID = 7;
    levelO = (i + eventID)%10 + 1;
}
NinaDeRings::NinaDeRings(){
    eventID = 8;
    // levelO = (i + eventID)%10 + 1;
}
DurianGarden::DurianGarden(){
    eventID = 9;
    // levelO = (i + eventID)%10 + 1;
}
OmegaWeapon::OmegaWeapon(){
    eventID = 10;
    // levelO = (i + eventID)%10 + 1;
}
Hades::Hades(){
    eventID = 11;
    // levelO = (i + eventID)%10 + 1;
}
Ultimecia::Ultimecia(){
    eventID = 99;
}
/* * * END implementation of class BaseOpponent * * */

/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights (const string & file_armyknights){
    ifstream file_in(file_armyknights);
    //doc so luong knight o dong 1
    file_in >> n_knights;
    //tao mang dong de luu n knight
    knight = new BaseKnight[n_knights];
    //loop nhap du lieu cho n knight
    for (int i = 0; i < n_knights; i++){
        int id = i+1;
        //tao bien cuc bo de luu thong so
        int maxhp, level, phoenixdownI, gil, antidote;
        file_in >> maxhp >> level >> phoenixdownI >> gil >> antidote;
        //create tra ve &knight -> giai tham chieu de lay gia tri cho knight thu i
        knight[i] = *knight[i].create(id, maxhp, level, gil, antidote, phoenixdownI);
    }
}
ArmyKnights::~ArmyKnights(){
    delete[] knight;
    knight = nullptr;
}

void ArmyKnights::truyenGilDu(){
    if (n_knights <= 1) return; //so luong hiep si la 1 thi khong truyen gil
    //duyet nguoc tu hiep si cuoi cung ve hiep si dau tien
    for (int i = n_knights - 1; i >= 0; i--){
        //neu du gil
        if (knight[i].getGil() > 999){
            knight[i].gilDu = knight[i].getGil() - 999; //gil du bang tong gil - so gil toi da
            knight[i].setGil(999);
        }
        if (knight[i].gilDu > 0){
            knight[i-1].setGil(knight[i-1].getGil() + knight[i].gilDu); //tang gil cho hiep si dung truoc
        }
        //neu het gil du va hiep si nhan gil ko vuot qua gil toi da thi ket thuc 
        if (knight[i].gilDu == 0 && knight[i-1].getGil() <= 999) break;  
        knight[i].gilDu = 0;    //cap nhat gil du ve 0
    }
}
bool ArmyKnights::hasPaladinShield() const {
    if (palaShield > 0) return 1;
    else return 0;
}
bool ArmyKnights::hasLancelotSpear() const {
    if (lancSpear > 0) return 1;
    else return 0;
}
bool ArmyKnights::hasGuinevereHair() const {
    if (guinHair > 0) return 1;
    else return 0;
}
bool ArmyKnights::hasExcaliburSword() const {
    if (excaSword > 0) return 1;
    else return 0;
}

void ArmyKnights::fightUltimecia(BaseKnight* knight){
    for (int i = n_knights - 1; i >= 0; i--){
        if (knight[i].getKnightType() == PALADIN){
            UltimeciaHP -= knight[i].getHp() * knight[i].getLevel() * 0.06;
            if (UltimeciaHP > 0){
                knight[i].setHp(0);
                n_knights--;
            }
        }
        else if (knight[i].getKnightType() == LANCELOT){
           UltimeciaHP -= knight[i].getHp() * knight[i].getLevel() * 0.05;
            if (UltimeciaHP > 0){
                knight[i].setHp(0);
                n_knights--;
            }
        }
        else if (knight[i].getKnightType() == DRAGON){
            UltimeciaHP -= knight[i].getHp() * knight[i].getLevel() * 0.075;
            if (UltimeciaHP > 0){
                knight[i].setHp(0);
                n_knights--;
            }
        }
        else if (knight[i].getKnightType() == NORMAL){
            continue;
        }
        if (UltimeciaHP <= 0) break;
    }
}

bool ArmyKnights::fight(BaseOpponent * opponent){
    BaseKnight * lknight = lastKnight();
    //lay thuoc tinh eventID tu opponent truyen vao, roi dem so sanh
    switch (opponent->eventID){      
        case 1:
        {        
            //neu thang
            if (lknight->getLevel() >= opponent->levelO  || lknight->getKnightType() == LANCELOT || lknight->getKnightType() == PALADIN){
                lknight->setGil_1to5(opponent);    //tang gil tuong ung voi madbear
            }
            //neu thua
            else{
                //giam hp
                lknight->setHp_1to5(opponent); 
                //luc tim thuoc hoi mau
                lknight->getBag()->usePhoenixDown(lknight);
                //neu van chet thi bo gil hoi sinh
                if (lknight->getHp() <= 0)
                    lknight->revival();
            }
            //neu du gil thi truyen cho hiep si truoc
            truyenGilDu();
            break;
        }
        case 2:
        {   
            if (lknight->getLevel() >= opponent->levelO || lknight->getKnightType() == LANCELOT || lknight->getKnightType() == PALADIN){
                lknight->setGil_1to5(opponent);
            }
            else{
                lknight->setHp_1to5(opponent);
                lknight->getBag()->usePhoenixDown(lknight);
                if (lknight->getHp() <= 0)
                    lknight->revival();
            }
            truyenGilDu();
            break;
        }
        case 3:
        {   
            if (lknight->getLevel() >= opponent->levelO || lknight->getKnightType() == LANCELOT || lknight->getKnightType() == PALADIN){
                lknight->setGil_1to5(opponent);
            }
            else{
                lknight->setHp_1to5(opponent);
                lknight->getBag()->usePhoenixDown(lknight);
                if (lknight->getHp() <= 0)
                    lknight->revival();
            }
            truyenGilDu();
            break;
        }
        case 4:
        {   
            if (lknight->getLevel() >= opponent->levelO || lknight->getKnightType() == LANCELOT || lknight->getKnightType() == PALADIN){
                lknight->setGil_1to5(opponent);
            }
            else{
                lknight->setHp_1to5(opponent);
                lknight->getBag()->usePhoenixDown(lknight);
                if (lknight->getHp() <= 0)
                    lknight->revival();
            }
            truyenGilDu();
            break;
        }
        case 5: 
        {
            if (lknight->getLevel() >= opponent->levelO || lknight->getKnightType() == LANCELOT || lknight->getKnightType() == PALADIN){
                lknight->setGil_1to5(opponent);
            }
            else{
                lknight->setHp_1to5(opponent);
                lknight->getBag()->usePhoenixDown(lknight);
                if (lknight->getHp() <= 0)
                    lknight->revival();
            }
            truyenGilDu();
            break;
        }
        case 6:
        {
            if (lknight->getLevel() >= opponent->levelO){
                lknight->levelUp();   //tang level len 1
            }
            else{
                lknight->getBag()->getPoisoned(lknight);
                lknight->getBag()->usePhoenixDown(lknight);
                if (lknight->getHp() <= 0)
                    lknight->revival();
            }
            break;
        }
        case 7:
        {   
            if (lknight->getLevel() >= opponent->levelO){
                lknight->nhan2Gil();
            }
            else{
                if (lknight->getKnightType() == PALADIN) break;
                else lknight->chia2Gil();    
            }
            truyenGilDu();  
            break;
        case 8:
            lknight->setHpGil_8(); //doi gil lay hp
            break;
        case 9:
            lknight->setHptoMaxHp();  //tang hp len maxhp
            break;
        }
        case 10:
        {    
            //neu da thang OmegaWeapon roi thi bo qua
            if (wonOmegaWeapon) break;  
            //kiem tra da thang OmegaWeapon chua, neu thang thi bat wonOmegaWeapon len 1
            bool level10_va_maxHp = (lknight->getLevel() == 10) && (lknight->getHp() == lknight->getMaxHp());
            bool dragon = checkDragon(lknight->getMaxHp());
            if (level10_va_maxHp || dragon){
                wonOmegaWeapon = 1;
                //level va tien max 
                lknight->maxLevelmaxGil();
            }
            else{
                lknight->setHp(0);
                lknight->getBag()->usePhoenixDown(lknight);
                if (lknight->getHp() <= 0)
                    lknight->revival();
            }
            break;
        }
        case 11:
        {    
            //neu da thang Hades roi thi bo qua
            if (wonHades) break;
            //kiem tra da thang Hades chua, neu thang thi bat wonHades len 1
            bool level10 = lknight->getLevel() == 10;
            bool paladin_va_level8 = (checkPaladin(lknight->getMaxHp())) && (lknight->getLevel() >= 8);
            if (level10 || paladin_va_level8){
                wonHades = 1;
                //hades ren khien Paladin
                palaShield = true;
            }
            else{
                lknight->setHp(0);
                lknight->getBag()->usePhoenixDown(lknight);
                if (lknight->getHp() <= 0)
                    lknight->revival();
            }
            break;
        }
        case 99:
        {
            if (hasExcaliburSword()){
                UltimeciaHP = 0;
                break;
            }
            else if (hasPaladinShield() && hasLancelotSpear() && hasGuinevereHair()){
                fightUltimecia(lknight);
                if (UltimeciaHP <= 0) break;
                else{
                    for (int i = 0; i < n_knights; i++){
                        knight[i].setHp(0);
                        n_knights = 0;
                    }
                }
            }
            else{
                for (int i = 0; i < n_knights; i++){
                    knight[i].setHp(0);
                    n_knights = 0;
                }
            }
            bool isAllNormal = true;
            for (int i = 0; i < n_knights; i++){
                if (knight[i].getKnightType() == PALADIN || knight[i].getKnightType() == LANCELOT || knight[i].getKnightType() == DRAGON)
                    isAllNormal = false;
            }
            if (isAllNormal) return false;
            break;
        }
    }
    if (lknight->getHp() <= 0) return false;
    return true;
}

bool ArmyKnights::adventure (Events * events){
    for (int i = 0; i < events->count(); i++){
        BaseKnight * lknight = lastKnight();
        switch (events->get_eventCode(i)){
            case 1:
            {
                //create opponent
                MadBear* madbear = new MadBear(i);
                //vi fight chi end khi hiep si hoi sinh hoac ca doi quan hiep si hi sinh
                //khi fight(opponent) tra ve true (win) -> while(false) -> chi danh 1 lan
                //fight(opponent) return false (thua) -> while(true) -> danh den khi nao thang hoac chet het thi thoi
                if (!fight(madbear)){
                    n_knights--;
                }
                break;
            }
            case 2:
            {
                Bandit* bandit = new Bandit(i);
                if(!fight(bandit)){
                    n_knights--;
                }
                break;
            }
            case 3: 
            {
                LordLupin* lupin = new LordLupin(i);
                if(!fight(lupin)){
                    n_knights--;
                }
                break;
            }
        
            case 4:
            {
                Elf* elf = new Elf(i);
                if(!fight(elf)){
                    n_knights--;
                }
                break;
            }
             case 5:
            {
                Troll* troll = new Troll(i);
                if(!fight(troll)){
                    n_knights--;
                }
                break;
            }
            case 6:
            {
                Tornbery* tornbery = new Tornbery(i);
                if(!fight(tornbery)){
                    n_knights--;
                }
                break;
            }
           
            case 7:
            {
                QueenOfCards* queen = new QueenOfCards(i);
                if(!fight(queen)){
                    n_knights--;
                }
                break;
            }
            case 8:
            {
                NinaDeRings* nina = new NinaDeRings();
                if(!fight(nina)){
                    n_knights--;
                }
                break;
            }
            case 9:
            {   DurianGarden* durian = new DurianGarden();
                if(!fight(durian)){
                    n_knights--;
                }
                break;
            }
            case 10:
            {
                OmegaWeapon* omega = new OmegaWeapon();
                if(!fight(omega)){
                    n_knights--;
                }
                break;
            }
            case 11:
            {
                Hades* hades = new Hades();
                if(!fight(hades)){
                    n_knights--;
                }
                break;
            }
            case 112:
            {
                lknight->getBag()->insertFirst(lknight->getBag()->makeBItem(PHOENIXDOWNII));
                break;
            }
            case 113:
            {
                lknight->getBag()->insertFirst(lknight->getBag()->makeBItem(PHOENIXDOWNIII));
                break;
            }
            case 114:
            {
                lknight->getBag()->insertFirst(lknight->getBag()->makeBItem(PHOENIXDOWNIV));
                break;
            }
            case 95:
            {
                palaShield = 1;
                break;
            }
            case 96:
            {
                lancSpear = 1;
                break;
            }
            case 97:
            {
                guinHair = 1;
                break;
            }
            case 98:
            {
                if (hasPaladinShield() && hasLancelotSpear() && hasGuinevereHair()) excaSword = 1;
                break;
            }
            case 99:
            {
                Ultimecia* ultimecia = new Ultimecia;
                fight(ultimecia);
                break;
            }
        }
        printInfo();    //n = 0 van phai in 
        if (n_knights <= 0) return false;
    }
    return true;
}

void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}
/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure(){
    armyKnights = NULL;
    events = NULL;
}
void KnightAdventure::loadArmyKnights(const string & file_armyknights){
    armyKnights = new ArmyKnights(file_armyknights);    
}
void KnightAdventure::loadEvents(const string & file_events){
    events = new Events(file_events);       
}
void KnightAdventure::run(){
    armyKnights->printResult(armyKnights->adventure(events));
}   
KnightAdventure::~KnightAdventure(){
    delete armyKnights;
    armyKnights = nullptr;
    delete events;
    events = nullptr;
}
/* * * END implementation of class KnightAdventure * * */