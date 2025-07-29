#include "hcmcampaign.h"
//!----------------------------------------------
//! Lớp Position
//!----------------------------------------------
int Position::getRow() const { return r; }
int Position::getCol() const { return c; }
void Position::setRow(int r) { 
    this->r = std::max(0, r);
}
void Position::setCol(int c) { 
    this->c = std::max(0, c);
}

string Position::str() const {
    stringstream ss;
    ss << "(" << r << "," << c << ")";
    return ss.str();
}

Position::Position(int r, int c) : r(r), c(c)
{
}

Position::Position(const string &str_pos)
{
    int index=1,j=index+1;
        for(j;str_pos[j]!=',';++j);
        istringstream ss1(str_pos.substr(1,j-1));
        ss1>>this->r;
        index=j+1;j=index+1;
        for(j;str_pos[j]!=')';++j);
        istringstream ss2(str_pos.substr(index,j-index));
        ss2>>this->c;
}
//!----------------------------------------------
//! Lớp Unit
//!----------------------------------------------
Unit::Unit(int quantity, int weight, Position pos)
    : quantity(quantity), weight(weight), pos(pos)
{
    markcheckinsert=1;
}



Unit::~Unit()
{
}
Position Unit::getCurrentPosition() const
{
    return pos;
}
//!----------------------------------------------
//! Lớp Infantry
//!----------------------------------------------

int Infantry::summingDigits(int a){
    if(a==0) return 0;
    int i=summingDigits(a/10)+a%10;
    if(i>9) i=summingDigits(i);
    if(i<0) i=-i;
    return i;
}

Infantry::Infantry( int quantity , int weight , const Position pos , InfantryType
    infantryType ): Unit(quantity,weight,pos),infantryType(infantryType){
        if(quantity<=0){ 
            quantity=1;
            this->quantity=quantity;
        }
        if(weight<=0){
             weight=1; 
             this->weight=weight;
        }
        vehi=0;
        this->attackscorestatic=getnewAttackScore(1);
    }; 
int Infantry::getAttackScore(){
    int score=(infantryType*56+quantity*weight);
    int tempscore=score;
    if(infantryType==4&&((int)sqrt(weight)*(int)sqrt(weight))==weight) tempscore+=75;
    int sum=summingDigits(summingDigits(tempscore)+summingDigits(1975));
    if(sum>7){
        quantity = safeCeil(quantity+(0.2)*quantity);
        score=(infantryType*56+quantity*weight);
        setAttackScorestatic(score);
    }
    else if(sum<3){
        quantity = safeCeil(quantity-0.1*quantity);
        score = (infantryType*56+quantity*weight);
        setAttackScorestatic(score);
    }
    return score;
}
int Infantry::getAttackScoreInFight(){
    int score=(infantryType*56+quantity*weight);
    return score;
}
string Infantry::str()const{
    string s="Infantry[infantryType=";
    string temp;
    if(infantryType==0) temp="SNIPER";
    else if(infantryType==1) temp="ANTIAIRCRAFTSQUAD";
    else if(infantryType==2) temp="MORTARSQUAD";
    else if(infantryType==3) temp="ENGINEER";
    else if(infantryType==4) temp="SPECIALFORCES";
    else if(infantryType==5) temp="REGULARINFANTRY";
    s+=(temp+",quantity="+to_string(quantity)+",weight="+to_string(weight)
    +",position=("+to_string(pos.getRow())+","+to_string(pos.getCol())+")]");
    return s;
}

int Infantry::getnewAttackScore(double coefficient){
    int score=getAttackScoreInFight();
    return safeCeil(score*coefficient);
}
//!----------------------------------------------
//! Lớp Vehicle
//!----------------------------------------------

Vehicle::Vehicle(int quantity,int weight,const Position pos,VehicleType
    vehicleType):Unit(quantity,weight,pos),vehicleType(vehicleType){
        if(quantity<=0){ 
            quantity=1;
            this->quantity=quantity;
        }
        if(weight<=0){
             weight=1;
             this->weight=weight;
        }
        vehi=1;
        this->attackscorestatic=getnewAttackScore(1);
    };
    
int Vehicle::getAttackScore(){
    return safeCeil((vehicleType*304+quantity*weight)/(float)30);
}
    
string Vehicle::str()const {
        string s="Vehicle[vehicleType=";
        string temp;
        if(vehicleType==0) temp="TRUCK";
        else if(vehicleType==1) temp="MORTAR";
        else if(vehicleType==2) temp="ANTIAIRCRAFT";
        else if(vehicleType==3) temp="ARMOREDCAR";
        else if(vehicleType==4) temp="APC";
        else if(vehicleType==5) temp="ARTILLERY";
        else if(vehicleType==6) temp="TANK";
        s+=(temp+",quantity="+to_string(quantity)+",weight="+to_string(weight)
        +",position=("+to_string(pos.getRow())+","+to_string(pos.getCol())+")]");
    
        return s;
    }
    
int Vehicle::getnewAttackScore(double coefficient){
        int score=getAttackScore();
        return safeCeil(score*coefficient);
}
//!----------------------------------------------
//! Lớp UnitList
//!----------------------------------------------
UnitList::~UnitList() {
    node* current = list.head;
    while (current != nullptr) {
        node* temp = current;
        current = current->next;
        // if (temp->ownsUnit) {
        //     delete temp->unit; 
        // }
        delete temp;
    }
    list.head=nullptr;
}

// Llist::~Llist(){
//     delete head;
// };

node::~node(){
    if (ownsUnit) {
            delete unit; 
        }
        unit = nullptr;
}



UnitList::UnitList(int S) : countInfantry(0), countVehicle(0)
{
    this->capacity=S;
    list.head = nullptr;
}

nodeinfantry* UnitList::clonenode(nodeinfantry* original) {
    if(original==nullptr) return nullptr;
    nodeinfantry* nodeclone= new nodeinfantry(original);
    return nodeclone;
}

nodevehicle* UnitList::clonenode(nodevehicle* original){
    if(original==nullptr) return nullptr;
    nodevehicle* nodeclone= new nodevehicle(original);
    return nodeclone;
};

UnitList::UnitList( UnitList& original){
    list.head=nullptr;
    node* current = original.getLlist().head;
    while (current!=nullptr){
        if(current->unit->isVehi()){
            nodevehicle* newnode=clonenode(dynamic_cast<nodevehicle*>(current));
            if(list.head==nullptr){
                list.head=newnode;
                newnode=nullptr;
            }
            else { 
                node* current2=list.head;
                while(current2->next!=nullptr){
                    current2=current2->next;
                }
                current2->next=newnode;
                newnode=nullptr;
            }
        }
        else {
            nodeinfantry* newnode=clonenode(dynamic_cast<nodeinfantry*>(current));
            if(list.head==nullptr){
                list.head=newnode;
                newnode=nullptr;
            }
            else { 
                node* current2=list.head;
                while(current2->next!=nullptr){
                    current2=current2->next;
                }
                current2->next=newnode;
                newnode=nullptr;
            }
        }
        current=current->next;
    }
    this->capacity=original.capacity;
    this->countInfantry=original.countInfantry;
    this->countVehicle=original.countVehicle;
}

bool UnitList::insert(Unit *unit)
{
    // TODO: Implement
    if (unit==nullptr) return false;
    if(dynamic_cast<Vehicle*>(unit)) {
        Vehicle* added= (dynamic_cast<Vehicle*>(unit));
        if(this->isContain(added->getVehicleType())) {
            nodevehicle* old=findEqual(added->getVehicleType());
            old->unit->setQuantity(old->unit->getQuantity()+added->getQuantity());
            if(old->unit->getWeight()<added->getWeight()){
                old->unit->setWeight(added->getWeight());
            }
            old->unit->setAttackScorestatic(old->unit->getAttackScore());
            return false;
        }
        else {
            if(this->countVehicle+this->countInfantry<this->capacity){
                nodevehicle* temp= new nodevehicle(dynamic_cast<Vehicle*>(unit),nullptr);
                if (list.head==nullptr) {
                    list.head = temp;
                }
                else{
                    node* current=list.head;
                    while(current->next!=nullptr){
                        current=current->next;
                    }
                    current->next=temp;
                }
                temp=nullptr;
                ++this->countVehicle;
                return true;
            }
        }
        return false;
    }

    else {
        Infantry* added= (dynamic_cast<Infantry*>(unit));
        if(this->isContain(added->getInfantryType())) {
            nodeinfantry* old=findEqual(added->getInfantryType());
            old->unit->setQuantity(old->unit->getQuantity()+added->getQuantity());
            if(old->unit->getWeight()<added->getWeight()){
                old->unit->setWeight(added->getWeight());
            }
            old->unit->setAttackScorestatic(old->unit->getAttackScore());
            return false;        
        }
        else {
            if(this->countVehicle+this->countInfantry<this->capacity){
                nodeinfantry* temp= new nodeinfantry(dynamic_cast<Infantry*>(unit),nullptr);
                if (list.head==nullptr) {
                    list.head = temp;
                }
                else{
                    node* current=list.head;
                    temp->next=list.head;
                    list.head=temp;
                }
                temp=nullptr;
                ++this->countInfantry;
                return true;
            }
        }
        return false;
    }
    return false;
}

bool UnitList::insertLlistBackward(UnitList* original,UnitList* enemy)
{
    // TODO: Implement
    node* current= enemy->getLlist().head;
    if(current==nullptr) return false;
    while(current!=nullptr&&current->unit->getMarkCheckInsert()){
        for(current;current->next!=nullptr&&current->next->unit->getMarkCheckInsert();current=current->next);
        bool insertpoint=original->insert(current->unit);
        if(insertpoint){
            // ++countVehicle;
            // int temp=(enemy->getCountVehicle());
            // enemy->setCountVehicle(--temp);
            enemy->removeNode(enemy->getLlistRef(),current);
        } 
        // else if(insertpoint&&!current->unit->isVehi()){
            // ++countInfantry;
            // int temp=(enemy->getCountInfantry());
            // enemy->setCountInfantry(--temp);
            // enemy->removeNode(enemy->getLlistRef(),current);
        // }
        else if(!insertpoint&&current->unit->isVehi()&&isContain(dynamic_cast<Vehicle*>(current->unit)->getVehicleType())){
            // int temp=(enemy->getCountVehicle());
            // enemy->setCountVehicle(--temp);
            enemy->removeNode(enemy->getLlistRef(),current);
        } 
        else if(!insertpoint&&!current->unit->isVehi()&&isContain(dynamic_cast<Infantry*>(current->unit)->getInfantryType())){
            // int temp=(enemy->getCountInfantry());
            // enemy->setCountInfantry(--temp);
            enemy->removeNode(enemy->getLlistRef(),current);
        } 
        else{
            current->unit->setMarkCheckInsert(0);
        }
        current= enemy->getLlist().head;
    }
    return true;
}

