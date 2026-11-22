#include "TextEditor.h"
#include <iostream>

using namespace std;

TextEditor::TextEditor() : Software(), format("TXT") {}

TextEditor::TextEditor(const string& name, const string& company, const string& format)
    : Software(name, company), format(format) {}

void TextEditor::setFormat(const string& format) {
    this->format = format;
}

string TextEditor::getFormat() const {
    return format;
}

void TextEditor::show() const {
    cout << "[Текстовый редактор] Название: " << name
         << " | Фирма: " << company
         << " | Формат: " << format << endl;
}
