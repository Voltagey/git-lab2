#ifndef SOFTWARE_H
#define SOFTWARE_H

#include <string>

class Software {
protected:
    std::string name;
    std::string company;

public:
    Software();
    Software(const std::string& name, const std::string& company);
    virtual ~Software();

    std::string getCompany() const;
    void setCompany(const std::string& company);

    virtual void show() const;
};

#endif