nodevehicle* UnitList::findEqual(VehicleType vehicleType){
    node* current=list.head;
    while(current!=nullptr&&!(dynamic_cast<Vehicle*>(current->unit))){
        current=current->next;
    }
    while(current!=nullptr){
        if(dynamic_cast<Vehicle*>(current->unit)->getVehicleType()==vehicleType){
            return dynamic_cast<nodevehicle*>(current);
        };
        current=current->next;
    }
    return nullptr;
}

nodeinfantry* UnitList::findEqual(InfantryType infantryType){
    node* current=list.head;
    while(current!=nullptr){
        if(dynamic_cast<Infantry*>(current->unit)->getInfantryType()==infantryType){
            return dynamic_cast<nodeinfantry*>(current);
        };
        current=current->next;
    }
    return nullptr;
}

bool UnitList::isContain(VehicleType vehicleType)
{
    // TODO: Implement
    node* current=list.head;
    if(current==nullptr) return false;
    while(current!=nullptr&&!(dynamic_cast<Vehicle*>(current->unit))){
        current=current->next;
    }
    if(current==nullptr||!(dynamic_cast<Vehicle*>(current->unit))) return false;
    while(current!=nullptr){
        Vehicle* temp=dynamic_cast<Vehicle*>(current->unit);
        if(temp->getVehicleType()==vehicleType){
            return true;
        };
        current=current->next;
    }
    return false;
}

bool UnitList::isContain(InfantryType infantryType)
{
    // TODO: Implement
    node* current=list.head;
    if(current==nullptr) return false;
    while(current!=nullptr&&!(dynamic_cast<Infantry*>(current->unit))){
        current=current->next;
    }
    while(current!=nullptr&&!(current->unit->isVehi())){
        Infantry* temp=dynamic_cast<Infantry*>(current->unit);
        if(temp->getInfantryType()==infantryType){
            return true;
        };
        current=current->next;
    }
    return false;
}

string UnitList::str() const
{
    // TODO: Implement
    string s="UnitList[count_vehicle="+to_string(countVehicle)+";count_infantry="+to_string(countInfantry);
    node* current=list.head;
    if(current!=nullptr) s+=";";
    while(current!=nullptr){
        s+=current->unit->str();
        if(current->next!=nullptr) s+=",";
        current=current->next;
    }
    s+="]";
    return s;
}

void UnitList::insertIndex(Llist list){
    node* current=list.head;
    if(current==nullptr) return;
    int index=1;
    current->index=index++;
    current=current->next;
    while(current!=nullptr){
        current->index=index++;
        current=current->next;
    }
}

void UnitList::removeKnapsack(Llist& original,Llist knapsack) {
    // TODO: Implement
    node* firstpointer=original.head;
    node* secondpointer=knapsack.head;
    if(firstpointer==nullptr||secondpointer==nullptr) return;
    while(secondpointer!=nullptr){
        if(secondpointer->vehi){
            if(original.head->vehi&&dynamic_cast<Vehicle*>(original.head->unit)->getVehicleType()==dynamic_cast<Vehicle*>(secondpointer->unit)->getVehicleType()){
                node* needdelete=original.head;
                original.head=original.head->next;
                firstpointer=original.head;
                delete needdelete;
                secondpointer=secondpointer->next;
                --countVehicle;
                continue;
            }
            else{
                for(firstpointer;firstpointer && firstpointer->next&&!dynamic_cast<Vehicle*>(firstpointer->next->unit);firstpointer=firstpointer->next);
                for(firstpointer;firstpointer && firstpointer->next&&dynamic_cast<Vehicle*>(firstpointer->next->unit)->getVehicleType()!=dynamic_cast<Vehicle*>(secondpointer->unit)->getVehicleType();firstpointer=firstpointer->next);
                node* needdelete=firstpointer->next;
                firstpointer->next=firstpointer->next->next;
                delete needdelete;
                secondpointer=secondpointer->next;
                firstpointer=original.head;
                --countVehicle;
            }
        }
       else{
            if(dynamic_cast<Infantry*>(original.head->unit)->getInfantryType()==dynamic_cast<Infantry*>(secondpointer->unit)->getInfantryType()){
                node* needdelete=original.head;
                original.head=original.head->next;
                firstpointer=original.head;
                delete needdelete;
                secondpointer=secondpointer->next;
                --countInfantry;
                continue;
            }
            else{
                for(firstpointer;firstpointer && firstpointer->next&&dynamic_cast<Infantry*>(firstpointer->next->unit)->getInfantryType()!=dynamic_cast<Infantry*>(secondpointer->unit)->getInfantryType();firstpointer=firstpointer->next);
                node* needdelete=firstpointer->next;
                firstpointer->next=firstpointer->next->next;
                delete needdelete;
                secondpointer=secondpointer->next;
                firstpointer=original.head;
                --countInfantry;
            }
        }
    }
}

void UnitList::removeNode(Llist &list,node* sample){
    node* current=list.head;
    if(current==nullptr) return;
    while(current!=nullptr){
        if(sample->vehi){
            if(list.head->vehi&&dynamic_cast<Vehicle*>(list.head->unit)->getVehicleType()==dynamic_cast<Vehicle*>(sample->unit)->getVehicleType()){
                node* needdelete=list.head;
                list.head=list.head->next;
                current=list.head;
                delete needdelete;
                --countVehicle;
                return;
            }
            else{
                for(current;current->next!=nullptr&&!(current->next->vehi);current=current->next);
                if(current->next==nullptr) return;
                for(current;dynamic_cast<Vehicle*>(current->next->unit)->getVehicleType()!=dynamic_cast<Vehicle*>(sample->unit)->getVehicleType();current=current->next);
                node* needdelete=current->next;
                current->next=current->next->next;
                delete needdelete;
                --countVehicle;
                return;
            }
        }
        else{
            if(!(list.head->vehi)&&dynamic_cast<Infantry*>(list.head->unit)->getInfantryType()==dynamic_cast<Infantry*>(sample->unit)->getInfantryType()){
                node* needdelete=list.head;
                list.head=list.head->next;
                current=list.head;
                delete needdelete;
                --countInfantry;
                return;
            }
            else{
                if(!(current->next->vehi)){
                    for(current;current->next!=nullptr&&!(current->next->unit->isVehi())&&dynamic_cast<Infantry*>(current->next->unit)->getInfantryType()!=dynamic_cast<Infantry*>(sample->unit)->getInfantryType();current=current->next);
                    if(current->next==nullptr&&(current->next->unit->isVehi())) return;
                    node* needdelete=current->next;
                    current->next=current->next->next;
                    delete needdelete;
                    --countInfantry;
                    return;
                }
            }
        }
    }
}

void UnitList::clearLlist(Llist& llist) {
    node* current = llist.head;
    while (current != nullptr) {
        node* temp = current;
        current = current->next;
        delete temp;
    }
    llist.head = nullptr;
}
//!----------------------------------------------
//! Lớp Army
//!----------------------------------------------

int Army::support(int x, int i, int k) {
    if(x == 0)
        return true;
    if(pow(i, k) > x)
        return false;
    return support(x - pow(i, k), i, k + 1) + support(x, i, k + 1);
}

bool Army::specialNumber(int S) {
    if(S <= 2 && S != 1)
        return false;
    else if(S == 3 || S == 1)
        return true;
    if(support(S, 3, 0))
        return true;
    if(support(S, 5, 0))
        return true;
    if(support(S, 7, 0))
        return true;
    return false;
}
Army::Army(Unit **unitArray, int size, string name, BattleField *battleField) : name(name), battleField(battleField) {
    // TODO: Implement
    this->LF = 0;
    this->EXP = 0;
    this->name = name;
    for(int i = 0; i < size; i++) {
        if(unitArray[i]->isVehi()) {
            this->LF += unitArray[i]->getAttackScore();
        } else {
            this->EXP += unitArray[i]->getAttackScore();
        }
    }
    LF = max(0, min(LF, 1000));
    EXP = max(0, min(EXP, 500));
    int capacity=8;
    if(specialNumber(LF+EXP)){
        capacity = 12;
    }
    this->unitList = new UnitList(capacity);
    for(int i = 0; i < size; ++i) {
        unitList->insert(unitArray[i]);
    }
}

Army::~Army() {
    delete unitList;
    unitList = nullptr;
}

// void Army::fight(Army* enemy, bool defense) {
// }

string Army::str() const {
    return "Army[name=" + name + ",LF=" + to_string(LF) + ",EXP=" + to_string(EXP) + "]";
}
//!----------------------------------------------
//! CLASS LiberationArmy
//!----------------------------------------------
// LiberationArmy::~LiberationArmy(){
//     delete unitList;
//     delete battleField;
// }
LiberationArmy::LiberationArmy(Unit **unitArray, int size, string name, BattleField *battleField)
                                                : Army(unitArray,size,name, battleField) {
    // TODO: Implement
    // size_V=unitList->getCountVehicle();
    // size_I=unitList->getCountInfantry();
    liberfight=false;
    liberwin=false;
    justice=true;
    unitList->insertIndex(unitList->getLlist());
}

