#ifndef OPERATINGSYSTEM_H
#define OPERATINGSYSTEM_H

#include "Software.h"

class OperatingSystem : public Software {
private:
    int bitness;

public:
    OperatingSystem();
    OperatingSystem(const std::string& name, const std::string& company, int bitness);

    void setBitness(int bitness);
    int getBitness() const;

    void show() const override;
};

#endif
