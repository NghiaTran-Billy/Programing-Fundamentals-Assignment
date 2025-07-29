// The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_HCM_CAMPAIGN_H_
#define _H_HCM_CAMPAIGN_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class Unit;
class UnitList;
class Army;
class TerrainElement;

class Vehicle;
class Infantry;

class LiberationArmy;
class ARVN;

class Position;

class Road;
class Mountain;
class River;
class Urban;
class Fortification;
class SpecialZone;

class BattleField;

class HCMCampaign;
class Configuration;

enum VehicleType
{
    TRUCK,
    MORTAR,
    ANTIAIRCRAFT,
    ARMOREDCAR,
    APC,
    ARTILLERY,
    TANK
};
enum InfantryType
{
    SNIPER,
    ANTIAIRCRAFTSQUAD,
    MORTARSQUAD,
    ENGINEER,
    SPECIALFORCES,
    REGULARINFANTRY
};

enum TerrainType
{
    ROAD,
    MOUNTAIN,
    RIVER,
    FORTIFICATION,
    URBAN,
    SPECIAL_ZONE
};
//!-----------------------------------------------------
//! CLASS Position
//!-----------------------------------------------------
class Position
{
private:
    int r, c;

public:
    Position(int r = 0, int c = 0);
    Position(const string &str_pos);
    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);
    string str() const;
};

//!-----------------------------------------------------
//! CLASS Unit
//!-----------------------------------------------------
class Unit
{
protected:
    int quantity, weight;
    Position pos;
    bool vehi;
    int attackscorestatic;
    bool markcheckinsert;
public:
    Unit(int quantity, int weight, Position pos);
    virtual ~Unit();
    virtual int getAttackScore() = 0;
    virtual int getAttackScorestatic() const =0;
    void setAttackScorestatic(int newattackscorestatic) {this->attackscorestatic=newattackscorestatic;};
    Position getCurrentPosition() const;
    virtual string str() const = 0;
    void setWeight(int weight) { this->weight = weight; }
    void setQuantity(int quantity) { this->quantity = quantity; }
    int getQuantity() const { return quantity; }
    int getWeight() const { return weight; }
    virtual bool isVehi() const = 0;
    void setCurrentPosition(Position newpos){
        this->pos.setRow(newpos.getRow());
        this->pos.setCol(newpos.getCol());
    };
    void setMarkCheckInsert(bool a){this->markcheckinsert=a;};
    bool getMarkCheckInsert()const{return this->markcheckinsert;};
    virtual int getnewAttackScore(double) =0;
    int safeCeil(double value) {
        double diff = abs(value - round(value));
        return (diff < 1e-9) ? round(value) : ceil(value);
    }
};

//!-----------------------------------------------------
//! CLASS Infantry : public Unit
//!-----------------------------------------------------
class Infantry : public Unit
{
protected:
    InfantryType infantryType; 

public:
    Infantry(int quantity, int weight, Position pos, InfantryType infantryType);
    // Infantry(int quantity, int weight, Position pos):Unit(quantity,weight,pos){
    //     this->vehi=0;
    //     if(quantity<=0){ 
    //         quantity=1;
    //         this->quantity=quantity;
    //     }
    //     if(weight<=0){
    //          weight=1;
    //          this->weight=weight;
    //     }
    //     this->attackscorestatic=getnewAttackScore(1);
    // };
    Infantry(Infantry* infantry):Unit(infantry->getQuantity(),infantry->getWeight(),infantry->getCurrentPosition()){
        this->infantryType=infantry->infantryType;
        vehi=0;
        this->attackscorestatic=getnewAttackScore(1);
    }
    int getAttackScore() override;
    int getAttackScorestatic() const override {return this->attackscorestatic;};
    int getAttackScoreInFight();
    int getnewAttackScore(double) ;
    bool isVehi() const override{return vehi;};
    InfantryType getInfantryType()const {return infantryType;};
    void setInfantryType(InfantryType type){ this->infantryType=type;};
    string str() const override;
    int summingDigits(int a);
};

