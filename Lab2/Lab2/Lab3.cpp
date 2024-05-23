#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "gravity.h"
#include "MyContainer.h"

using namespace sf;
const int fps = 150;
const float gravity = 1;

Font font;
RectangleShape menu;
RectangleShape drawspace;
std::vector<Text> vText;
std::vector<TChoice> vChoice;
Field field;

void draw(RenderWindow& win, TButton& ser, TButton& deser) {
    win.clear();
    win.draw(drawspace);
    field.draw(win);
    win.draw(menu);
    for (const auto& elem : vText) {
        win.draw(elem);
    }
    for (auto& elem : vChoice) {
        elem.draw(win);
    }
    ser.draw(win);
    deser.draw(win);
    win.display();
}

int main()
{
    font.loadFromFile("Fonts/arialmt.ttf");
    RenderWindow win(VideoMode(1200, 800), "Lab2", Style::Close);
    win.setFramerateLimit(fps);
    win.setVerticalSyncEnabled(true);

    menu.setPosition(0, 0);
    menu.setSize(Vector2f(300, 800));
    menu.setFillColor(Color(230, 230, 230));
    menu.setOutlineColor(Color::Black);
    menu.setOutlineThickness(7);

    drawspace.setSize(Vector2f(900, 800));
    drawspace.setPosition(300, 0);
    drawspace.setFillColor(Color(230, 230, 230));

    Text text("Choose what to draw:", font, 24);
    text.setFillColor(Color::Black);
    text.setPosition(25, 20);
    vText.push_back(text);
    text.setString("Choice");
    text.setPosition(20, 100);
    vText.push_back(text);
    text.setString("Button");
    text.setPosition(20, 175);
    vText.push_back(text);
    text.setString("Assess bar");
    text.setPosition(20, 250);
    vText.push_back(text);
    text.setString("Progress bar");
    text.setPosition(20, 325);
    vText.push_back(text);
    /*
    text.setString("Input");
    text.setPosition(20, 400);
    vText.push_back(text);
    */
    TChoice choice;
    choice.setStatus(true);
    choice.setThickness(3);
    choice.setSize(20, 20);
    choice.setPos(230, 105);
    vChoice.push_back(choice);
    choice.setStatus(false);
    choice.setPos(230, 180);
    vChoice.push_back(choice);
    choice.setPos(230, 255);
    vChoice.push_back(choice);
    choice.setPos(230, 330);
    vChoice.push_back(choice);
    /*
    choice.setPos(230, 405);
    vChoice.push_back(choice);
    */

    TButton ser;
    ser.setSize(150, 50);
    ser.setPos(50, 600);
    ser.setColor(Color::Green);
    ser.setText("Save");
    ser.setThickness(3);

    TButton deser;
    deser.setSize(150, 50);
    deser.setPos(50, 700);
    deser.setColor(Color::Green);
    deser.setText("Load");
    deser.setThickness(3);

    draw(win, ser, deser);

    bool rPress = false, lPress = false;

    while (win.isOpen()) {

        lPress = Keyboard::isKeyPressed(Keyboard::Left);
        rPress = Keyboard::isKeyPressed(Keyboard::Right);

        if (lPress ^ rPress) {
            if (lPress) {
                field.moveX(4);
            }
            else {
                field.moveX(-4);
            }
        }
        field.moveY();

        Vector2i pos = Mouse::getPosition(win);
        
        draw(win, ser, deser);

        Event event;
        while (win.pollEvent(event)) {

            

            if (event.type == Event::Closed) {
                win.close();
            }
            else if (event.type == Event::MouseButtonPressed) {
                Vector2f mousePos = Vector2f(Mouse::getPosition(win));
                if (menu.getGlobalBounds().contains(mousePos)) {
                    int index = -1;
                    for (int i = 0; i < vChoice.size(); i++) {
                        if (vChoice[i].isPressed(mousePos)) {
                            index = i;
                            break;
                        }
                    }
                    if (index != -1) {
                        vChoice[index].onPress();
                        for (int i = 0; i < vChoice.size(); i++) {
                            if (i != index) {
                                vChoice[i].setStatus(false);
                            }
                        }
                    }
                    else if (ser.isPressed(mousePos)) {
                        ser.onPress();
                        field.save();
                    }
                    else if (deser.isPressed(mousePos)) {
                        deser.onPress();
                        field.load();
                        draw(win, ser, deser);
                    }
                }
                else if (drawspace.getGlobalBounds().contains(mousePos)) {
                    if (event.mouseButton.button == Mouse::Left) {
                        int index = -1;
                        for (int i = 0; i < vChoice.size(); i++) {
                            if (vChoice[i].getStatus()) {
                                index = i;
                                break;
                            }
                        }
                        field.onLeftClick(mousePos, index);
                    }
                    else {
                        field.onRightClick(mousePos);
                    }                 
                }
            }
            else if (event.type == Event::MouseButtonReleased) {
                if (event.mouseButton.button == Mouse::Left) {
                    field.onLeftRelease();
                    ser.onRelease();
                    deser.onRelease();
                }
            }
            else if (event.type == Event::KeyPressed) {
                Keyboard::Key key = event.key.code;
                field.onKeyPress(key);
            }
        }

    }
    return 0;
}

