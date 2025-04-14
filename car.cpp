#include "car.h"
#include <stdexcept>
#include <algorithm>

Car::Car() : gear(GearState::PARK), speed(0), hasDestination(false) {
    currentLocation = {0.0, 0.0};
    destination = {0.0, 0.0};
}

void Car::accelerate(double acceleration) {
    if (gear != GearState::DRIVE && gear != GearState::REVERSE) {
        throw std::runtime_error("Cannot accelerate in current gear");
    }

    speed += acceleration;
    // Prevent negative speed (use brake for deceleration)
    if (speed < 0) speed = 0;
}

void Car::brake(double brakeForce) {
    speed -= brakeForce;
    if (speed < 0) speed = 0;
}

void Car::shiftGear(GearState newGear) {
    // Prevent shifting to drive/reverse at high speeds
    if ((newGear == GearState::DRIVE || newGear == GearState::REVERSE) && speed > 10) {
        throw std::runtime_error("Cannot shift to drive/reverse at high speed");
    }

    gear = newGear;

    // When shifting to park, speed should be zero
    if (gear == GearState::PARK) {
        speed = 0;
    }
}

GearState Car::getGearState() const {
    return gear;
}

double Car::getSpeed() const {
    return speed;
}

Location Car::getLocation() const {
    return currentLocation;
}

Location Car::getDestination() const {
    return destination;
}

bool Car::hasArrived() const {
    if (!hasDestination) return false;
    return currentLocation.distanceTo(destination) < 0.001; // 1 meter tolerance
}

void Car::setDestination(const Location& dest) {
    destination = dest;
    hasDestination = true;
}

void Car::clearDestination() {
    hasDestination = false;
}

void Car::drive(double time) {
    if (gear != GearState::DRIVE && gear != GearState::REVERSE) {
        return; // Can't drive in park or neutral
    }

    if (!hasDestination) {
        return; // No destination set
    }

    double distance = speed * time;
    double totalDistance = currentLocation.distanceTo(destination);

    if (distance >= totalDistance) {
        // Reached destination
        currentLocation = destination;
        speed = 0;
        gear = GearState::PARK;
    } else {
        // Move part of the way
        double ratio = distance / totalDistance;
        currentLocation.latitude += (destination.latitude - currentLocation.latitude) * ratio;
        currentLocation.longitude += (destination.longitude - currentLocation.longitude) * ratio;
    }
}

double Car::timeToDestination() const {
    if (!hasDestination || speed == 0) {
        return 0;
    }

    double distance = currentLocation.distanceTo(destination);
    return distance / speed;
}

std::string Car::gearStateToString(GearState state) {
    switch(state) {
        case GearState::PARK:
            return "PARK";
        case GearState::REVERSE:
            return "REVERSE";
        case GearState::NEUTRAL:
            return "NEUTRAL";
        case GearState::DRIVE:
            return "DRIVE";
        default:
            return "UNKNOWN";
    }
}