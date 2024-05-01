#pragma once
#include "TClickable.h"

class TInput : public TClickable {
protected:
	bool isSelected;
	Text text;
	char limit;
	bool checkchar(char toCheck);

public:
	TInput();
	void onPress();
	void onKeyPress(char inputChar);
	void onRelease();
	void draw(RenderWindow& win) override;
	void setPos(int x0, int y0) override;
	void setSize(int w, int h) override;
	void setText(std::string toSet);
	void serialize(std::ofstream& out) override;
	void deserialize(std::ifstream& in);
	void jsonSerialize(json& j) override;
	void jsonDeserialize(json& j) override;
	void setLimit(int lim);
};




