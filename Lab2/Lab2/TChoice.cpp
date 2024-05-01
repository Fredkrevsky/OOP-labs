#include "TChoice.h"

TChoice::TChoice() : TClickable() {
    isSelected = false;
    in.setFillColor(Color(30, 30, 30));
    in.setPosition(x + width / 4, y + height / 4);
    in.setSize(Vector2f(width / 2, height / 2));
}
void TChoice::setPos(int tx, int ty) {
    TObject::setPos(tx, ty);
    in.setPosition(tx + width / 4, ty + height / 4);
}
void TChoice::setSize(int twidth, int theight) {
    TObject::setSize(twidth, theight);
    in.setPosition(x + twidth / 4, y + theight / 4);
    in.setSize(Vector2f(twidth / 2, theight / 2));
}
void TChoice::onPress() {
    isSelected = !isSelected;
    setStatus(isSelected);
}
void TChoice::onRelease() { }
void TChoice::setStatus(bool status) {
    isSelected = status;
}
void TChoice::draw(RenderWindow& win) {
    TObject::draw(win);
    if (isSelected) {
        win.draw(in);
    }
}
bool TChoice::getStatus() {
    return isSelected;
}
void TChoice::serialize(std::ofstream& out) {
    TObject::serialize(out);
    out.write(reinterpret_cast<char*>(&isSelected), sizeof(bool));
}
void TChoice::deserialize(std::ifstream& in) {
    TObject::deserialize(in);
    bool isSel;
    in.read(reinterpret_cast<char*>(&isSel), sizeof(isSel));
    setStatus(isSel);
}
void TChoice::jsonSerialize(json& j) {

    TObject::jsonSerialize(j);

    j["isSelected"] = isSelected;
}

void TChoice::jsonDeserialize(json& j) {

    TObject::jsonDeserialize(j);

    setStatus(j["isSelected"]);
}