//!-----------------------------------------------------
//! CLASS Vehicle : public Unit
//!-----------------------------------------------------
class Vehicle : public Unit
{
protected:
    VehicleType vehicleType; 
public:
    Vehicle(int quantity, int weight, Position pos, VehicleType vehicleType);
    // Vehicle(int quantity, int weight, Position pos):Unit(quantity,weight,pos){
    //     this->vehi=1;
    //             if(quantity<=0){ 
    //         quantity=1;
    //         this->quantity=quantity;
    //     }
    //     if(weight<=0){
    //          weight=1;
    //          this->weight=weight;
    //     }
    //     this->attackscorestatic=getnewAttackScore(1);
        
    // };
    Vehicle(Vehicle* vehicle):Unit(vehicle->getQuantity(),vehicle->getWeight(),vehicle->getCurrentPosition()){
        this->vehicleType=vehicle->vehicleType;
                if(quantity<=0){ 
            quantity=1;
            this->quantity=quantity;
        }
        if(weight<=0){
             weight=1;
             this->weight=weight;
        }
        this->attackscorestatic=getnewAttackScore(1);
        this->vehi=1;
    }
    int getAttackScore() override;
    int getAttackScorestatic() const override {return this->attackscorestatic;};
    int getnewAttackScore(double) ;
    VehicleType getVehicleType()const{return vehicleType;};
    string str() const override;
    bool isVehi() const override{return vehi;};
};

//!-----------------------------------------------------
//! CLASS UnitList
//!-----------------------------------------------------
struct node{
    Unit* unit;
    node* next;
    bool vehi;
    int index;
    bool ownsUnit;
    node(node*next=nullptr):next(next),ownsUnit(false){};
    node(Unit *unit,node* next=nullptr,bool owns = false):unit(unit),next(next),ownsUnit(owns){};
    virtual ~node();
};

struct nodeinfantry:public node{
    nodeinfantry(Infantry *unit1,node* next=nullptr, bool owns = false){
        this->unit=unit1;
        this->next=next;
        this->vehi=0;
    };
    nodeinfantry(nodeinfantry* copy): node(nullptr, nullptr, true){
        this->unit=new Infantry(dynamic_cast<Infantry*>(copy->unit));
        this->next=nullptr;
        this->vehi=copy->vehi;
        this->index=copy->index;
    };
};

struct nodevehicle:public node{
    nodevehicle(Vehicle *unit1,node* next=nullptr, bool owns = false){
        this->unit=unit1;
        this->next=next;
        this->vehi=1;
    };
    nodevehicle(nodevehicle* copy): node(nullptr, nullptr, true){
        this->unit=new Vehicle(dynamic_cast<Vehicle*>(copy->unit));
        this->next=nullptr;
        this->vehi=copy->vehi;
        this->index=copy->index;
    };
};

struct Llist{
    node* head;
    // ~Llist();
};

class UnitList {
  private:
    // Your implement
    int capacity;
    Llist list;
    int countVehicle, countInfantry;

  public:
    UnitList(int capacity);
    UnitList(UnitList &original);
    ~UnitList();
    bool insert(Unit *unit);
    bool insertLlistBackward(UnitList *, UnitList *);
    bool isContain(VehicleType vehicleType);
    bool isContain(InfantryType infantryType);
    Llist getLlist() const {
        return list;
    };
    Llist &getLlistRef() {
        return list;
    }
    void setLlist(node *pointer) {
        this->list.head = pointer;
    };
    string str() const;
    int getCountVehicle() const {
        return countVehicle;
    }
    void setCountVehicle(int newcount) {
        this->countVehicle = newcount;
    }
    int getCountInfantry() const {
        return countInfantry;
    }
    void setCountInfantry(int newcount) {
        this->countInfantry = newcount;
    }
    // int setcapacity(int capacity) { this->capacity = capacity; }
    int getCapacity() const {
        return capacity;
    };
    // * Additional functions if possible
    nodevehicle *findEqual(VehicleType vehicleType);
    nodeinfantry *findEqual(InfantryType infantryType);
    void insertIndex(Llist list);
    void removeKnapsack(Llist &, Llist);
    void removeNode(Llist &, node *);
    void clearLlist(Llist &llist);
    nodeinfantry *clonenode(nodeinfantry *original);
    nodevehicle *clonenode(nodevehicle *original);