void LiberationArmy::fight(Army *enemy, bool defense){
    // TODO: Implement
    liberfight=true;
    if(!defense){ //use getNewAttackScore(1.5);
        int NewLF=safeCeil(LF*(float)1.5);
        int NewEXP=safeCeil(EXP*(float)1.5);
        NewLF = max(0,min(NewLF, 1000));
        NewEXP = max(0,min(NewEXP, 500));
        this->LF=NewLF;
        this->EXP=NewEXP;
        Llist knapsackA,knapsackB;
        knapsackA.head=nullptr;
        knapsackB.head=nullptr;
        bool hasKnapsackA=knapsackinfantry(unitList->getLlist(),enemy->getEXP(),knapsackA,1);
        bool hasKnapsackB=knapsackvehicle(unitList->getLlist(),enemy->getLF(),knapsackB,1);
        if(hasKnapsackA && hasKnapsackB){
            liberwin=true;
            unitList->removeKnapsack(unitList->getLlistRef(),knapsackA);
            unitList->removeKnapsack(unitList->getLlistRef(),knapsackB);
            unitList->insertLlistBackward(unitList,enemy->getUnitList());
            node* currentUpdateStrengthenemy=enemy->getUnitList()->getLlist().head;
            enemy->setLF(0);
            enemy->setEXP(0);
            while(currentUpdateStrengthenemy!=nullptr){
                if(currentUpdateStrengthenemy->unit->isVehi()){
                    enemy->setLF(enemy->getLF()+currentUpdateStrengthenemy->unit->getnewAttackScore(1));
                    currentUpdateStrengthenemy=currentUpdateStrengthenemy->next;
                }
                else{
                    enemy->setEXP(enemy->getEXP()+currentUpdateStrengthenemy->unit->getnewAttackScore(1));
                    currentUpdateStrengthenemy=currentUpdateStrengthenemy->next;
                }
            }
            enemy->setLF(max(0,min(enemy->getLF(), 1000)));
            enemy->setEXP(max(0,min(enemy->getEXP(), 500)));
            node* currentUpdateStrength=unitList->getLlist().head;
            this->LF=0;
            this->EXP=0;
            while(currentUpdateStrength!=nullptr){
                if(currentUpdateStrength->unit->isVehi()){
                    currentUpdateStrength->unit->setAttackScorestatic(currentUpdateStrength->unit->getAttackScore());
                    this->LF+=currentUpdateStrength->unit->getAttackScorestatic();
                    currentUpdateStrength=currentUpdateStrength->next;
                }
                else{
                    currentUpdateStrength->unit->setAttackScorestatic(currentUpdateStrength->unit->getAttackScore());
                    this->EXP+=currentUpdateStrength->unit->getAttackScorestatic();
                    currentUpdateStrength=currentUpdateStrength->next;
                }
            }
            this->LF = max(0,min(this->LF, 1000));
            this->EXP = max(0,min(this->EXP, 500));
            unitList->clearLlist(knapsackA);
            unitList->clearLlist(knapsackB);
            return;
        }
        else if(hasKnapsackA && !hasKnapsackB && NewLF>enemy->getLF()){
            liberwin=true;
            unitList->removeKnapsack(unitList->getLlistRef(),knapsackA);
            node* currentremove=unitList->getLlist().head;
            for(currentremove;currentremove!=nullptr&&!(currentremove->vehi);currentremove=currentremove->next);      
            while(currentremove!=nullptr&&currentremove->vehi){
                node* temp=currentremove;
                currentremove=currentremove->next;
                unitList->removeNode(unitList->getLlistRef(),temp);
            }
            unitList->insertLlistBackward(unitList,enemy->getUnitList());
            node* currentUpdateStrengthenemy=enemy->getUnitList()->getLlist().head;
            enemy->setLF(0);
            enemy->setEXP(0);
            while(currentUpdateStrengthenemy!=nullptr){
                if(currentUpdateStrengthenemy->unit->isVehi()){
                    enemy->setLF(enemy->getLF()+currentUpdateStrengthenemy->unit->getnewAttackScore(1));
                    currentUpdateStrengthenemy=currentUpdateStrengthenemy->next;
                }
                else{
                    enemy->setEXP(enemy->getEXP()+currentUpdateStrengthenemy->unit->getnewAttackScore(1));
                    currentUpdateStrengthenemy=currentUpdateStrengthenemy->next;
                }
            }
            enemy->setLF(max(0,min(enemy->getLF(), 1000)));
            enemy->setEXP(max(0,min(enemy->getEXP(), 500)));
            node* currentUpdateStrength=unitList->getLlist().head;
            this->LF=0;
            this->EXP=0;
            while(currentUpdateStrength!=nullptr){
                if(currentUpdateStrength->unit->isVehi()){
                    currentUpdateStrength->unit->setAttackScorestatic(currentUpdateStrength->unit->getAttackScore());
                    this->LF+=currentUpdateStrength->unit->getAttackScorestatic();
                    currentUpdateStrength=currentUpdateStrength->next;
                }
                else{
                    currentUpdateStrength->unit->setAttackScorestatic(currentUpdateStrength->unit->getAttackScore());
                    this->EXP+=currentUpdateStrength->unit->getAttackScorestatic();
                    currentUpdateStrength=currentUpdateStrength->next;
                }
            }
            this->LF = max(0,min(this->LF, 1000));
            this->EXP = max(0,min(this->EXP, 500));
            unitList->clearLlist(knapsackA);
            unitList->clearLlist(knapsackB);
            return;
        }
        else if(!hasKnapsackA && hasKnapsackB && NewEXP>enemy->getEXP()){
            liberwin=true;
            unitList->removeKnapsack(unitList->getLlistRef(),knapsackB);
            node* currentremove=unitList->getLlist().head;
            while(currentremove!=nullptr&&!(currentremove->vehi)){
                node* temp=currentremove;
                currentremove=currentremove->next;
                unitList->removeNode(unitList->getLlistRef(),temp);
            }
            unitList->insertLlistBackward(unitList,enemy->getUnitList());
            node* currentUpdateStrengthenemy=enemy->getUnitList()->getLlist().head;
            enemy->setLF(0);
            enemy->setEXP(0);
            while(currentUpdateStrengthenemy!=nullptr){
                if(currentUpdateStrengthenemy->unit->isVehi()){
                    enemy->setLF(enemy->getLF()+currentUpdateStrengthenemy->unit->getnewAttackScore(1));
                    currentUpdateStrengthenemy=currentUpdateStrengthenemy->next;
                }
                else{
                    enemy->setEXP(enemy->getEXP()+currentUpdateStrengthenemy->unit->getnewAttackScore(1));
                    currentUpdateStrengthenemy=currentUpdateStrengthenemy->next;
                }
            }
            enemy->setLF(max(0,min(enemy->getLF(), 1000)));
            enemy->setEXP(max(0,min(enemy->getEXP(), 500)));
            node* currentUpdateStrength=unitList->getLlist().head;
            this->LF=0;
            this->EXP=0;
            while(currentUpdateStrength!=nullptr){
                if(currentUpdateStrength->unit->isVehi()){
                    currentUpdateStrength->unit->setAttackScorestatic(currentUpdateStrength->unit->getAttackScore());
                    this->LF+=currentUpdateStrength->unit->getAttackScorestatic();
                    currentUpdateStrength=currentUpdateStrength->next;
                }
                else{
                    currentUpdateStrength->unit->setAttackScorestatic(currentUpdateStrength->unit->getAttackScore());
                    this->EXP+=currentUpdateStrength->unit->getAttackScorestatic();
                    currentUpdateStrength=currentUpdateStrength->next;
                }
            }
            this->LF = max(0,min(this->LF, 1000));
            this->EXP = max(0,min(this->EXP, 500));
            unitList->clearLlist(knapsackA);
            unitList->clearLlist(knapsackB);
            return;
        }
        else{
            node* currentUpdateStrength=unitList->getLlist().head;
            this->LF=0;
            this->EXP=0;
            while(currentUpdateStrength!=nullptr){
                currentUpdateStrength->unit->setWeight(safeCeil(currentUpdateStrength->unit->getWeight()*0.9f));
                if(currentUpdateStrength->unit->isVehi()){
                    currentUpdateStrength->unit->setAttackScorestatic(currentUpdateStrength->unit->getAttackScore());
                    this->LF+=currentUpdateStrength->unit->getAttackScorestatic();
                    currentUpdateStrength=currentUpdateStrength->next;
                }
                else{
                    currentUpdateStrength->unit->setAttackScorestatic(currentUpdateStrength->unit->getAttackScore());
                    this->EXP+=currentUpdateStrength->unit->getAttackScorestatic();
                    currentUpdateStrength=currentUpdateStrength->next;
                }
            }
            this->LF = max(0,min(this->LF, 1000));
            this->EXP = max(0,min(this->EXP, 500));
            unitList->clearLlist(knapsackA);
            unitList->clearLlist(knapsackB);
            return;
        }
    }
    else{
        int NewLF=safeCeil(LF*(float)1.3);
        int NewEXP=safeCeil(EXP*(float)1.3);
        NewLF = max(0,min(NewLF, 1000));
        NewEXP = max(0,min(NewEXP, 500));
        this->LF=NewLF;
        this->EXP=NewEXP;
        if(NewLF>=enemy->getLF() && NewEXP>=enemy->getEXP()){
            return;
        }
        else if(NewLF>=enemy->getLF() && NewEXP<enemy->getEXP()||NewLF<enemy->getLF() && NewEXP>=enemy->getEXP()){
            node* currentUpdateStrength=unitList->getLlist().head;
            this->LF=0;
            this->EXP=0;
            while(currentUpdateStrength!=nullptr){
                currentUpdateStrength->unit->setQuantity(safeCeil(currentUpdateStrength->unit->getQuantity()*(float)0.9));
                if(currentUpdateStrength->unit->isVehi()){
                    currentUpdateStrength->unit->setAttackScorestatic(currentUpdateStrength->unit->getAttackScore());
                    this->LF+=currentUpdateStrength->unit->getAttackScorestatic();
                    currentUpdateStrength=currentUpdateStrength->next;
                }
                else{
                    currentUpdateStrength->unit->setAttackScorestatic(currentUpdateStrength->unit->getAttackScore());
                    this->EXP+=currentUpdateStrength->unit->getAttackScorestatic();
                    currentUpdateStrength=currentUpdateStrength->next;
                }
            }
            this->LF = max(0,min(this->LF, 1000));
            this->EXP = max(0,min(this->EXP, 500));
        }
        else{
            while(!(NewLF>=enemy->getLF() && NewEXP>=enemy->getEXP())&&!(NewLF>=enemy->getLF() && NewEXP<enemy->getEXP()||NewLF<enemy->getLF() && NewEXP>=enemy->getEXP())){
                node* current= unitList->getLlist().head;
                while(current!=nullptr){
                    current->unit->setQuantity(nearestFibonacci(current->unit->getQuantity()));
                    current=current->next;
                }
                node* currentUpdateStrength=unitList->getLlist().head;
                this->LF=0;
                this->EXP=0;
                while(currentUpdateStrength!=nullptr){
                    if(currentUpdateStrength->unit->isVehi()){
                        currentUpdateStrength->unit->setAttackScorestatic(currentUpdateStrength->unit->getAttackScore());
                        this->LF+=currentUpdateStrength->unit->getAttackScorestatic();
                        currentUpdateStrength=currentUpdateStrength->next;
                    }
                    else{
                        currentUpdateStrength->unit->setAttackScorestatic(currentUpdateStrength->unit->getAttackScore());
                        this->EXP+=currentUpdateStrength->unit->getAttackScorestatic();
                        currentUpdateStrength=currentUpdateStrength->next;
                    }
                }
                this->LF = max(0,min(this->LF, 1000));
                this->EXP = max(0,min(this->EXP, 500));
                // NewLF=safeCeil(LF*(float)1.3);
                // NewEXP=safeCeil(EXP*(float)1.3);
                // NewLF = max(0,min(NewLF, 1000));
                // NewEXP = max(0,min(NewEXP, 500));
                // this->LF=NewLF;
                // this->EXP=NewEXP;
                NewLF=this->LF;
                NewEXP=this->EXP;
                if(NewLF>=enemy->getLF() && NewEXP>=enemy->getEXP()){
                    return;
                }
                else if(NewLF>=enemy->getLF() && NewEXP<enemy->getEXP()||NewLF<enemy->getLF() && NewEXP>=enemy->getEXP()){
                    node* currentUpdateStrength=unitList->getLlist().head;
                    this->LF=0;
                    this->EXP=0;
                    while(currentUpdateStrength!=nullptr){
                        currentUpdateStrength->unit->setQuantity(safeCeil(currentUpdateStrength->unit->getQuantity()*0.9f));
                        if(currentUpdateStrength->unit->isVehi()){
                            currentUpdateStrength->unit->setAttackScorestatic(currentUpdateStrength->unit->getAttackScore());
                            this->LF+=currentUpdateStrength->unit->getAttackScorestatic();
                            currentUpdateStrength=currentUpdateStrength->next;
                        }
                        else{
                            currentUpdateStrength->unit->setAttackScorestatic(currentUpdateStrength->unit->getAttackScore());
                            this->EXP+=currentUpdateStrength->unit->getAttackScorestatic();
                            currentUpdateStrength=currentUpdateStrength->next;
                        }
                    }
                    this->LF = max(0,min(this->LF, 1000));
                    this->EXP = max(0,min(this->EXP, 500));
                    return;
                }
            }
        }
    }
}

