#include "TInput.h"

TInput::TInput() : TClickable() {
	text.setPosition(3, 3);
	text.setCharacterSize(FontSize);
	text.setFont(font);
	text.setFillColor(Color::Black);
	setColor(Color::White);
	text.setString("");

	limit = 15;
	isSelected = false;
}
bool TInput::checkchar(char toCheck) {
	return (toCheck >= '0') && (toCheck <= '9') || (toCheck >= 'a') && (toCheck <= 'z') || (toCheck >= 'A') && (toCheck <= 'Z') || (toCheck == '_');
}
void TInput::onPress() {
	isSelected = true;
}
void TInput::onKeyPress(char inputChar) {

	if (isSelected) {
		std::string temp = text.getString();

		if (inputChar >= 0 && inputChar <= 25) {
			if (temp.size() < limit) {
				temp.push_back('A' + inputChar);
			}
		}
		else if (inputChar >= 26 && inputChar <= 35) {
			if (temp.size() < limit) {
				temp.push_back('0' + inputChar - 26);
			}
		}
		else if (inputChar == 59 && !temp.empty()) {
			temp.pop_back();
		}
		text.setString(temp);

	}
}
void TInput::onRelease() {
	isSelected = false;
}
void TInput::draw(RenderWindow& win) {
	TClickable::draw(win);
	win.draw(text);
}
void TInput::setPos(int x0, int y0) {
	TClickable::setPos(x0, y0);
	text.setPosition(x0 + 3, y0 + (height - FontSize) / 2 - 4);
}
void TInput::setSize(int w, int h) {
	TClickable::setSize(w, h);
}
void TInput::setLimit(int lim) {
	limit = lim;
}
