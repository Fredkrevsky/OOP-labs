#include "MyContainer.h"

MyContainer::MyContainer() {
	assessFactory = new TAssessFactory();
	progressFactory = new TProgressFactory();
	choiceFactory = new TChoiceFactory();
	buttonFactory = new TButtonFactory();
	inputFactory = new TInputFactory();
	
	hDll = LoadLibrary(L"Dll1.dll");
	if (hDll == NULL) {
		return;
	}
	drag = (DragFunctionType)GetProcAddress(hDll, "drag");
	if (drag == NULL) {
		FreeLibrary(hDll);
		return;
	}
}
MyContainer::~MyContainer() {
	delete assessFactory;
	delete progressFactory;
	delete buttonFactory;
	delete choiceFactory;
	if (hDll) {
		FreeLibrary(hDll);
	}
}
void MyContainer::add(TObject* obj) {
	vec.push_back(obj);
}
void MyContainer::clear() {
	for (int i = 0; i < vec.size(); i++) {
		delete vec[i];
	}
	vec.clear();
}
int MyContainer::size() {
	return vec.size();
}
void MyContainer::erase(int index) {
	delete vec[index];
	vec.erase(vec.begin() + index);
}
void MyContainer::serialize(std::string path) {

	std::ofstream out(path, std::ios::binary);
	char type;

	for (TObject* ptr : vec) {
		if (TAssessBar* derivedPtr = dynamic_cast<TAssessBar*>(ptr)) {
			type = 0;
			out.write(&type, 1);
			derivedPtr->serialize(out);
		}
		else if (TProgressBar* derivedPtr = dynamic_cast<TProgressBar*>(ptr)) {
			type = 1;
			out.write(&type, 1);
			derivedPtr->serialize(out);
		}
		else if (TButton* derivedPtr = dynamic_cast<TButton*>(ptr)) {
			type = 2;
			out.write(&type, 1);
			derivedPtr->serialize(out);
		}
		else if (TChoice* derivedPtr = dynamic_cast<TChoice*>(ptr)) {
			type = 3;
			out.write(&type, 1);
			derivedPtr->serialize(out);
		}
		else if (TInput* derivedPtr = dynamic_cast<TInput*>(ptr)) {
			type = 4;
			out.write(&type, 1);
			derivedPtr->serialize(out);
		}
	}

	out.close();
}
void MyContainer::deserialize(std::string path) {

	std::ifstream in(path, std::ios::binary);

	char type;
	TObject* temp;

	while (in.peek() != EOF) {
		in.read(&type, 1);
		switch (type) {
		case 0: 
			temp = new TAssessBar();
			static_cast<TAssessBar*>(temp)->deserialize(in);
			add(temp);
			break;
		case 1:
			temp = new TProgressBar();
			static_cast<TProgressBar*>(temp)->deserialize(in);
			add(temp);
			break;
		case 2:
			temp = new TButton();
			static_cast<TButton*>(temp)->deserialize(in);
			add(temp);
			break;
		case 3:
			temp = new TChoice();
			static_cast<TChoice*>(temp)->deserialize(in);
			add(temp);
			break;
		case 4:
			temp = new TInput();
			static_cast<TInput*>(temp)->deserialize(in);
			add(temp);
			break;
		}
	}

	in.close();
}
void MyContainer::jsonSerialize(std::string path) {
	
	std::ofstream out(path, std::ios::binary);

	for (TObject* ptr : vec) {

		if (TAssessBar* derivedPtr = dynamic_cast<TAssessBar*>(ptr)) {
			json j;
			j["type"] = 0;
			derivedPtr->jsonSerialize(j);
			out << j.dump(4);
		}
		else if (TProgressBar* derivedPtr = dynamic_cast<TProgressBar*>(ptr)) {
			json j;
			j["type"] = 1;
			derivedPtr->jsonSerialize(j);
			out << j.dump(4);
		}
		else if (TButton* derivedPtr = dynamic_cast<TButton*>(ptr)) {
			json j;
			j["type"] = 2;
			derivedPtr->jsonSerialize(j);
			out << j.dump(4);
		}
		else if (TChoice* derivedPtr = dynamic_cast<TChoice*>(ptr)) {
			json j;
			j["type"] = 3;
			derivedPtr->jsonSerialize(j);
			out << j.dump(4);
		}
		else if (TInput* derivedPtr = dynamic_cast<TInput*>(ptr)) {
			json j;
			j["type"] = 4;
			derivedPtr->jsonSerialize(j);
			out << j.dump(4);
		}
	}

	out.close();

}
void MyContainer::jsonDeserialize(std::string path) {
	
	std::ifstream in(path, std::ios::binary);

	char type;
	TObject* temp;

	while (in.peek() != EOF) {
		
		json j;
		in >> j;
		int type = j["type"];

		switch (type) {
		case 0:
			temp = new TAssessBar();
			static_cast<TAssessBar*>(temp)->jsonDeserialize(j);
			add(temp);
			break;
		case 1:
			temp = new TProgressBar();
			static_cast<TProgressBar*>(temp)->jsonDeserialize(j);
			add(temp);
			break;
		case 2:
			temp = new TButton();
			static_cast<TButton*>(temp)->jsonDeserialize(j);
			add(temp);
			break;
		case 3:
			temp = new TChoice();
			static_cast<TChoice*>(temp)->jsonDeserialize(j);
			add(temp);
			break;
		case 4:
		    temp = new TInput();
			static_cast<TInput*>(temp)->jsonDeserialize(j);
			add(temp);
			break;
		}
	}

	in.close();
}
void MyContainer::onLeftClick(Vector2f pos, int tindex) {
	TObject* temp;
	int index = -1;
	for (int i = vec.size() - 1; i >= 0; i--) {
		if (vec[i]->contains(pos)) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		TObject* ptr = vec[index];
		if (TButton* derivedPtr = dynamic_cast<TButton*>(ptr)) {
			derivedPtr->onPress();
		}
		else if (TChoice* derivedPtr = dynamic_cast<TChoice*>(ptr)) {
			derivedPtr->onPress();
		}
		else if (TInput* derivedPtr = dynamic_cast<TInput*>(ptr)) {
			derivedPtr->onPress();
			for (int i = 0; i < vec.size(); ++i) {
				if (i != index) {
					if (TInput* ptr2 = dynamic_cast<TInput*>(vec[i])) {
						ptr2->onRelease();
					}
				}
			}
		}
	}
	else {
		switch (tindex) {
		case 0:
			temp = choiceFactory->create();
			temp->setPos(pos.x, pos.y);
			add(temp);
			break;
		case 1:
			temp = buttonFactory->create();
			temp->setPos(pos.x, pos.y);
			add(temp);
			break;
		case 2:
			temp = assessFactory->create();
			temp->setPos(pos.x, pos.y);
			add(temp);
			break;
		case 3:
			temp = progressFactory->create();
			temp->setPos(pos.x, pos.y);
			add(temp);
			break;
	    case 4:
			temp = inputFactory->create();
			temp->setPos(pos.x, pos.y);
			add(temp);
			break;
		}
	}
}
void MyContainer::onRightClick(Vector2f pos) {
	int index = -1;
	for (int i = vec.size() - 1; i >= 0; i--) {
		if (vec[i]->contains(pos)) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		erase(index);
	}
}
void MyContainer::onLeftRelease() {
	for (TObject* ptr : vec) {
		if (TButton* derivedPtr = dynamic_cast<TButton*>(ptr)) {
			derivedPtr->onRelease();
		}
	}
}

void MyContainer::onKeyPress(Keyboard::Key key) {
	for (TObject* ptr : vec) {
		if (TInput* derivedPtr = dynamic_cast<TInput*>(ptr)) {
			derivedPtr->onKeyPress(key);
		}
	}
}
void MyContainer::drawAll(RenderWindow& win) {
	for (const auto& elem : vec) {
		elem->draw(win);
	}
}
void MyContainer::dragAll(int posx, int posy, float gravity) {
	if (drag) {
		for (const auto& elem : vec) {
			coord data = {};
			int t1, t2;
			elem->getPos(t1, t2);
			data[0] = t1;
			data[1] = t2;

			elem->getSize(t1, t2);
			data[2] = t1;
			data[3] = t2;

			data[4] = posx;
			data[5] = posy;
			data[6] = 300;
			data[7] = 50;
			data[8] = 1200;
			data[9] = 700;

			elem->getV(t1, t2);
			data[10] = t1;
			data[11] = t2;

			drag(data, gravity);
			t1 = data[0];
			t2 = data[1];
			elem->setPos(t1, t2);
			t1 = data[10];
			t2 = data[11];
			elem->setV(t1, t2);
		}
	}
}