    // vector<Unit *> getUnits() const;
    //  void reduceQuantity(int percent);
    //  void reduceWeight(int percent);
    //  void clear() {}
    //  void setUnits(vector<Unit *> units);
    //  void remove(Unit *unit);
    //  vector<Unit *>& getUnits();
    //  void removeUnits(vector<Unit*>& unitsToRemove);
};

//!-----------------------------------------------------
//! CLASS Army 
//!-----------------------------------------------------
class Army {
  protected:
    int LF;
    int EXP;
    string name;
    UnitList *unitList;
    bool liberfight;
    bool liberwin;
    BattleField *battleField;
    bool justice;

  public:
    virtual ~Army();
    virtual void fight(Army *enemy, bool defense = false) = 0;
    virtual string str() const = 0;
    bool getLiberFight() const {
        return liberfight;
    }
    bool getLiberWin() const {
        return liberwin;
    }
    int getLF() const {
        return LF;
    };
    void setLF(int newLF) {
        this->LF = newLF;
    };
    int getEXP() const {
        return EXP;
    };
    void setEXP(int newEXP) {
        this->EXP = newEXP;
    };
    bool isJustice() const {
        return justice;
    }
    UnitList *getUnitList() const {
        return this->unitList;
    };
    // * Additional functions if possible
    // virtual bool knapsackinfantry(Llist list, int minScore,Llist& newlist, double coefficient) = 0;
    // virtual bool knapsackvehicle(Llist list, int minScore,Llist& newlist, double coefficient) = 0;
    // virtual nodeinfantry* clonenode(nodeinfantry* original) =0;
    // virtual nodevehicle* clonenode(nodevehicle* original) =0;
    int safeCeil(double value) {
        double diff = abs(value - round(value));
        return (diff < 1e-9) ? round(value) : ceil(value);
    }
    Army(Unit **unitArray, int size, string name, BattleField *battleField);
    int support(int x, int i, int k);
    bool specialNumber(int S);
};

//!-----------------------------------------------------
//! CLASS LiberationArmy
//!-----------------------------------------------------
class LiberationArmy : public Army
{
private:
    // Unit **unitArray;       // For temporary
    // int size_V = 0;         // For temporary: vehicle count
    // int size_I = 0;         // For temporary: infantry count

public:
    LiberationArmy(Unit **unitArray, int size, string name, BattleField *battleField);
    // ~LiberationArmy();
    void fight(Army *enemy, bool defense) override;
    string str() const override;
    int nearestFibonacci(int value);
    // bool knapsackinfantry(Llist list, int minScore,vector<Unit*> newlist);
    bool knapsackinfantry(Llist list, int minScore,Llist& newlist,double coefficient) ;
    bool knapsackvehicle(Llist list, int minScore,Llist& newlist,double coefficient) ;
    nodeinfantry* clonenode(nodeinfantry* original) ;
    nodevehicle* clonenode(nodevehicle* original) ;
    // Unit* cloneUnit(Unit* original);
    // bool cloneList(Llist oldList,Llist& newlist);

    // Unit* cloneUnit(Unit* unit);
};

//!-----------------------------------------------------
//! CLASS ARVN
//!-----------------------------------------------------
class ARVN : public Army
{
// private:
//     Unit **unitArray;  
public:
    ARVN(Unit** unitArray, int size, string name, BattleField *battleField);
    void fight(Army* enemy, bool defense=false) override;
    string str() const;
    // * Additional functions if possible
    bool knapsackinfantry(Llist list, int minScore,Llist& newlist,double coefficient) ;
    bool knapsackvehicle(Llist list, int minScore,Llist& newlist,double coefficient) ;
    nodeinfantry* clonenode(nodeinfantry* original) ;
    nodevehicle* clonenode(nodevehicle* original) ;

    
};

//!-----------------------------------------------------
//! CLASS TerrainElement và các lớp dẫn xuất
//!-----------------------------------------------------
class TerrainElement {
protected:
    Position pos; 
    TerrainType terrainType;
    
public:
    TerrainElement(Position);
    virtual ~TerrainElement();
    TerrainType getTerrainType() const {return terrainType;};
    void setTerrainType(TerrainType type) {terrainType = type;};
    Position getCurrentPosition() const{return pos;};
    void setCurrentPosition(Position newpos){
        this->pos.setRow(newpos.getRow());
        this->pos.setCol(newpos.getCol());
    };
    virtual void getEffect(Army *army) = 0;
    double calculateDistance(const Position& pos1, const Position& pos2);
    int safeCeil(double value);
};

