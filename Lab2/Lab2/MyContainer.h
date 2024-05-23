#pragma once
#include <vector>
#include <fstream>
#include "TButton.h"
#include "TChoice.h"
#include "TProgressBar.h"
#include "TAssessBar.h"
#include "TInput.h"
#include "TFactory.h"
#include "gravity.h"
#include <Windows.h>
#include "Player.h"
#include "JsonToXmlAdapter.h"
#include "XmlToJson.h"

class MyContainer
{
	std::vector<TObject*> vec;
	HMODULE cipherDll;
	cipherType cipher, decipher;
	HMODULE convertDll;
	ConvertFunc convert;
	friend class ContainerIter;

public:
	MyContainer();
	~MyContainer();
	TObject* operator[](int index) {
		if (index >= 0 && index < vec.size()) {
			return vec[index];
		}
		return nullptr;
	}
	void add(TObject* obj);
	void clear();
	int size();
	void erase(int index);
	void serialize();
	void deserialize();
	void jsonSerialize();
	void jsonDeserialize();
};

class ContainerIter
{
	MyContainer& container;
	size_t index;
public:
	ContainerIter(MyContainer& cont) : container(cont), index(0) {}

	TObject* begin() {
		if (container.vec.size()) {
			index = 0;
			return container.vec[0];
		}
		return nullptr;
	}

	TObject* end() {
		if (container.vec.size()) {
			index = container.vec.size();
			return container.vec[container.vec.size() - 1];
		}
		return nullptr;
	}

	TObject* operator++(int) {
		if (index < container.vec.size()) {
			TObject* tmp = container.vec[index];
			index++;
			return tmp;
		}
		return nullptr;
	}

	TObject* operator--(int) {
		if (index < container.vec.size() && index >= 0) {
			TObject* tmp = container.vec[index];
			index--;
			return tmp;
		}
		return nullptr;
	}

	TObject* curr() {
		if (index >= 0 && index <= container.vec.size() - 1) {
			return container.vec[index];
		}
		return nullptr;
	}

	void setstart() {
		index = 0;
	}

	void setend() {
		index = container.vec.size() - 1;
	}

	bool operator!=(const ContainerIter& other) const {
		return index != other.index;
	}

	bool operator==(const ContainerIter& other) const {
		return index == other.index;
	}
};

class Field {
	const int step = 4;

	TAssessFactory* assessFactory;
	TProgressFactory* progressFactory;
	TChoiceFactory* choiceFactory;
	TButtonFactory* buttonFactory;
	TInputFactory* inputFactory;

	DragFunctionType drag;
	HMODULE gravDll;

	Player* player;
	MyContainer container;

	int xLeft = 0;
	const int width = 900;
	int count = 0;
	const int COUNT = 5;
	bool ground = true;

public:
	Field();
	~Field();
	void save();
	void load();
	void onLeftClick(Vector2f pos, int index);
	void onRightClick(Vector2f pos);
	void onLeftRelease();
	void onKeyPress(Keyboard::Key key);
	void draw(RenderWindow& win);
	void jump();
	void moveX(int step);
	void moveY();
};



