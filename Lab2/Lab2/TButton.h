#pragma once
#include "TClickable.h"


class TButton : public TClickable {
    Text text;
    int len;
    void normText();
public:
    TButton();
    void setText(std::string toSet);
    void setPos(int tx, int ty) override;
    void setSize(int twidth, int theight);
    void onPress();
    void onRelease();
    void serialize(std::ofstream& out) override;
    void deserialize(std::ifstream& in) override;
    void jsonSerialize(json& j) override;
    void jsonDeserialize(json& j) override;
    void draw(RenderWindow& win) override;
};
