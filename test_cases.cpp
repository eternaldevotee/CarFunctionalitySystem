#include <iostream>
#include <cassert>
#include "car.h"
using namespace std;
void Accelerate() {
    Car car;
    car.shiftGear(GearState::DRIVE);
    car.accelerate(30);
    assert(car.getSpeed() == 30);
   cout << "Accelerate passed"<<endl;
}

void Brake() {
    Car car;
    car.shiftGear(GearState::DRIVE);
    car.accelerate(40);
    car.brake(10);
    assert(car.getSpeed() == 30);
    cout << "Brake passed"<<endl;
}

void ShiftGearSafety() {
    Car car;
    car.shiftGear(GearState::NEUTRAL);
    assert(car.getGearState() == GearState::NEUTRAL);
    cout << "ShiftGearSafety passed.\n";
}

void DestinationAndArrival() {
    Car car;
    car.setDestination({1.0, 1.0});
    assert(!car.hasArrived());
    car.shiftGear(GearState::DRIVE);
    car.accelerate(200);
    car.drive(1); 
    assert(car.hasArrived());
    cout << "Destination And Arrival passed"<<endl;
}

void DrivePartial() {
    Car car;
    car.setDestination({1.0, 1.0});
    car.shiftGear(GearState::DRIVE);
    car.accelerate(10);
    car.drive(0.1);
    assert(!car.hasArrived());
    cout << "Drive Partial passed"<<endl;
}

int main() {
    testAccelerate();
    testBrake();
    testShiftGearSafety();
    testDestinationAndArrival();
    testDrivePartial();
    cout << "All tests passed successfully."<<endl;
    return 0;
}
