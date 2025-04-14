#include <iostream>
#include "car.h"
using namespace std;

int main() {
    Car myCar;

    cout << "Initial state:" << endl;
    cout << "Gear: " << Car::gearStateToString(myCar.getGearState()) << endl;
    cout << "Speed: " << myCar.getSpeed() << " km/h" << endl;

    // Set destination
    Location destination = {10.0, 10.0};
    myCar.setDestination(destination);

    // Start driving
    myCar.shiftGear(GearState::DRIVE);
    myCar.accelerate(20.0); // Accelerate to 20 km/h

    cout << "\nAfter starting:" << endl;
    cout << "Gear: " << Car::gearStateToString(myCar.getGearState()) << endl;
    cout << "Speed: " << myCar.getSpeed() << " km/h" << endl;
    cout << "Time to destination: " << myCar.timeToDestination() << " hours" << endl;

    // Drive for 0.5 hours
    myCar.drive(0.5);

    cout << "\nAfter driving for 0.5 hours:" << endl;
    Location loc = myCar.getLocation();
    cout << "Location: (" << loc.latitude << ", " << loc.longitude << ")" << endl;
    cout << "Time to destination: " << myCar.timeToDestination() << " hours" << endl;

    return 0;
}