string LiberationArmy::str() const {
    // TODO: Implement
    string s="LiberationArmy[LF="+to_string(this->LF)+","+"EXP="+to_string(this->EXP)+",unitList=";
    s+=unitList->str();
    // s+="]";
    s+=",battleField=";
    stringstream ss;
    ss<<s;
    if(battleField!=nullptr){
        ss<<battleField->str();
    }
    ss<<"]";
    return ss.str().c_str();
}


int LiberationArmy::nearestFibonacci(int value) {
    // TODO: Implement
    int firstnum=0;
    int secondnum=1;
    int sum=firstnum+secondnum;
    while(sum<=value){
        firstnum=secondnum;
        secondnum=sum;
        sum=firstnum+secondnum;
    }
    return sum;
}



// bool LiberationArmy::cloneList(Llist oldlist,Llist& newlist){
//     newlist.head=nullptr;
//     node* current = oldlist.head;
//     while (current!=nullptr){
//         if(current->unit->isVehi()){
//             nodevehicle* newnode=clonenode(dynamic_cast<nodevehicle*>(current));
//             if(newlist.head==nullptr){
//                 newlist.head=newnode;
//                 newnode=nullptr;
//             }
//             else { 
//                 node* current2=newlist.head;
//                 while(current2->next!=nullptr){
//                     current2=current2->next;
//                 }
//                 current2->next=newnode;
//                 newnode=nullptr;
//             }
//         }
//         else {
//             nodeinfantry* newnode=clonenode(dynamic_cast<nodeinfantry*>(current));
//             if(newlist.head==nullptr){
//                 newlist.head=newnode;
//                 newnode=nullptr;
//             }
//             else { 
//                 node* current2=newlist.head;
//                 while(current2->next!=nullptr){
//                     current2=current2->next;
//                 }
//                 current2->next=newnode;
//                 newnode=nullptr;
//             }
//         }
//         current=current->next;
//     }
//     if(newlist.head==nullptr) return false;
//     return true;
// }

bool LiberationArmy::knapsackinfantry(Llist list, int minScore,Llist& newlist, double coefficient) {
    // TODO: Implement
    node*current=list.head;
    if(current==nullptr) return false;
    int attackScore=0;
    int minvalue=1410065408;
    int n=unitList->getCountInfantry();
    for(int k=1;k<=n;++k){
        vector<int> sample;
        sample.push_back(0);
        for(int i=1;i<=k;++i){
            sample.push_back(i);
        }
        while(1){
            for(int i=1;i<=k;++i){
                for(current;current!=nullptr&&current->index!=sample.at(i);current=current->next);
                if(current==nullptr){
                    if(minvalue==1410065408) return false;
                    else return true;
                } 
                attackScore+=dynamic_cast<Infantry*>(current->unit)->getAttackScorestatic();
            }
            current=list.head;
            if(attackScore>minScore&&attackScore<minvalue){
                minvalue=attackScore;
                node* currentclear = newlist.head;
                while (currentclear != nullptr) {
                    node* temp = currentclear;
                    currentclear = currentclear->next;
                    delete temp;
                }
                newlist.head=nullptr;
                for(int i=1;i<=k;++i){
                    for(current;current!=nullptr&&current->index!=sample.at(i);current=current->next);
                    nodeinfantry* clone=clonenode(dynamic_cast<nodeinfantry*>(current));
                    if(newlist.head==nullptr) {
                        newlist.head=clone;
                        clone=nullptr;
                    }
                    else { 
                        node* current2=newlist.head;
                        while(current2->next!=nullptr){
                            current2=current2->next;
                        }
                        current2->next=clone;
                        clone=nullptr;
                    }
                }
            }
            int i=k;
            while(sample.at(i)==n-k+i&&i>0) --i;
            if(i==0) break;
            else{
                ++sample.at(i);
                for(int j=i+1;j<=k;++j) sample.at(j)=sample.at(i)+j-i;
            }
            attackScore=0;
            current=list.head;
        }
        attackScore=0;
        current=list.head;
    }
    if(minvalue==1410065408) return false;
    else return true;
}

bool LiberationArmy::knapsackvehicle(Llist list, int minScore,Llist& newlist,double coefficient) {
    // TODO: Implement
    node*current=list.head;
    if(current==nullptr) return false;
    int attackScore=0;
    int minvalue=1410065408;
    int n=unitList->getCountVehicle();
    for(int k=1;k<=n;++k){
        vector<int> sample;
        sample.push_back(0);
        for(int i=unitList->getCountInfantry()+1;i<=unitList->getCountInfantry()+k;++i){
            sample.push_back(i-unitList->getCountInfantry());
        }
        while(1){
            for(int i=1;i<=k;++i){
                for(current;current!=nullptr&&current->index!=(sample.at(i)+unitList->getCountInfantry());current=current->next);
                if(current==nullptr){
                    if(minvalue==1410065408) return false;
                    else return true;
                }
                attackScore+=dynamic_cast<Vehicle*>(current->unit)->getAttackScorestatic();
            }
            current=list.head;
            if(attackScore>minScore&&attackScore<minvalue){
                minvalue=attackScore;
                node* currentclear = newlist.head;
                while (currentclear != nullptr) {
                    node* temp = currentclear;
                    currentclear = currentclear->next;
                    delete temp;
                }
                newlist.head=nullptr;
                for(int j=1;j<=k;++j){
                    for(current;current!=nullptr&&current->index!=sample.at(j)+unitList->getCountInfantry();current=current->next);
                    if(newlist.head==nullptr) {
                        nodevehicle* clone=clonenode(dynamic_cast<nodevehicle*>(current));
                        newlist.head=clone;
                        clone=nullptr;
                    }
                    else { 
                        nodevehicle* clone=clonenode(dynamic_cast<nodevehicle*>(current));
                        node* current2=newlist.head;
                        while(current2->next!=nullptr){
                            current2=current2->next;
                        }
                        current2->next=clone;
                        clone=nullptr;
                    }
                }
            }
            int i=k;
            while(sample.at(i)==n-k+i&&i>0) --i;
            if(i==0) break;
            else{
                ++sample.at(i);
                for(int j=i+1;j<=k;++j) sample.at(j)=sample.at(i)+j-i;
            }
            attackScore=0;
            current=list.head;
        }
        attackScore=0;
        current=list.head;
    }
    if(minvalue==1410065408) return false;
    else return true;
}

nodeinfantry* LiberationArmy::clonenode(nodeinfantry* original) {
    // TODO: Implement
    if(original==nullptr) return nullptr;
    nodeinfantry* nodeclone= new nodeinfantry(original);
    return nodeclone;
}

nodevehicle* LiberationArmy::clonenode(nodevehicle* original){
    if(original==nullptr) return nullptr;
    nodevehicle* nodeclone= new nodevehicle(original);
    return nodeclone;
};
//!----------------------------------------------
//! CLASS ARVN
//!----------------------------------------------
// ARVN::~ARVN(){
//     delete unitList;
//     delete battleField;
    // for(int i=0;i<size;++i){
    //     delete unitArray[i];
    // }
    // delete [] unitArray;
// }
ARVN::ARVN(Unit** unitArray, int size, string name, BattleField *battleField) 
        : Army(unitArray, size, name, battleField) {
                justice=false;
}

