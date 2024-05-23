#pragma once
#include "TObject.h";

class TClickable : public TObject {
protected:
    Vector2f pressPos;
public:
    virtual void onPress() = 0;
    virtual void onRelease() = 0;
    bool isPressed(Vector2f& pos);
    TClickable();
};

