#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
using namespace sf;

class TChoice: public TClickable {
    bool isSelected;
    RectangleShape in;
public:
    TChoice() : TClickable() {
        isSelected = false;
        in.setFillColor(Color(30, 30, 30));
        in.setPosition(x + width / 4, y + height / 4);
        in.setSize(Vector2f(width / 2, height / 2));
    }
    void setPos(int tx, int ty) override {
        TObject::setPos(tx, ty);
        in.setPosition(tx + width / 4, ty + height / 4);
    }
    void setSize(int twidth, int theight) {
        TObject::setSize(twidth, theight);
        in.setPosition(x + twidth / 4, y + theight / 4);
        in.setSize(Vector2f(twidth / 2, theight / 2));
    }
    void onPress() {
        isSelected = !isSelected;
    }
    void onRelease() { }
    void draw(RenderWindow& win) {
        TObject::draw(win);
        if (isSelected) {
            win.draw(in);
        }
    }
    void setStatus(bool status) {
        isSelected = status;
    }
    bool getStatus() {
        return isSelected;
    }
};

class TButton: public TClickable {
    Text text;
    int len;
    void normText() {
        text.setPosition(x + (width - len * FontSize / 2) / 2, y + (height - FontSize) / 2);
    }
public:
    TButton() : TClickable() {
        len = 0;
        text.setPosition(0, 0);
        text.setFont(font);
        text.setCharacterSize(FontSize);
        text.setFillColor(Color::Black);
    }
    void setText(std::string toSet) {
        text.setString(toSet);
        len = toSet.size();
        normText();
    }
    void setPos(int tx, int ty) override {
        TObject::setPos(tx, ty);
        normText();
    }
    void setSize(int twidth, int theight) {
        TObject::setSize(twidth, theight);
        normText();
    }
    void onPress() { 
        background.setFillColor(Color(50, 170, 50));
    }
    void onRelease() {
        background.setFillColor(Color::Green);
    }
    void draw(RenderWindow& win) {
        TObject::draw(win);
        win.draw(text);
    }
};

class TAssessBar: public TBar {

    inline void setWidth() {
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
    inline void setTextColor() {
        if (value > 0) {
            text.setFillColor(second.getFillColor());
        }
        else {
            text.setFillColor(first.getFillColor());
        }
    }
    inline void setTextPosition() {
        if (value < 0) {
            text.setPosition(x + width - 40, y + (height - FontSize) / 2 - 3);
        }
        else {
            text.setPosition(x + 4, y + (height - FontSize) / 2 - 3);
        }
    }
    inline void setString() {
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

public:
    TAssessBar() : TBar() { }
    void setPos(int tx, int ty) override {
        TObject::setPos(tx, ty);

        first.setPosition(tx, ty);
        second.setPosition(tx + posX, ty);

        setTextPosition();
    }
    void setSize(int twidth, int theight) override {
        TObject::setSize(twidth, theight);

        first.setSize(Vector2f(twidth, theight));

        second.setSize(Vector2f(width - posX, height));
        second.setPosition(x + posX, y);

        setTextPosition();
    }
    void setValue(float toSet) {
        value = toSet;
        setWidth();
        setString();
        setTextColor();
        setTextPosition();
        first.setSize(Vector2f(posX, height));
        second.setPosition(x + posX, y);
        second.setSize(Vector2f(width - posX, height));
    }
    
};

class TProgressBar: public TBar {
    inline void setWidth() {
        posX = width * value;
    }
    inline void setTextPosition() {
        text.setPosition(x + 4, y + (height - FontSize) / 2 - 3);
    }
    inline void setString() {
        int toSet = std::round(abs(value) * 100);
        std::string result = std::to_string(toSet);
        result.push_back('%');
        text.setString(result);
    }
   
public:
    TProgressBar() : TBar() { }
    void setPos(int tx, int ty) override {
        TObject::setPos(tx, ty);

        first.setPosition(tx, ty);
        second.setPosition(tx + posX, ty);

        setTextPosition();
    }
    void setSize(int twidth, int theight) override {
        TObject::setSize(twidth, theight);

        first.setSize(Vector2f(twidth, theight));

        second.setSize(Vector2f(width - posX, height));
        second.setPosition(x + posX, y);

        setTextPosition();
    }
    void setValue(float toSet) {
        value = toSet;
        setWidth();
        setString();
        setTextPosition();
        first.setSize(Vector2f(posX, height));
        second.setPosition(x + posX, y);
        second.setSize(Vector2f(width - posX, height));
    }
};