void ARVN::fight(Army* enemy, bool defense) {
    // TODO: Implement
    
    if(!defense){
        // int NewLF=safeCeil(enemy->getLF()*(float)1.3);
        // int NewEXP=safeCeil(enemy->getEXP()*(float)1.3);
        // NewLF = max(0,min(NewLF, 1000));
        // NewEXP = max(0,min(NewEXP, 500));
        node* currentUpdateStrength=unitList->getLlist().head;
        this->LF=0;
        this->EXP=0;
        while(currentUpdateStrength!=nullptr){
            currentUpdateStrength->unit->setQuantity(safeCeil(currentUpdateStrength->unit->getQuantity()*0.8f));
            if(currentUpdateStrength->unit->getQuantity()<=1){
                node* temp=currentUpdateStrength;
                currentUpdateStrength=currentUpdateStrength->next;
                unitList->removeNode(unitList->getLlistRef(),temp);
                temp=nullptr;
            }
            else{
                if(currentUpdateStrength->unit->isVehi()){
                    currentUpdateStrength->unit->setAttackScorestatic(currentUpdateStrength->unit->getAttackScore());
                    this->LF+=currentUpdateStrength->unit->getAttackScorestatic();
                    currentUpdateStrength=currentUpdateStrength->next;
                }
                else{
                    currentUpdateStrength->unit->setAttackScorestatic(currentUpdateStrength->unit->getAttackScore());
                    this->EXP+=currentUpdateStrength->unit->getAttackScorestatic();
                    currentUpdateStrength=currentUpdateStrength->next;
                }
            }
            
        }
        this->LF = max(0,min(this->LF, 1000));
        this->EXP = max(0,min(this->EXP, 500));
    }
    else{
        if(enemy->getLiberFight()==false) return;
        // int NewLF=safeCeil(enemy->getLF()*(float)1.5);
        // int NewEXP=safeCeil(enemy->getEXP()*(float)1.5);
        // NewLF = max(0,min(NewLF, 1000));
        // NewEXP = max(0,min(NewEXP, 500));
        // Llist knapsackA,knapsackB;
        // knapsackA.head=nullptr;
        // knapsackB.head=nullptr;
        // bool hasKnapsackA=enemy->knapsackinfantry(enemy->getUnitList()->getLlistRef(),EXP,knapsackA,1);
        // bool hasKnapsackB=enemy->knapsackvehicle(enemy->getUnitList()->getLlistRef(),LF,knapsackB,1);
        // if(hasKnapsackA && hasKnapsackB){
            // enemy->getUnitList()->removeKnapsack(unitList->getLlistRef(),knapsackA);
            // enemy->getUnitList()->removeKnapsack(unitList->getLlistRef(),knapsackB);
            // enemy->getUnitList()->insertLlistBackward(enemy->getUnitList(),unitList);
            // node* currentUpdateStrength=unitList->getLlist().head;
            // this->LF=0;
            // this->EXP=0;
            // while(currentUpdateStrength!=nullptr){
            //     currentUpdateStrength->unit->setWeight(ceil(currentUpdateStrength->unit->getWeight()*(float)0.8));
            //     this->EXP+=currentUpdateStrength->unit->getAttackScore();
            //     currentUpdateStrength=currentUpdateStrength->next;
            // }
            // this->EXP = max(0,min(this->EXP, 500));
            if(enemy->getLiberWin()){
                node* currentUpdateStrengthARVN=unitList->getLlist().head;
                setLF(0);
                setEXP(0);
                while(currentUpdateStrengthARVN!=nullptr){
                    currentUpdateStrengthARVN->unit->setWeight(safeCeil(currentUpdateStrengthARVN->unit->getWeight()*(float)0.8));
                // if(currentUpdateStrengthARVN->unit->getQuantity()<=1){
                //     node* temp=currentUpdateStrengthARVN;
                //     currentUpdateStrengthARVN=currentUpdateStrengthARVN->next;
                //     temp=nullptr;
                //     unitList->removeNode(unitList->getLlistRef(),temp);
                // }
                // else{
                if(currentUpdateStrengthARVN->unit->isVehi()){
                    currentUpdateStrengthARVN->unit->setAttackScorestatic(currentUpdateStrengthARVN->unit->getAttackScore());
                    this->LF+=currentUpdateStrengthARVN->unit->getAttackScorestatic();
                    currentUpdateStrengthARVN=currentUpdateStrengthARVN->next;
                }
                else{
                    currentUpdateStrengthARVN->unit->setAttackScorestatic(currentUpdateStrengthARVN->unit->getAttackScore());
                    this->EXP+=currentUpdateStrengthARVN->unit->getAttackScorestatic();
                    currentUpdateStrengthARVN=currentUpdateStrengthARVN->next;
                }
                // }
                }
                setLF(max(0,min(getLF(), 1000)));
                setEXP(max(0,min(getEXP(), 500)));
            }
            // else{
                // node* currentUpdateStrengthARVN=unitList->getLlist().head;
                // setLF(0);
                // setEXP(0);
                // while(currentUpdateStrengthARVN!=nullptr){
                // currentUpdateStrengthARVN->unit->setWeight(safeCeil(currentUpdateStrengthARVN->unit->getWeight()*(float)0.8));
                // if(currentUpdateStrengthARVN->unit->getQuantity()<=1){
                //     node* temp=currentUpdateStrengthARVN;
                //     currentUpdateStrengthARVN=currentUpdateStrengthARVN->next;
                //     temp=nullptr;
                //     unitList->removeNode(unitList->getLlistRef(),temp);
                // }
                // else{
            //         if(currentUpdateStrengthARVN->unit->isVehi()){
            //             setLF(getLF()+currentUpdateStrengthARVN->unit->getAttackScore());
            //             currentUpdateStrengthARVN=currentUpdateStrengthARVN->next;
            //         }
            //         else{
            //             setEXP(getEXP()+currentUpdateStrengthARVN->unit->getAttackScore());
            //             currentUpdateStrengthARVN=currentUpdateStrengthARVN->next;
            //         }
            //     // }
            //     }
            //     setLF(max(0,min(getLF(), 1000)));
            //     setEXP(max(0,min(getEXP(), 500)));
            // }
            // node* currentUpdateStrengthenemy=enemy->getUnitList()->getLlist().head;
            // enemy->setLF(0);
            // enemy->setEXP(0);
            // while(currentUpdateStrengthenemy!=nullptr){
            //     if(currentUpdateStrengthenemy->unit->isVehi()){
            //         enemy->setLF(enemy->getLF()+currentUpdateStrengthenemy->unit->getAttackScore());
            //         currentUpdateStrengthenemy=currentUpdateStrengthenemy->next;
            //     }
            //     else{
            //         enemy->setEXP(enemy->getEXP()+currentUpdateStrengthenemy->unit->getAttackScore());
            //         currentUpdateStrengthenemy=currentUpdateStrengthenemy->next;
            //     }
            // }
            // enemy->setLF(max(0,min(enemy->getLF(), 1000)));
            // enemy->setEXP(max(0,min(enemy->getEXP(), 500)));
        //     unitList->clearLlist(knapsackA);
        //     unitList->clearLlist(knapsackB);
        //     return;
        // }

        // else if(hasKnapsackA && !hasKnapsackB && NewLF>LF){
        //    enemy->getUnitList()->insertLlistBackward(enemy->getUnitList(),unitList);
            // node* currentUpdateStrength=unitList->getLlist().head;
            // this->LF=0;
            // this->EXP=0;
            // while(currentUpdateStrength!=nullptr){
            //     currentUpdateStrength->unit->setWeight(ceil(currentUpdateStrength->unit->getWeight()*(float)0.8));
            //     this->EXP+=currentUpdateStrength->unit->getAttackScore();
            //     currentUpdateStrength=currentUpdateStrength->next;
            // }
            // this->EXP = max(0,min(this->EXP, 500));
            // node* currentUpdateStrengthARVN=unitList->getLlist().head;
            // setLF(0);
            // setEXP(0);
            // while(currentUpdateStrengthARVN!=nullptr){
            //     currentUpdateStrengthARVN->unit->setWeight(safeCeil(currentUpdateStrengthARVN->unit->getWeight()*(float)0.8));
                // if(currentUpdateStrengthARVN->unit->getQuantity()<=1){
                //     node* temp=currentUpdateStrengthARVN;
                //     currentUpdateStrengthARVN=currentUpdateStrengthARVN->next;
                //     temp=nullptr;
                //     unitList->removeNode(unitList->getLlistRef(),temp);
                // }
                // else{
                    // if(currentUpdateStrengthARVN->unit->isVehi()){
                    //     setLF(getLF()+currentUpdateStrengthARVN->unit->getAttackScore());
                    //     currentUpdateStrengthARVN=currentUpdateStrengthARVN->next;
                    // }
                    // else{
                    //     setEXP(getEXP()+currentUpdateStrengthARVN->unit->getAttackScore());
                    //     currentUpdateStrengthARVN=currentUpdateStrengthARVN->next;
                    // }
                // }
        //     }
        //     setLF(max(0,min(getLF(), 1000)));
        //     setEXP(max(0,min(getEXP(), 500)));
        //     unitList->clearLlist(knapsackA);
        //     unitList->clearLlist(knapsackB);
        //     return;
        // }
        // else if(!hasKnapsackA && hasKnapsackB && NewEXP>EXP){
        //     enemy->getUnitList()->insertLlistBackward(enemy->getUnitList(),unitList);
            // node* currentUpdateStrength=unitList->getLlist().head;
            // this->LF=0;
            // this->EXP=0;
            // while(currentUpdateStrength!=nullptr){
            //     currentUpdateStrength->unit->setWeight(ceil(currentUpdateStrength->unit->getWeight()*(float)0.8));
            //     this->EXP+=currentUpdateStrength->unit->getAttackScore();
            //     currentUpdateStrength=currentUpdateStrength->next;
            // }
            // this->EXP = max(0,min(this->EXP, 500));
            // node* currentUpdateStrengthARVN=unitList->getLlist().head;
            // setLF(0);
            // setEXP(0);
            // while(currentUpdateStrengthARVN!=nullptr){
            //     currentUpdateStrengthARVN->unit->setWeight(safeCeil(currentUpdateStrengthARVN->unit->getWeight()*(float)0.8));
                // if(currentUpdateStrengthARVN->unit->getQuantity()<=1){
                //     node* temp=currentUpdateStrengthARVN;
                //     currentUpdateStrengthARVN=currentUpdateStrengthARVN->next;
                //     temp=nullptr;
                //     unitList->removeNode(unitList->getLlistRef(),temp);
                // }
                // else{
            //         if(currentUpdateStrengthARVN->unit->isVehi()){
            //             setLF(getLF()+currentUpdateStrengthARVN->unit->getAttackScore());
            //             currentUpdateStrengthARVN=currentUpdateStrengthARVN->next;
            //         }
            //         else{
            //             setEXP(getEXP()+currentUpdateStrengthARVN->unit->getAttackScore());
            //             currentUpdateStrengthARVN=currentUpdateStrengthARVN->next;
            //         // }
            //     }
            // }
            // setLF(max(0,min(getLF(), 1000)));
            // setEXP(max(0,min(getEXP(), 500)));
            // unitList->clearLlist(knapsackA);
            // unitList->clearLlist(knapsackB);
            // return;
        // }
        // else{
        //     return;
        // }
    }
}

string ARVN::str() const {
    // TODO: Implement
    string s="ARVN[LF="+to_string(this->LF)+","+"EXP="+to_string(this->EXP)+",unitList=";
    s+=unitList->str();
    // s+="]";
    s+=",battleField=";
    stringstream ss;
    ss<<s;
    if(battleField!=nullptr){
        ss<<battleField->str();
    }
    ss<<"]";
    return ss.str().c_str();
}

// void ARVN::updateScores() {
//     // TODO: Implement
// }

bool ARVN::knapsackinfantry(Llist list, int minScore,Llist& newlist, double coefficient) {
    // TODO: Implement
    node*current=list.head;
    if(current==nullptr) return false;
    int attackScore=0;
    int minvalue=1410065408;
    int n=unitList->getCountInfantry();
    for(int k=1;k<=n;++k){
        vector<int> sample;
        for(int i=1;i<=k;++i){
            sample.push_back(i);
        }
        while(1){
            for(int i=1;i<=k;++i){
                for(current;current->index!=sample.at(i);current=current->next);
                attackScore+=current->unit->getAttackScorestatic();
            }
            current=list.head;
            if(attackScore==minScore){
                node* currentclear = newlist.head;
                while (currentclear != nullptr) {
                    node* temp = currentclear;
                    currentclear = currentclear->next;
                    delete temp;
                }
                newlist.head=nullptr;
                for(int i=1;i<=k;++i){
                    for(current;current->index!=sample.at(i);current=current->next);
                    nodeinfantry* clone=clonenode(dynamic_cast<nodeinfantry*>(current));
                    if(newlist.head==nullptr) {
                        newlist.head=clone;
                        clone=nullptr;
                    }
                    else { 
                        node* current2=newlist.head;
                        while(current2->next!=nullptr){
                            current2=current2->next;
                        }
                        current2->next=clone;
                        clone=nullptr;
                    }
                }
                return true;
            } 
            else if(attackScore>minScore&&attackScore<minvalue){
                minvalue=attackScore;
                node* currentclear = newlist.head;
                while (currentclear != nullptr) {
                    node* temp = currentclear;
                    currentclear = currentclear->next;
                    delete temp;
                }
                newlist.head=nullptr;
                for(int i=1;i<=k;++i){
                    for(current;current->index!=sample.at(i);current=current->next);
                    nodeinfantry* clone=clonenode(dynamic_cast<nodeinfantry*>(current));
                    if(newlist.head==nullptr) {
                        newlist.head=clone;
                        clone=nullptr;
                    }
                    else { 
                        node* current2=newlist.head;
                        while(current2->next!=nullptr){
                            current2=current2->next;
                        }
                        current2->next=clone;
                        clone=nullptr;
                    }
                }
            }
            int i=k;
            while(sample.at(i)==n-k+i&&i>0) --i;
            if(i==0) break;
            else{
                ++sample.at(i);
                for(int j=i+1;j<=k;++j) sample.at(j)=sample.at(i)+j-i;
            }
        }
    }
    if(minvalue==1410065408) return false;
    else return true;
}

