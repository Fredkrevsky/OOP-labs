#pragma once
#include "TClickable.h"

class TChoice : public TClickable {
    bool isSelected;
    RectangleShape in;
public:
    TChoice();
    void setPos(int tx, int ty) override;
    void setSize(int twidth, int theight);
    void onPress();
    void onRelease();
    void draw(RenderWindow& win) override;
    void setStatus(bool status);
    bool getStatus();
    void serialize(std::ofstream& out) override;
    void deserialize(std::ifstream& in) override;
    void jsonSerialize(json& j) override;
    void jsonDeserialize(json& j) override;
};

