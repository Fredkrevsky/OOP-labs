#include "TObject.h"
#include <iostream>

TObject::TObject() {
    background.setFillColor(Color(230, 230, 230));
    background.setPosition(0, 0);
    background.setSize(Vector2f(0, 0));
    background.setOutlineColor(Color(30, 30, 30));
}
bool TObject::contains(Vector2f mousePos) {
    return background.getGlobalBounds().contains(mousePos);
}
void TObject::setPos(int tx, int ty) {
    x = tx;
    y = ty;
    background.setPosition(Vector2f(x, y));
}
void TObject::setSize(int twidth, int theight) {
    width = twidth;
    height = theight;
    background.setSize(Vector2f(width, height));
}
void TObject::getPos(int& tx, int& ty) {
    tx = x;
    ty = y;
}
void TObject::getSize(int& w, int& h) {
    w = width;
    h = height;
}

void TObject::setColor(Color color) {
    background.setFillColor(color);
}
void TObject::setThickness(int thickness) {
    background.setOutlineThickness(thickness);
}
void TObject::draw(RenderWindow& win) {
    win.draw(background);
}
void TObject::serialize(std::ofstream& out) {
    out.write(reinterpret_cast<char*>(&x), sizeof(x));
    out.write(reinterpret_cast<char*>(&y), sizeof(y));
    out.write(reinterpret_cast<char*>(&width), sizeof(width));
    out.write(reinterpret_cast<char*>(&height), sizeof(height));

    Color color = background.getFillColor();
    out.write(reinterpret_cast<char*>(&color), sizeof(color));

    int thick = background.getOutlineThickness();
    out.write(reinterpret_cast<char*>(&thick), sizeof(thick));
}
void TObject::deserialize(std::ifstream& in) {
    int tx, ty, twidth, theight, thick;
    Color color;

    in.read(reinterpret_cast<char*>(&tx), sizeof(tx));
    in.read(reinterpret_cast<char*>(&ty), sizeof(ty));
    setPos(tx, ty);

    in.read(reinterpret_cast<char*>(&twidth), sizeof(twidth));
    in.read(reinterpret_cast<char*>(&theight), sizeof(theight));
    setSize(twidth, theight);

    in.read(reinterpret_cast<char*>(&color), sizeof(color));
    background.setFillColor(color);

    in.read(reinterpret_cast<char*>(&thick), sizeof(thick));
    background.setOutlineThickness(thick);
}

void TObject::jsonSerialize(json& j) {

    j["x"] = x;
    j["y"] = y;
    j["width"] = width;
    j["height"] = height;

    Color color = background.getFillColor();
    j["fill_color"]["r"] = color.r;
    j["fill_color"]["g"] = color.g;
    j["fill_color"]["b"] = color.b;
    j["fill_color"]["a"] = color.a;

    int thick = background.getOutlineThickness();
    j["outline_thickness"] = thick;
}
void TObject::jsonDeserialize(json& j) {

    setPos(j["x"], j["y"]);
    setSize(j["width"], j["height"]);

    Color color;
    color.r = j["fill_color"]["r"];
    color.g = j["fill_color"]["g"];
    color.b = j["fill_color"]["b"];
    color.a = j["fill_color"]["a"];
    background.setFillColor(color);

    background.setOutlineThickness(j["outline_thickness"]);
}