bool ARVN::knapsackvehicle(Llist list, int minScore,Llist& newlist,double coefficient) {
    // TODO: Implement
    node*current=list.head;
    if(current==nullptr) return false;
    int attackScore=0;
    int minvalue=1410065408;
    int n=unitList->getCountVehicle();
    for(int k=1;k<=n;++k){
        vector<int> sample;
        for(int i=unitList->getCountInfantry()+1;i<=(unitList->getCountInfantry()+unitList->getCountVehicle());++i){
            sample.push_back(i);
        }
        while(1){
            for(int i=1;i<=k;++i){
                for(current;current->index!=sample.at(i);current=current->next);
                attackScore+=current->unit->getAttackScorestatic();
            }
            current=list.head;
            if(attackScore==minScore){
                node* currentclear = newlist.head;
                while (currentclear != nullptr) {
                    node* temp = currentclear;
                    currentclear = currentclear->next;
                    delete temp;
                }
                newlist.head=nullptr;
                for(int i=1;i<=k;++i){
                    for(current;current->index!=sample.at(i);current=current->next);
                    if(newlist.head==nullptr) {
                        nodevehicle* clone=clonenode(dynamic_cast<nodevehicle*>(current));
                        newlist.head=clone;
                        clone=nullptr;
                    }
                    else { 
                        nodevehicle* clone=clonenode(dynamic_cast<nodevehicle*>(current));
                        node* current2=newlist.head;
                        while(current2->next!=nullptr){
                            current2=current2->next;
                        }
                        current2->next=clone;
                        clone=nullptr;
                    }
                }
                return true;
            } 
            else if(attackScore>minScore&&attackScore<minvalue){
                minvalue=attackScore;
                node* currentclear = newlist.head;
                while (currentclear != nullptr) {
                    node* temp = currentclear;
                    currentclear = currentclear->next;
                    delete temp;
                }
                newlist.head=nullptr;
                for(int i=1;i<=k;++i){
                    for(current;current->index!=sample.at(i);current=current->next);
                    if(newlist.head==nullptr) {
                        nodevehicle* clone=clonenode(dynamic_cast<nodevehicle*>(current));
                        newlist.head=clone;
                        clone=nullptr;
                    }
                    else { 
                        nodevehicle* clone=clonenode(dynamic_cast<nodevehicle*>(current));
                        node* current2=newlist.head;
                        while(current2->next!=nullptr){
                            current2=current2->next;
                        }
                        current2->next=clone;
                        clone=nullptr;
                    }
                }
            }
            int i=k;
            while(sample.at(i)==n-k+i&&i>0) --i;
            if(i==0) break;
            else{
                ++sample.at(i);
                for(int j=i+1;j<=k;++j) sample.at(j)=sample.at(i)+j-i;
            }
        }
    }
    if(minvalue==1410065408) return false;
    else return true;
}

nodeinfantry* ARVN::clonenode(nodeinfantry* original) {
    // TODO: Implement
    if(original==nullptr) return nullptr;
    nodeinfantry* nodeclone= new nodeinfantry(original);
    return nodeclone;
}

nodevehicle* ARVN::clonenode(nodevehicle* original){
    if(original==nullptr) return nullptr;
    nodevehicle* nodeclone= new nodevehicle(original);
    return nodeclone;
};
//!-----------------------------------------------------
//! Lớp TerrainElement và các lớp con
//!-----------------------------------------------------
double TerrainElement::calculateDistance(const Position& pos1, const Position& pos2) {
    int rowDiff = pos1.getRow() - pos2.getRow();
    int colDiff = pos1.getCol() - pos2.getCol();
    return (sqrt(double(rowDiff * rowDiff + colDiff * colDiff)));
}
int TerrainElement::safeCeil(double value) {
    double diff = abs(value - round(value));
    return (diff < 1e-5) ? round(value) : ceil(value);
}

TerrainElement::TerrainElement(Position pos) : pos(pos)
{
    this->terrainType = ROAD; 
}

TerrainElement::~TerrainElement() {
}

void Road::getEffect(Army *army) {
}

void Mountain::getEffect(Army *army) {
    if(army==nullptr) return;
    if(army->isJustice()){
        node* current=army->getUnitList()->getLlist().head;
        while(current!=nullptr){
            if(calculateDistance(this->pos,current->unit->getCurrentPosition())<=2){
                if(current->unit->isVehi()){
                    army->setLF(army->getLF()-safeCeil((float)0.1*current->unit->getAttackScorestatic()));
                }
                else army->setEXP(army->getEXP()+safeCeil((float)0.3*current->unit->getAttackScorestatic()));
            }
            current=current->next;
        }
        army->setEXP(max(0,min(army->getEXP(),500)));
        army->setLF(max(0,min(army->getLF(),1000)));
    }
    else {
        node* current=army->getUnitList()->getLlist().head;
        while(current!=nullptr){
            if(calculateDistance(this->pos,current->unit->getCurrentPosition())<=4){
                if(current->unit->isVehi()){
                    army->setLF(army->getLF()-safeCeil((float)0.05*current->unit->getAttackScorestatic()));
                }
                else army->setEXP(army->getEXP()+safeCeil((float)0.2*current->unit->getAttackScorestatic()));
            }
            current=current->next;
        }
        army->setEXP(max(0,min(army->getEXP(),500)));
        army->setLF(max(0,min(army->getLF(),1000)));
    }

}

void River::getEffect(Army *army) {
    if(army==nullptr) return;
    node* current=army->getUnitList()->getLlist().head;
    while(current!=nullptr){
        if(calculateDistance(this->pos,current->unit->getCurrentPosition())<=2){
            if(!(current->unit->isVehi())){
                current->unit->setAttackScorestatic(safeCeil(current->unit->getAttackScorestatic()*(float)0.9));
            }
        }
        current=current->next;
    }
}

void Urban::getEffect(Army *army) {
        if(army==nullptr) return;
        if(army->isJustice()){
            node* current=army->getUnitList()->getLlist().head;
            while(current!=nullptr){
                double distance=calculateDistance(this->pos,current->unit->getCurrentPosition());
                if(distance<=5&&!(current->unit->isVehi())&&(dynamic_cast<Infantry*>(current->unit)->getInfantryType()==SPECIALFORCES||dynamic_cast<Infantry*>(current->unit)->getInfantryType()==REGULARINFANTRY)){
                    if(distance==0){
                        // current->unit->setAttackScorestatic(0);
                        return;
                    }
                    else{
                        current->unit->setAttackScorestatic(current->unit->getAttackScorestatic()+safeCeil(current->unit->getAttackScorestatic()*2/(float)distance));
                    }                
                }
                else if(distance<=2&&current->unit->isVehi()&&dynamic_cast<Vehicle*>(current->unit)->getVehicleType()==ARTILLERY){
                    current->unit->setAttackScorestatic(safeCeil(current->unit->getAttackScorestatic()*(float)0.5));
                }
                current=current->next;
            }
        }
        else {
            node* current=army->getUnitList()->getLlist().head;
            while(current!=nullptr){
                double distance=calculateDistance(this->pos,current->unit->getCurrentPosition());
                if(distance<=3&&!(current->unit->isVehi())&&dynamic_cast<Infantry*>(current->unit)->getInfantryType()==REGULARINFANTRY){
                    if(distance==0){
                        // current->unit->setAttackScorestatic(0);
                        return;
                    }
                    else{
                        current->unit->setAttackScorestatic(current->unit->getAttackScorestatic()+safeCeil((current->unit->getAttackScorestatic()*3)/(2*(float)distance)));                  
                    }
                }  
                current=current->next;
            }
        }
}

void Fortification::getEffect(Army *army) {
        if(army==nullptr) return;
        if(army->isJustice()){
            node* current=army->getUnitList()->getLlist().head;
            while(current!=nullptr){
                if(calculateDistance(this->pos,current->unit->getCurrentPosition())<=2){
                    current->unit->setAttackScorestatic(safeCeil(current->unit->getAttackScorestatic()*(float)0.8));
                }
                current=current->next;
            }
        }
        else{
            node* current=army->getUnitList()->getLlist().head;
            while(current!=nullptr){
                if(calculateDistance(this->pos,current->unit->getCurrentPosition())<=2){
                    current->unit->setAttackScorestatic(safeCeil(current->unit->getAttackScorestatic()*(float)1.2));
                }
                current=current->next;
            }
        }
}

void SpecialZone::getEffect(Army *army) {
        if(army==nullptr) return;
        node* current=army->getUnitList()->getLlist().head;
        while(current!=nullptr){
            if(calculateDistance(this->pos,current->unit->getCurrentPosition())<=1){
                current->unit->setAttackScorestatic(0);
            }
            current=current->next;
        }
}
//!----------------------------------------------
//! CLASS BattleField
//!----------------------------------------------
BattleField::BattleField(int n_rows, int n_cols, const vector<Position*>& arrayForest,
                         const vector<Position*>& arrayRiver, const vector<Position*>& arrayFortification,
                         const vector<Position*>& arrayUrban, const vector<Position*>& arraySpecialZone)
    : n_rows(n_rows), n_cols(n_cols)
{
    terrain = new TerrainElement**[n_rows];
    for (int i = 0; i < n_rows; ++i) {
        terrain[i] = new TerrainElement*[n_cols];
        for (int j = 0; j < n_cols; ++j) {
            terrain[i][j] = nullptr; 
        }
    }
        for (const auto& pos : arrayForest) {
        if(pos->getRow()<0||pos->getCol()<0||pos->getRow()>=n_rows||pos->getCol()>=n_cols) continue;
        if(terrain[pos->getRow()][pos->getCol()]!=nullptr) continue;
        // delete terrain[pos->getRow()][pos->getCol()];
        terrain[pos->getRow()][pos->getCol()] = new Mountain(*pos);
    }
    for (const auto& pos : arrayRiver) {
        if(pos->getRow()<0||pos->getCol()<0||pos->getRow()>=n_rows||pos->getCol()>=n_cols) continue;
        if(terrain[pos->getRow()][pos->getCol()]!=nullptr) continue;
        // delete terrain[pos->getRow()][pos->getCol()];
        terrain[pos->getRow()][pos->getCol()] = new River(*pos);
    }
    for (const auto& pos : arrayFortification) {
        if(pos->getRow()<0||pos->getCol()<0||pos->getRow()>=n_rows||pos->getCol()>=n_cols) continue;
        if(terrain[pos->getRow()][pos->getCol()]!=nullptr) continue;
        // delete terrain[pos->getRow()][pos->getCol()];
        terrain[pos->getRow()][pos->getCol()] = new Fortification(*pos);
    }
    for (const auto& pos : arrayUrban) {
        if(pos->getRow()<0||pos->getCol()<0||pos->getRow()>=n_rows||pos->getCol()>=n_cols) continue;
        if(terrain[pos->getRow()][pos->getCol()]!=nullptr) continue;
        // delete terrain[pos->getRow()][pos->getCol()];
        terrain[pos->getRow()][pos->getCol()] = new Urban(*pos);
    }
    for (const auto& pos : arraySpecialZone) {
        if(pos->getRow()<0||pos->getCol()<0||pos->getRow()>=n_rows||pos->getCol()>=n_cols) continue;
        if(terrain[pos->getRow()][pos->getCol()]!=nullptr) continue;
        // delete terrain[pos->getRow()][pos->getCol()];
        terrain[pos->getRow()][pos->getCol()] = new SpecialZone(*pos);
    }
    for (int i = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            if(terrain[i][j] == nullptr){
                Position p(i,j);
                terrain[i][j]=new Road(p);
            }
        }
    }
}

