#include "TProgressBar.h"

inline void TProgressBar::setWidth() {
    posX = width * value;
}
inline void TProgressBar::setTextPosition() {
    text.setPosition(x + 4, y + (height - FontSize) / 2 - 3);
}
inline void TProgressBar::setString() {
    int toSet = std::round(abs(value) * 100);
    std::string result = std::to_string(toSet);
    result.push_back('%');
    text.setString(result);
}

TProgressBar::TProgressBar() : TBar() { }

void TProgressBar::setPos(int tx, int ty) {
    TObject::setPos(tx, ty);

    first.setPosition(tx, ty);
    second.setPosition(tx + posX, ty);

    setTextPosition();
}
void TProgressBar::setSize(int twidth, int theight) {
    TObject::setSize(twidth, theight);

    first.setSize(Vector2f(twidth, theight));

    second.setSize(Vector2f(width - posX, height));
    second.setPosition(x + posX, y);

    setTextPosition();
}
void TProgressBar::setValue(float toSet) {
    value = toSet;
    setWidth();
    setString();
    setTextPosition();
    first.setSize(Vector2f(posX, height));
    second.setPosition(x + posX, y);
    second.setSize(Vector2f(width - posX, height));
}
void TProgressBar::serialize(std::ofstream& out) {
    TObject::serialize(out);
    
    Color color = first.getFillColor();
    out.write(reinterpret_cast<char*>(&color), sizeof(color));
    color = second.getFillColor();
    out.write(reinterpret_cast<char*>(&color), sizeof(color));
    out.write(reinterpret_cast<char*>(&value), sizeof(value));
}
void TProgressBar::deserialize(std::ifstream& in) {
    TObject::deserialize(in);
    Color color;
    float tvalue;

    in.read(reinterpret_cast<char*>(&color), sizeof(color));
    setFirstColor(color);
    in.read(reinterpret_cast<char*>(&color), sizeof(color));
    setSecondColor(color);
    in.read(reinterpret_cast<char*>(&tvalue), sizeof(tvalue));
    setValue(tvalue);
}
void TProgressBar::jsonSerialize(json& j) {

    TObject::jsonSerialize(j);

    Color color = first.getFillColor();
    j["first_color"]["r"] = color.r;
    j["first_color"]["g"] = color.g;
    j["first_color"]["b"] = color.b;
    j["first_color"]["a"] = color.a;

    color = second.getFillColor();
    j["second_color"]["r"] = color.r;
    j["second_color"]["g"] = color.g;
    j["second_color"]["b"] = color.b;
    j["second_color"]["a"] = color.a;

    j["value"] = value;
}

void TProgressBar::jsonDeserialize(json& j) {

    TObject::jsonDeserialize(j);

    Color color;
    color.r = j["first_color"]["r"];
    color.g = j["first_color"]["g"];
    color.b = j["first_color"]["b"];
    color.a = j["first_color"]["a"];
    setFirstColor(color);

    color.r = j["second_color"]["r"];
    color.g = j["second_color"]["g"];
    color.b = j["second_color"]["b"];
    color.a = j["second_color"]["a"];
    setSecondColor(color);

    setValue(j["value"]);
}
