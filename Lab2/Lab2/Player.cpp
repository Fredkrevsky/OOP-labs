#include "Player.h"

Player* Player::playerInstance = nullptr;

Player::Player(){
	texture.create(width, height);
	string path = "cut_images/image_part_";
	for (int i = 0; i < 30; ++i) {
		texture.loadFromFile(path + std::to_string(i + 1) + ".png");
		vTexture.push_back(texture);
	}
	sprite.setPosition(x, y);
	sprite.setTextureRect(IntRect(0, 0, width, height));
	sprite.setTexture(vTexture[0]);
	sprite.setOrigin(width / 2, height / 2);
}
void Player::setNext() {
	curr = (curr + 1) % 30;
	sprite.setTexture(vTexture[curr]);
}
void Player::draw(RenderWindow& win) {
	win.draw(sprite);
}
void Player::invert() {
	inverted = !inverted;
	sprite.setScale(-sprite.getScale().x, sprite.getScale().y);
}
void Player::move(int ty) {
	y = ty;
	sprite.setPosition(x, y);
}
int Player::getY() {
	return y;
}
void Player::setV(float ty) {
	vy = ty;
}
void Player::getV(float& tvy) {
	tvy = vy;
}
Player* Player::getPlayer() {
	if (!playerInstance) {
		playerInstance = new Player();
	}
	return playerInstance;
}