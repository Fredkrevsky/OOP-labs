#pragma once
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "TButton.h"
#include "TChoice.h"
#include "TProgressBar.h"
#include "TAssessBar.h"
#include "TInput.h"
#include "TFactory.h"
#include "gravity.h"
#include <Windows.h>

class MyContainer
{
	std::vector<TObject*> vec;
	HMODULE hDll;
	TAssessFactory* assessFactory;
	TProgressFactory* progressFactory;
	TChoiceFactory* choiceFactory;
	TButtonFactory* buttonFactory;
	TInputFactory* inputFactory;
	DragFunctionType drag;

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
	void serialize(std::string path);
	void deserialize(std::string path);
	void jsonSerialize(std::string path);
	void jsonDeserialize(std::string path);
	void onLeftClick(Vector2f pos, int index);
	void onRightClick(Vector2f pos);
	void onLeftRelease();
	void onKeyPress(Keyboard::Key key);
	void drawAll(RenderWindow& win);
	void dragAll(int posx, int posy, float gravity);
};

