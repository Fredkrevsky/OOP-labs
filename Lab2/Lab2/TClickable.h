#pragma once
#include "TObject.h";

class TClickable : public TObject {
protected:
    Vector2f pressPos;
    virtual void onPress() = 0;
    virtual void onRelease() = 0;
public:
    bool isPressed(Vector2f& pos);
    TClickable();
};

