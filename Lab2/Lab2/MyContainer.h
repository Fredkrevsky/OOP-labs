#pragma once
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "TObject.h"
#include "TButton.h"
#include "TChoice.h"
#include "TProgressBar.h"
#include "TAssessBar.h"
#include "TFactory.h"

class MyContainer
{
	std::vector<TObject*> vec;
	TAssessFactory* assessFactory;
	TProgressFactory* progressFactory;
	TChoiceFactory* choiceFactory;
	TButtonFactory* buttonFactory;
	TInputFactory* inputFactory;
	char getchar(Keyboard::Key key);

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
};

