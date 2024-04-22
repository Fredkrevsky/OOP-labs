#pragma once
#include "TClickable.h"

class TInput : public TClickable {
	bool isSelected;
	Text text;
	int limit;
	bool checkchar(char toCheck);
public: 
	TInput();
	void onPress() override;
	void onKeyPress(char pressed);
	void onRelease() override;
	void draw(RenderWindow& win) override;
	void setPos(int x0, int y0) override;
	void setSize(int w, int h) override;
	void setLimit(int lim);
};

