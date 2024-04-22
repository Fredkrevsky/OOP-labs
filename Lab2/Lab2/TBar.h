#pragma once
#include "TObject.h"

class TBar : public TObject {

protected:
    RectangleShape first;
    float value;
    int posX;
    RectangleShape second;
    Text text;

    virtual void setValue(float toSet) = 0;
    TBar();

public:
    void setFirstColor(Color color);
    void setSecondColor(Color color);
    void draw(RenderWindow& win);
};

