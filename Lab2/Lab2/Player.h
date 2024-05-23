#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using std::vector;
using std::string;

class Player
{

	const int x = 600; 
	int y = 600;
	const int width = 85;
	const int height = 102;

	float vy = 0;

	Sprite sprite;
	vector<Texture> vTexture;
	Texture texture;
	int curr = 0;
	Player();

public:
	static Player* playerInstance;
	bool inverted = false;
	static Player* getPlayer();
	void setNext();
	void invert();
	void draw(RenderWindow& win);
	void move(int ty);
	int getY();
	void setV(float ty);
	void getV(float& tvy);
};


