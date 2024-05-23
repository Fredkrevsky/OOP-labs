#pragma once
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <vector>
#include <fstream>

using namespace sf;
using json = nlohmann::json;

const int FontSize = 24;
extern Font font;

class TObject
{
protected:
    RectangleShape background;
    int x = 0, y = 0, width = 0, height = 0;

    TObject();

public:
    virtual void jsonSerialize(json& j);
    virtual void jsonDeserialize(json& j);
    virtual ~TObject() {}
    virtual void draw(RenderWindow& win);
    bool contains(Vector2f mousePos);
    virtual void setPos(int tx, int ty);
    virtual void setSize(int twidth, int theight);
    void getPos(int& x, int& y);
    void getSize(int& width, int& height);
    void setColor(Color color);
    void setThickness(int thickness);
    virtual void serialize(std::ofstream& out);
    virtual void deserialize(std::ifstream& in);
};