BattleField::~BattleField() {
    for (int i = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            delete terrain[i][j];
        }
        delete[] terrain[i];
    }
    delete[] terrain;
    terrain = nullptr;
}

TerrainElement* BattleField::getElement(int r, int c) const {
    if(r<0||c<0||r>=n_rows||c>=n_cols) return nullptr;
    if(terrain[r][c]==nullptr){
        Position p=(r,c);
        TerrainElement* defaultTerrain= new Road(p);
        return defaultTerrain;
    } 
    return terrain[r][c];

}

string BattleField::str() const {
    stringstream ss;
    ss<<"BattleField[n_rows="<<n_rows<<",n_cols="<<n_cols<<"]";
    return ss.str().c_str();
}
//!-----------------------------------------------------
//! CLASS Configuration
//!-----------------------------------------------------
Configuration::Configuration(const std::string &filepath) {
    liberationUnits=nullptr;
    ARVNUnits=nullptr;
    numOfLiberUnit=0;
    numOfARVNUnit=0;
    ifstream file;
    file.open(filepath);
    if(!file.is_open()) {
        cout<<"bye";
        return;
    }
    string s;
    vector<string> vec;
    while(getline(file,s)){
        vec.push_back(s);
    }
    size_t pos;
    for(int i=0;i<vec.size();++i){
        pos = vec.at(i).find("NUM_ROWS");
        if (pos != std::string::npos) {
            int index=9;
            for(index;vec.at(i)[index]!='-'&&(vec.at(i)[index]<'0'||vec.at(i)[index]>'9');++index);
            istringstream ss(vec.at(i).substr(index));
            ss>>this->num_rows;
            continue;
        }
        pos = vec.at(i).find("NUM_COLS");
        if (pos != std::string::npos) {
            int index=9;
            for(index;vec.at(i)[index]!='-'&&(vec.at(i)[index]<'0'||vec.at(i)[index]>'9');++index);
            istringstream ss(vec.at(i).substr(index));
            ss>>this->num_cols;
            continue;
        }
    } 
    if(this->num_rows<=0||this->num_cols<=0){
        return;
    }
    // battlefield=new TerrainType*[NUM_ROWS];
    // for(int i=0;i<NUM_ROWS;++i){
    //     battlefield[i]=new TerrainType[NUM_COLS]();
    // }
    for(int i=0;i<vec.size();++i){
        pos = vec.at(i).find("EVENT_CODE");
        if (pos != std::string::npos) {
            int index=11;
            for(index;vec.at(i)[index]!='-'&&(vec.at(i)[index]<'0'||vec.at(i)[index]>'9');++index);
            istringstream ss(vec.at(i).substr(index));
            ss>>this->eventCode;
            if(eventCode<0) eventCode=0;
            else eventCode=eventCode%100;
            continue;
        }
        pos = vec.at(i).find("ARRAY");
        if (pos != std::string::npos) {
            // if(vec.at(i).substr(6,4)=="ROAD"){
                // char switcher='y';
                // int positionx,positiony;
                // for(int j=vec.at(i).length()-2;vec.at(i)[j]!='[';--j){
                //     if(vec.at(i)[j]>='0'&&vec.at(i)[j]<='9'){
                //         if(switcher=='y'){
                //             int index1=j;
                //             for(index1;vec.at(i)[index1]!=',';--index1);
                //             istringstream ss(vec.at(i).substr(index1+1,j-index1-1));
                //             ss>>positiony;
                //             switcher='x';
                //             j=index1;
                //         }
                //         else if(switcher=='x'){
                //             int index1=j;
                //             for(index1;vec.at(i)[index1]!='(';--index1);
                //             istringstream ss(vec.at(i).substr(index1+1,j-index1-1));
                //             ss>>positionx;
                //             battlefield[positionx][positiony]=ROAD;
                //             switcher='y';
                //             j=index1;
                //         }
                //     }
                // }
            // }
            pos = vec.at(i).find("FORE");
            if (pos != std::string::npos) {
                char switcher='x';
                int positionx,positiony;
                for(int j=13;vec.at(i)[j]!=']';++j){
                    if(vec.at(i)[j]=='-'||vec.at(i)[j]>='0'&&vec.at(i)[j]<='9'){
                        if(switcher=='x'){
                            int index1=j;
                            for(index1;vec.at(i)[index1]!=',';++index1);
                            istringstream ss(vec.at(i).substr(j,index1-j));
                            ss>>positionx;
                            switcher='y';
                            j=index1;
                        }
                        else if(switcher=='y'){
                            int index1=j;
                            for(index1;vec.at(i)[index1]!=')';++index1);
                            istringstream ss(vec.at(i).substr(j,index1-j));
                            ss>>positiony;
                            Position* p=new Position(positionx,positiony);
                            arrayForest.push_back(p);
                            switcher='x';
                            j=index1;
                        }
                    }
                }
                continue;
            }
            pos = vec.at(i).find("RIV");
            if (pos != std::string::npos) {
                char switcher='x';
                int positionx,positiony;
                for(int j=12;vec.at(i)[j]!=']';++j){
                    if(vec.at(i)[j]=='-'||vec.at(i)[j]>='0'&&vec.at(i)[j]<='9'){
                        if(switcher=='x'){
                            int index1=j;
                            for(index1;vec.at(i)[index1]!=',';++index1);
                            istringstream ss(vec.at(i).substr(j,index1-j));
                            ss>>positionx;
                            switcher='y';
                            j=index1;
                        }
                        else if(switcher=='y'){
                            int index1=j;
                            for(index1;vec.at(i)[index1]!=')';++index1);
                            istringstream ss(vec.at(i).substr(j,index1-j));
                            ss>>positiony;
                            Position* p=new Position(positionx,positiony);
                            arrayRiver.push_back(p);
                            switcher='x';
                            j=index1;
                        }
                    }
                }
                continue;
            }
            pos = vec.at(i).find("FORT");
            if (pos != std::string::npos) {
                char switcher='x';
                int positionx,positiony;
                for(int j=20;vec.at(i)[j]!=']';++j){
                    if(vec.at(i)[j]=='-'||vec.at(i)[j]>='0'&&vec.at(i)[j]<='9'){
                        if(switcher=='x'){
                            int index1=j;
                            for(index1;vec.at(i)[index1]!=',';++index1);
                            istringstream ss(vec.at(i).substr(j,index1-j));
                            ss>>positionx;
                            switcher='y';
                            j=index1;
                        }
                        else if(switcher=='y'){
                            int index1=j;
                            for(index1;vec.at(i)[index1]!=')';++index1);
                            istringstream ss(vec.at(i).substr(j,index1-j));
                            ss>>positiony;
                            Position* p=new Position(positionx,positiony);
                            arrayFortification.push_back(p);
                            switcher='x';
                            j=index1;
                        }
                    }
                }
                continue;
            }
            pos = vec.at(i).find("SPEC");
            if (pos != std::string::npos) {
                char switcher='x';
                int positionx,positiony;
                for(int j=19;vec.at(i)[j]!=']';++j){
                    if(vec.at(i)[j]=='-'||vec.at(i)[j]>='0'&&vec.at(i)[j]<='9'){
                        if(switcher=='x'){
                            int index1=j;
                            for(index1;vec.at(i)[index1]!=',';++index1);
                            istringstream ss(vec.at(i).substr(j,index1-j));
                            ss>>positionx;
                            switcher='y';
                            j=index1;
                        }
                        else if(switcher=='y'){
                            int index1=j;
                            for(index1;vec.at(i)[index1]!=')';++index1);
                            istringstream ss(vec.at(i).substr(j,index1-j));
                            ss>>positiony;
                            Position* p=new Position(positionx,positiony);
                            arraySpecialZone.push_back(p);
                            switcher='x';
                            j=index1;
                        }
                    }
                }
                continue;
            }
            pos = vec.at(i).find("URBA");
            if (pos != std::string::npos) {
                char switcher='x';
                int positionx,positiony;
                for(int j=12;vec.at(i)[j]!=']';++j){
                    if(vec.at(i)[j]=='-'||vec.at(i)[j]>='0'&&vec.at(i)[j]<='9'){
                        if(switcher=='x'){
                            int index1=j;
                            for(index1;vec.at(i)[index1]!=',';++index1);
                            istringstream ss(vec.at(i).substr(j,index1-j));
                            ss>>positionx;
                            switcher='y';
                            j=index1;
                        }
                        else if(switcher=='y'){
                            int index1=j;
                            for(index1;vec.at(i)[index1]!=')';++index1);
                            istringstream ss(vec.at(i).substr(j,index1-j));
                            ss>>positiony;
                            Position* p=new Position(positionx,positiony);
                            arrayUrban.push_back(p);
                            switcher='x';
                            j=index1;
                        }
                    }
                }
                continue;
            }
        }
            pos = vec.at(i).find("UNIT");
            if (pos != std::string::npos) {
                liberationUnits= new Unit*[100];
                ARVNUnits= new Unit*[100];
                int j=11;
                while(vec.at(i)[j]!=']'){
                string name;
                int mark;
                for(j;vec.at(i)[j]!='(';++j){
                    name+=vec.at(i)[j];
                    mark=j+2;
                }
                istringstream ss(vec.at(i).substr(mark));
                char s1;
                int quantity,weight,positionx,positiony,ARVNside;
                ss>>quantity;
                ss>>s1;
                ss>>weight;
                ss>>s1>>s1;
                ss>>positionx;
                ss>>s1;
                ss>>positiony;
                ss>>s1>>s1;
                ss>>ARVNside;
                Position p(positionx,positiony);
                if(name=="SNIPER"||name=="ANTIAIRCRAFTSQUAD"||name=="MORTARSQUAD"||name=="ENGINEER"||name=="SPECIALFORCES"||name=="REGULARINFANTRY"){
                    InfantryType type;
                    if(name=="SNIPER")  type=SNIPER;
                    else if(name=="ANTIAIRCRAFTSQUAD")  type=ANTIAIRCRAFTSQUAD;
                    else if(name=="MORTARSQUAD")  type=MORTARSQUAD;
                    else if(name=="ENGINEER")  type=ENGINEER;
                    else if(name=="SPECIALFORCES")  type=SPECIALFORCES;
                    else if(name=="REGULARINFANTRY")  type=REGULARINFANTRY;
                    Infantry* temp=new Infantry(quantity,weight,p,type);
                    if(ARVNside){
                        ARVNUnits[numOfARVNUnit++]=new Infantry(temp);
                        delete temp;
                    }
                    else {
                        liberationUnits[numOfLiberUnit++]=new Infantry(temp);
                        delete temp;
                    }
                    for(j;vec.at(i)[j] != ']' && !(vec.at(i)[j] >= 'A' && vec.at(i)[j] <= 'Z');++j);
                }
                else{
                    VehicleType type;
                    if(name=="TRUCK")                type=TRUCK;
                    else if(name=="MORTAR")          type=MORTAR;
                    else if(name=="ANTIAIRCRAFT")    type=ANTIAIRCRAFT;
                    else if(name=="ARMOREDCAR")      type=ARMOREDCAR;
                    else if(name=="APC")             type=APC;
                    else if(name=="ARTILLERY")       type=ARTILLERY;
                    else if(name=="TANK")            type=TANK;
                    Vehicle* temp=new Vehicle(quantity,weight,p,type);
                    if(ARVNside){
                        ARVNUnits[numOfARVNUnit++]=new Vehicle(temp);
                        delete temp;
                    }
                    else {
                        liberationUnits[numOfLiberUnit++]=new Vehicle(temp);
                        delete temp;
                    }
                    for(j;vec.at(i)[j] != ']' && !(vec.at(i)[j] >= 'A' && vec.at(i)[j] <= 'Z');++j);
                }
            }
            continue;
        }
    }
    file.close();
}

