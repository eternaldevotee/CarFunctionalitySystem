#ifndef CAR_H
#define CAR_H

#include <string>
#include <cmath>

enum class GearState {
    PARK,
    REVERSE,
    NEUTRAL,
    DRIVE
};

struct Location {
    double latitude;
    double longitude;

    double distanceTo(const Location& other) const {
        // Simple Euclidean distance for demonstration
        // In real application, use Haversine formula for geographical distance
        return std::sqrt(std::pow(latitude - other.latitude, 2) +
                        std::pow(longitude - other.longitude, 2));
    }
};

class Car {
private:
    GearState gear;
    double speed; // in km/h
    Location currentLocation;
    Location destination;
    bool hasDestination;

public:
    Car();

    // Core functionality
    void accelerate(double acceleration);
    void brake(double brakeForce);
    void shiftGear(GearState newGear);

    // Getters
    GearState getGearState() const;
    double getSpeed() const;
    Location getLocation() const;
    Location getDestination() const;
    bool hasArrived() const;

    // Destination management
    void setDestination(const Location& dest);
    void clearDestination();

    // Driving functions
    void drive(double time); // time in hours
    double timeToDestination() const;

    // Helper functions
    static std::string gearStateToString(GearState state);
};

#endif // CAR_H