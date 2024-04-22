#include "TButton.h"

void TButton::normText() {
    text.setPosition(x + (width - len * FontSize / 2) / 2, y + (height - FontSize) / 2);
}
TButton::TButton() : TClickable() {
    len = 0;
    text.setPosition(0, 0);
    text.setFont(font);
    text.setCharacterSize(FontSize);
    text.setFillColor(Color::Black);
}
void TButton::setText(std::string toSet) {
    text.setString(toSet);
    len = toSet.size();
    normText();
}
void TButton::setPos(int tx, int ty) {
    TObject::setPos(tx, ty);
    normText();
}
void TButton::setSize(int twidth, int theight) {
    TObject::setSize(twidth, theight);
    normText();
}
void TButton::onPress() {
    background.setFillColor(Color(50, 170, 50));
}
void TButton::onRelease() {
    background.setFillColor(Color::Green);
}
void TButton::draw(RenderWindow& win) {
    TObject::draw(win);
    win.draw(text);
}
void TButton::serialize(std::ofstream& out) {
    TObject::serialize(out);

    std::string str = text.getString();
    char length = str.size();
    out.write(&length, sizeof(length));
    out.write(str.c_str(), length);
}
void TButton::deserialize(std::ifstream& in) {
    TObject::deserialize(in);

    char length;
    in.read(&length, sizeof(length));
    char* buffer = new char[length + 1];
    in.read(buffer, length);
    buffer[length] = '\0';
    std::string str(buffer);
    delete[] buffer;
    setText(str);
}
void TButton::jsonSerialize(json& j) {

    TObject::jsonSerialize(j);

    j["text"] = text.getString();
}

void TButton::jsonDeserialize(json& j) {

    TObject::jsonDeserialize(j);

    setText(j["text"]);

}