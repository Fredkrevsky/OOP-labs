#include "TBar.h"

TBar::TBar() : TObject() {
    value = 0.5;
    posX = width * value;

    first.setPosition(x, y);
    first.setSize(Vector2f(posX, height));
    first.setFillColor(Color::Green);

    second.setPosition(x + posX, y);
    second.setSize(Vector2f(height - posX, height));
    second.setFillColor(Color::White);

    text.setFont(font);
    text.setFillColor(Color::Black);
    text.setPosition(0, 0);
    text.setCharacterSize(FontSize);
    text.setString("");

}
void TBar::setFirstColor(Color color) {
    first.setFillColor(color);
}
void TBar::setSecondColor(Color color) {
    second.setFillColor(color);
}
void TBar::draw(RenderWindow& win) {
    TObject::draw(win);
    win.draw(first);
    win.draw(second);
    win.draw(text);
}
