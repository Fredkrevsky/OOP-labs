#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace sf;
using json = nlohmann::json;

const int FontSize = 24;
extern Font font;
extern Font font;

class TObject
{
protected:
    RectangleShape background;
    int x, y, width, height;
    TObject();
    void jsonSerialize(json& j);
    void jsonDeserialize(json& j);
public:
    virtual ~TObject() {}
    bool contains(Vector2f mousePos);
    virtual void setPos(int tx, int ty);
    virtual void setSize(int twidth, int theight);
    void setColor(Color color);
    void setThickness(int thickness);
    virtual void draw(RenderWindow& win);
    virtual void serialize(std::ofstream& out);
    virtual void deserialize(std::ifstream& in);
};