class Road : public TerrainElement {
public:
    Road(Position pos) : TerrainElement(pos) {
        this->terrainType = ROAD; 
    }
    void getEffect(Army *army) override;
};

class Mountain : public TerrainElement {
public:
    Mountain(Position pos) : TerrainElement(pos) {
        this->terrainType = MOUNTAIN; 
    }
    void getEffect(Army *army)override;
};

class River : public TerrainElement {
public:
    River(Position pos) : TerrainElement(pos) {
        this->terrainType = RIVER;
    }
    void getEffect(Army *army) override;
};

class Urban : public TerrainElement {
public:
    Urban(Position pos) : TerrainElement(pos) {
        this->terrainType = URBAN;
    }
    void getEffect(Army *army)override;
};

class Fortification : public TerrainElement {
public:
    Fortification(Position pos) : TerrainElement(pos) {
        this->terrainType = FORTIFICATION;
    }
    void getEffect(Army *army)override;
};

class SpecialZone : public TerrainElement {
public:
    SpecialZone(Position pos) : TerrainElement(pos) {
        this->terrainType = SPECIAL_ZONE;
    }
    void getEffect(Army *army)override;
};

//!-----------------------------------------------------
//! CLASS BattleField
//!-----------------------------------------------------
class BattleField {
private:
    int n_rows, n_cols;
    TerrainElement ***terrain;
public:
    BattleField(int n_rows, int n_cols, const vector<Position*>& arrayForest,
                const vector<Position*>& arrayRiver, const vector<Position*>& arrayFortification,
                const vector<Position*>& arrayUrban, const vector<Position*>& arraySpecialZone);
    ~BattleField();
    
    TerrainElement* getElement(int r, int c) const;
    int getn_rows()const{return n_rows;}
    int getn_cols()const{return n_cols;}
    string str() const;
};

//!-----------------------------------------------------
//! CLASS Configuration
//!-----------------------------------------------------
class Configuration {
private:
    int num_rows;
    int num_cols;
    vector<Position*> arrayForest;
    vector<Position*> arrayRiver;
    vector<Position*> arrayFortification;
    vector<Position*> arrayUrban;
    vector<Position*> arraySpecialZone;
    Unit** liberationUnits;
    Unit** ARVNUnits;
    int numOfLiberUnit;
    int numOfARVNUnit;
    
    int eventCode;
public:
    Configuration(const string & filepath);
    ~Configuration();
    string str() const;
    int getNumRows() const { return num_rows; }
    void setNumRows(int r) {this->num_rows=r;}
    int getNumCols() const { return num_cols; }
    void setNumCols(int c) {this->num_cols=c;}
    int getNumOfLiberUnit()const{return numOfLiberUnit;}
    void setNumOfLiberUnit(int a){this->numOfLiberUnit=a;}
    int getNumOfARVNUnit()const{return numOfARVNUnit;}
    void setNumOfARVNUnit(int a){this->numOfARVNUnit=a;}
    const vector<Position*>& getForestPositions() const { return arrayForest; }
    const vector<Position*>& getRiverPositions() const { return arrayRiver; }
    const vector<Position*>& getFortificationPositions() const { return arrayFortification; }
    const vector<Position*>& getUrbanPositions() const { return arrayUrban; }
    const vector<Position*>& getSpecialZonePositions() const { return arraySpecialZone; }
    int getEventCode() const { return eventCode; }
    void setEventCode(int code){this->eventCode=code;}
    Unit**& getLiberationUnits() { return liberationUnits; }
    Unit**& getARVNUnits() { return ARVNUnits; }
};

//!-----------------------------------------------------
//! Lớp HCMCampaign
//!-----------------------------------------------------
class HCMCampaign {
private:
    Configuration* config;
    BattleField* battleField;
    LiberationArmy* liberationArmy;
    ARVN* arvnArmy;
public:
    HCMCampaign(const string & config_file_path);
    ~HCMCampaign();
    void run();
    string printResult();
};
#endif