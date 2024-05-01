#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

using namespace sf;
using json = nlohmann::json;

const int FontSize = 24;
extern Font font;

class TObject
{
protected:
    RectangleShape background;
    int x = 0, y = 0, width = 0, height = 0;
    float vx = 0, vy = 0;

    TObject();
    virtual void jsonSerialize(json& j);
    virtual void jsonDeserialize(json& j);
public:
    virtual ~TObject() {}
    virtual void draw(RenderWindow& win);
    bool contains(Vector2f mousePos);
    virtual void setPos(int tx, int ty);
    virtual void setSize(int twidth, int theight);
    void setV(int tvx, int tvy);
    void getPos(int& x, int& y);
    void getSize(int& width, int& height);
    void getV(int& tvx, int& tvy);
    void setColor(Color color);
    void setThickness(int thickness);
    virtual void serialize(std::ofstream& out);
    virtual void deserialize(std::ifstream& in);
};



