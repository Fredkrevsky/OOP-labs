#pragma once
#include "TBar.h"

class TAssessBar : public TBar {

    inline void setWidth();
    inline void setTextColor();
    inline void setTextPosition();
    inline void setString();

public:
    TAssessBar();
    void setPos(int tx, int ty) override;
    void setSize(int twidth, int theight) override;
    void setValue(float toSet);
    void serialize(std::ofstream& out) override;
    void deserialize(std::ifstream& in) override;
    void jsonSerialize(json& j) override;
    void jsonDeserialize(json& j) override;
};