Configuration::~Configuration() {
    for (Position* pos : arrayForest) {
        delete pos;
    }
    for (Position* pos : arrayRiver) {
        delete pos;
    }
    for (Position* pos : arrayFortification) {
        delete pos;
    }
    for (Position* pos : arrayUrban) {
        delete pos;
    }
    for (Position* pos : arraySpecialZone) {
        delete pos;
    }
    arrayForest.clear();
    arrayRiver.clear();
    arrayFortification.clear();
    arrayUrban.clear();
    arraySpecialZone.clear();
    if(numOfLiberUnit!=0){
        for (int i = 0; i < numOfLiberUnit; ++i) {
            delete liberationUnits[i];
        }
        delete[] liberationUnits;
    }
    else if(liberationUnits!=nullptr) delete[] liberationUnits;
    if(numOfARVNUnit!=0){
        for (int i = 0; i < numOfARVNUnit; ++i) {
            delete ARVNUnits[i];
        }
        delete[] ARVNUnits;
    }
    else if(ARVNUnits!=nullptr) delete[] ARVNUnits;
}

string Configuration::str() const {
    stringstream ss;
    ss<<"[num_rows="<<num_rows<<",num_cols="<<num_cols<<",arrayForest=[";
    int i=0;
    for( Position* pos : arrayForest){
        ss<<pos->str();
        if(i<arrayForest.size()-1){
            ss<<",";
        }
        ++i;
    }
    ss<<"],arrayRiver=[";
    i=0;
    for( Position* pos : arrayRiver){
        ss<<pos->str();
        if(i<arrayRiver.size()-1){
            ss<<",";
        }
        ++i;
    }
    ss<<"],arrayFortification=[";
    i=0;
    for( Position* pos : arrayFortification){
        ss<<pos->str();
        if(i<arrayFortification.size()-1){
            ss<<",";
        }
        ++i;
    }
    ss<<"],arrayUrban=[";
    i=0;
    for( Position* pos : arrayUrban){
        ss<<pos->str();
        if(i<arrayUrban.size()-1){
            ss<<",";
        }
        ++i;
    }
    ss<<"],arraySpecialZone=[";
    i=0;
    for( Position* pos : arraySpecialZone){
        ss<<pos->str();
        if(i<arraySpecialZone.size()-1){
            ss<<",";
        }
        ++i;
    }
    ss<<"],liberationUnits=[";
    i=0;
    for(int j=0;j<numOfLiberUnit;++j){
        ss<<liberationUnits[j]->str();
        if(j<numOfLiberUnit-1){
            ss<<",";
        }
    }
    ss<<"],ARVNUnits=[",
    i=0;
    for(int j=0;j<numOfARVNUnit;++j){
        ss<<ARVNUnits[j]->str();
        if(j<numOfARVNUnit-1){
            ss<<",";
        }
    }
    ss<<"],eventCode="<<eventCode<<"]";
    return ss.str().c_str();
}
//!-----------------------------------------------------
//! Lớp HCMCampaign
//!-----------------------------------------------------

HCMCampaign::HCMCampaign(const string & config_file_path){
    this->config=new Configuration(config_file_path);
    this->battleField=new BattleField(config->getNumRows(),config->getNumCols(),config->getForestPositions(),config->getRiverPositions(),config->getFortificationPositions(),config->getUrbanPositions(),config->getSpecialZonePositions());
    Unit **unitArrayLiberation=new Unit*[config->getNumOfLiberUnit()];
    for(int i=0;i<config->getNumOfLiberUnit();++i){
        unitArrayLiberation[i]=config->getLiberationUnits()[i];
    }
    this->liberationArmy= new LiberationArmy(unitArrayLiberation,config->getNumOfLiberUnit(),"LiberationArmy",battleField);
    Unit **unitArrayARVN=new Unit*[config->getNumOfARVNUnit()];
    for(int i=0;i<config->getNumOfARVNUnit();++i){
        unitArrayARVN[i]=config->getARVNUnits()[i];
    }
    this->arvnArmy= new ARVN(unitArrayARVN,config->getNumOfARVNUnit(),"ARVNArmy",battleField);
    delete[] unitArrayLiberation;
    delete[] unitArrayARVN;
}
HCMCampaign::~HCMCampaign(){
    delete config;
    delete battleField;
    // if(!(liberationArmy->getUnitList()->getCountVehicle()==0&&liberationArmy->getUnitList()->getCountVehicle()==0)){
        delete liberationArmy;
    // }
    // if(!(arvnArmy->getUnitList()->getCountVehicle()==0&&arvnArmy->getUnitList()->getCountVehicle()==0)){
        delete arvnArmy;
    // }
}

void HCMCampaign::run(){
        for(int i=0;i<battleField->getn_rows();++i){
        for(int j=0;j<battleField->getn_cols();++j){
            TerrainElement* element = battleField->getElement(i,j);
            if(!element) continue;
            if(element->getTerrainType()==MOUNTAIN){
                element->getEffect(liberationArmy);
                element->getEffect(arvnArmy);
            }
        }
    }
    for(int i=0;i<battleField->getn_rows();++i){
        for(int j=0;j<battleField->getn_cols();++j){
            TerrainElement* element = battleField->getElement(i,j);
            if(!element) continue;
            if(element->getTerrainType()==RIVER){
                element->getEffect(liberationArmy);
                element->getEffect(arvnArmy);
            }
        }
    }
    for(int i=0;i<battleField->getn_rows();++i){
        for(int j=0;j<battleField->getn_cols();++j){
            TerrainElement* element = battleField->getElement(i,j);
            if(!element) continue;
            if(element->getTerrainType()==URBAN){
                element->getEffect(liberationArmy);
                element->getEffect(arvnArmy);
            }
        }
    }
    for(int i=0;i<battleField->getn_rows();++i){
        for(int j=0;j<battleField->getn_cols();++j){
            TerrainElement* element = battleField->getElement(i,j);
            if(!element) continue;
            if(element->getTerrainType()==FORTIFICATION){
                element->getEffect(liberationArmy);
                element->getEffect(arvnArmy);
            }
        }
    }
    for(int i=0;i<battleField->getn_rows();++i){
        for(int j=0;j<battleField->getn_cols();++j){
            TerrainElement* element = battleField->getElement(i,j);
            if(!element) continue;
            if(element->getTerrainType()==SPECIAL_ZONE){
                element->getEffect(liberationArmy);
                element->getEffect(arvnArmy);
            }
        }
    }
    if(config->getEventCode()<75){
        liberationArmy->fight(arvnArmy,false);
        arvnArmy->fight(liberationArmy,true);
    }
    else{
        arvnArmy->fight(liberationArmy,false);
        liberationArmy->fight(arvnArmy,true);
        liberationArmy->fight(arvnArmy,false);
        arvnArmy->fight(liberationArmy,true);
    }
    node*currentliber=liberationArmy->getUnitList()->getLlist().head;
    node*currentarvn=arvnArmy->getUnitList()->getLlist().head;
    while(currentliber!=nullptr){
        if(currentliber->unit->getAttackScorestatic()<=5){
            node*temp =currentliber;
            currentliber=currentliber->next;
            liberationArmy->getUnitList()->removeNode(liberationArmy->getUnitList()->getLlistRef(),temp);
            temp=nullptr;
            continue;
        }
        currentliber=currentliber->next;
    }
    while(currentarvn!=nullptr){
        if(currentarvn->unit->getAttackScorestatic()<=5){
            node*temp =currentarvn;
            currentarvn=currentarvn->next;
            arvnArmy->getUnitList()->removeNode(arvnArmy->getUnitList()->getLlistRef(),temp);
            temp=nullptr;
            continue;
        }
        currentarvn=currentarvn->next;
    }
    currentliber=liberationArmy->getUnitList()->getLlist().head;
    currentarvn=arvnArmy->getUnitList()->getLlist().head;
    liberationArmy->setLF(0);
    liberationArmy->setEXP(0);
    arvnArmy->setLF(0);
    arvnArmy->setEXP(0);
    while(currentliber!=nullptr){
        if(currentliber->unit->isVehi()){
            liberationArmy->setLF(liberationArmy->getLF()+currentliber->unit->getnewAttackScore(1));
            currentliber=currentliber->next;
        }
        else{
            liberationArmy->setEXP(liberationArmy->getEXP()+currentliber->unit->getnewAttackScore(1));
            currentliber=currentliber->next;
        }
    }
    while(currentarvn!=nullptr){
        if(currentarvn->unit->isVehi()){
            arvnArmy->setLF(arvnArmy->getLF()+currentarvn->unit->getnewAttackScore(1));
            currentarvn=currentarvn->next;
        }
        else{
            arvnArmy->setEXP(arvnArmy->getEXP()+currentarvn->unit->getnewAttackScore(1));
            currentarvn=currentarvn->next;
        }
    }
    liberationArmy->setLF(max(0,min(liberationArmy->getLF(), 1000)));
    liberationArmy->setEXP(max(0,min(liberationArmy->getEXP(), 500)));
    arvnArmy->setLF(max(0,min(arvnArmy->getLF(), 1000)));
    arvnArmy->setEXP(max(0,min(arvnArmy->getEXP(), 500)));
}
string HCMCampaign::printResult(){
    stringstream ss;
    ss<<"LIBERATIONARMY[LF="<<liberationArmy->getLF()<<",EXP="<<liberationArmy->getEXP()<<"]-ARVN[LF="<<arvnArmy->getLF()<<",EXP="<<arvnArmy->getEXP()<<"]";
    return ss.str().c_str();
}