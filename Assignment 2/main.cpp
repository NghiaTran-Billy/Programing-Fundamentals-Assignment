#include"hcmcampaign.h"

int main() {
    string name = "Task3932";
    stringstream output;
    //! data ------------------------------------
    Unit **unit = new Unit *[2];
    unit[0] = new Infantry(10, 10, Position(5, 5), SNIPER);
    unit[1] = new Vehicle(100, 10, Position(5, 5), TRUCK);

    ARVN *army = new ARVN(unit, 2, "ARVN", 0);
    output << army->str() << endl;
    Fortification(Position(3, 5)).getEffect(army); // R = 2
    Fortification(Position(3, 3)).getEffect(army); // R > 2
    Fortification(Position(4, 4)).getEffect(army); // R < 2
    output << army->str() << endl;

    Mountain(Position(3, 5)).getEffect(army); // R = 2
    output << army->str() << endl;
    delete army;
    delete unit[0];
    delete unit[1];
    delete[] unit;

    //! expect ----------------------------------
    string expect =
        "ARVN[LF=34,EXP=100,unitList=UnitList[count_vehicle=1;count_infantry=1;"
        "Infantry[infantryType=SNIPER,quantity=10,weight=10,position=(5,5)],"
        "Vehicle[vehicleType=TRUCK,quantity=100,weight=10,position=(5,5)]],battleField=]\n"

        "ARVN[LF=32,EXP=129,unitList=UnitList[count_vehicle=1;count_infantry=1;"
        "Infantry[infantryType=SNIPER,quantity=10,weight=10,position=(5,5)],"
        "Vehicle[vehicleType=TRUCK,quantity=100,weight=10,position=(5,5)]],battleField=]\n";
    // stringstream output;
    // output << result;
    cout << output.str().c_str();
    return 0;
}