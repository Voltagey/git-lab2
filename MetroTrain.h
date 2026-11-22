#ifndef METROTRAIN_H
#define METROTRAIN_H

#include <string>

class MetroTrain {
private:
    bool headlightsOn;
    bool doorsClosed;
    int speed;

public:
    MetroTrain();
    MetroTrain(bool headlights, bool doors, int startSpeed);
    ~MetroTrain();

    void changeHeadlights();
    void openDoors();
    void closeDoors();
    void accelerate();
    void brake();
    void printState() const;

    std::string getModeDescription() const;
};

#endif
