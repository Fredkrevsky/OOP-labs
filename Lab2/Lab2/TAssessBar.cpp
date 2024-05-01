#include "TAssessBar.h"

inline void TAssessBar::setWidth() {
    if (abs(value) < 0.2) {
        posX = width / 2;
    }
    else if (value > 5) {
        posX = width;
    }
    else if (value < -5) {
        posX = 0;
    }
    else {
        posX = width * (value + 5) / 10;
    }
}
inline void TAssessBar::setTextColor() {
    if (value > 0) {
        text.setFillColor(second.getFillColor());
    }
    else {
        text.setFillColor(first.getFillColor());
    }
}
inline void TAssessBar::setTextPosition() {
    if (value < 0) {
        text.setPosition(x + width - 40, y + (height - FontSize) / 2 - 3);
    }
    else {
        text.setPosition(x + 4, y + (height - FontSize) / 2 - 3);
    }
}
inline void TAssessBar::setString() {
    float toSet = std::round(abs(value) * 100) / 100;
    std::string result = "";
    if (toSet > 0.15) {
        if (toSet > 99) {
            result = "win";
        }
        else {
            result = std::to_string(toSet);
            int dot = result.find(',');
            result = result.substr(0, dot + 2);
            result[dot] = '.';
        }
    }
    text.setString(result);
}

TAssessBar::TAssessBar() : TBar() { }

void TAssessBar::setPos(int tx, int ty) {
    TObject::setPos(tx, ty);

    first.setPosition(tx, ty);
    second.setPosition(tx + posX, ty);

    setTextPosition();
}
void TAssessBar::setSize(int twidth, int theight) {
    TObject::setSize(twidth, theight);

    first.setSize(Vector2f(twidth, theight));

    second.setSize(Vector2f(width - posX, height));
    second.setPosition(x + posX, y);

    setTextPosition();
}
void TAssessBar::setValue(float toSet) {
    value = toSet;
    setWidth();
    setString();
    setTextColor();
    setTextPosition();
    first.setSize(Vector2f(posX, height));
    second.setPosition(x + posX, y);
    second.setSize(Vector2f(width - posX, height));
}
void TAssessBar::serialize(std::ofstream& out) {
    TObject::serialize(out);

    Color color = first.getFillColor();
    out.write(reinterpret_cast<char*>(&color), sizeof(color));
    color = second.getFillColor();
    out.write(reinterpret_cast<char*>(&color), sizeof(color));

    out.write(reinterpret_cast<char*>(&value), sizeof(value));

}
void TAssessBar::deserialize(std::ifstream& in) {
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
void TAssessBar::jsonSerialize(json& j) {

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
void TAssessBar::jsonDeserialize(json& j) {
    
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