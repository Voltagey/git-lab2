#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include "Software.h"

class TextEditor : public Software {
private:
    std::string format;

public:
    TextEditor();
    TextEditor(const std::string& name, const std::string& company, const std::string& format);

    void setFormat(const std::string& format);
    std::string getFormat() const;

    void show() const override;
};

#endif
