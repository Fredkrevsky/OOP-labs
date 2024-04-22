#include "TClickable.h"

bool TClickable::isPressed(Vector2f& pos) {
    pressPos = pos;
    return ((pos.x - x) >= 0) && (pos.x - x <= width) && ((pos.y - y) >= 0) && (pos.y - y <= height);
}
TClickable::TClickable() : TObject() {}

