#include "MyContainer.h"
#define JSON

MyContainer::MyContainer() : cipher(nullptr), decipher(nullptr), convert(nullptr) {
	cipherDll = LoadLibrary(L"Dll2.dll");
	if (cipherDll == NULL) {
		return;
	}
	cipher = (cipherType)GetProcAddress(cipherDll, "cipher");
	decipher = (cipherType)GetProcAddress(cipherDll, "decipher");
	if (decipher == NULL || cipher == NULL) {
		FreeLibrary(cipherDll);
	}
	convertDll = LoadLibrary(L"JTX.dll");
	if (convertDll == NULL) {
		return;
	}
	convert = (ConvertFunc)GetProcAddress(convertDll, "convert");
	if (convert == NULL) {
		FreeLibrary(convertDll);
	}
}
MyContainer::~MyContainer() {
	for (auto elem : vec) {
		if (elem) {
			delete elem;
		}
	}
	if (cipherDll) {
		FreeLibrary(cipherDll);
	}
	if (convertDll) {
		FreeLibrary(convertDll);
	}
}
void MyContainer::add(TObject* obj) {
	vec.push_back(obj);
}
void MyContainer::clear() {
	for (int i = 0; i < vec.size(); ++i) {
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
void MyContainer::serialize() {
	std::string path = "data.bin";
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

	if (cipher) {
		cipher(path);
		std::remove(path.c_str());
	}
}
void MyContainer::deserialize() {
	std::string path = "data.bin";
	if (decipher) {
		decipher(path);
	}

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
	if (decipher) {
		std::remove(path.c_str());
	}
}
void MyContainer::jsonSerialize() {
	std::string path = "data.json";
	std::ofstream out(path, std::ios::binary);
	json mas = json::array();

	for (TObject* ptr : vec) {
		json j;
		if (TAssessBar* derivedPtr = dynamic_cast<TAssessBar*>(ptr)) {
			j["type"] = 0;
			derivedPtr->jsonSerialize(j);
		}
		else if (TProgressBar* derivedPtr = dynamic_cast<TProgressBar*>(ptr)) {
			j["type"] = 1;
			derivedPtr->jsonSerialize(j);
		}
		else if (TButton* derivedPtr = dynamic_cast<TButton*>(ptr)) {
			j["type"] = 2;
			derivedPtr->jsonSerialize(j);
		}
		else if (TChoice* derivedPtr = dynamic_cast<TChoice*>(ptr)) {
			j["type"] = 3;
			derivedPtr->jsonSerialize(j);
		}
		else if (TInput* derivedPtr = dynamic_cast<TInput*>(ptr)) {
			j["type"] = 4;
			derivedPtr->jsonSerialize(j);
		}
		mas.push_back(j);
	}
	out << mas.dump(4);
	out.close();

	if (convert) {
		convert(path, "data.xml");
	}

	if (cipher) {
		cipher("data.xml");
	}
}
void MyContainer::jsonDeserialize() {
	std::string path = "data.xml";
	if (decipher) {
		decipher(path);
	}
	XmlToJson::convert(path, "data.json");

	std::ifstream in("data.json", std::ios::binary);

	json mas;
	in >> mas;
	in.close();

	for (auto& j : mas) {
		int type = j["type"];
		TObject* temp = nullptr;

		switch (type) {
		case 0:
			temp = new TAssessBar();
			static_cast<TAssessBar*>(temp)->jsonDeserialize(j);
			break;
		case 1:
			temp = new TProgressBar();
			static_cast<TProgressBar*>(temp)->jsonDeserialize(j);
			break;
		case 2:
			temp = new TButton();
			static_cast<TButton*>(temp)->jsonDeserialize(j);
			break;
		case 3:
			temp = new TChoice();
			static_cast<TChoice*>(temp)->jsonDeserialize(j);
			break;
		case 4:
			temp = new TInput();
			static_cast<TInput*>(temp)->jsonDeserialize(j);
			break;
		}

		if (temp) {
			add(temp);
		}
	}
}

Field::Field() : player(nullptr), drag(nullptr) {
	player = Player::getPlayer();
	assessFactory = new TAssessFactory();
	progressFactory = new TProgressFactory();
	choiceFactory = new TChoiceFactory();
	buttonFactory = new TButtonFactory();
	inputFactory = new TInputFactory();

	gravDll = LoadLibrary(L"Dll1.dll");
	if (gravDll == NULL) {
		return;
	}
	drag = (DragFunctionType)GetProcAddress(gravDll, "drag");
	if (drag == NULL) {
		FreeLibrary(gravDll);
		return;
	}

}
Field::~Field() {
	delete assessFactory;
	delete progressFactory;
	delete buttonFactory;
	delete choiceFactory;
	if (gravDll) {
		FreeLibrary(gravDll);
	}
}
void Field::onLeftClick(Vector2f pos, int tindex) {
	TObject* index = nullptr;
	ContainerIter iter(container);
	iter.setend();
	while (auto obj = iter--) {
		if (obj->contains(pos)) {
			index = obj;
			break;
		}
	}
	if (index) {
		TObject* ptr = index;
		if (TButton* derivedPtr = dynamic_cast<TButton*>(ptr)) {
			derivedPtr->onPress();
		}
		else if (TChoice* derivedPtr = dynamic_cast<TChoice*>(ptr)) {
			derivedPtr->onPress();
		}
		else if (TInput* derivedPtr = dynamic_cast<TInput*>(ptr)) {
			derivedPtr->onPress();
			iter.setend();
			while (auto obj = iter--) {
				if (obj != index) {
					if (TInput* ptr2 = dynamic_cast<TInput*>(obj)) {
						ptr2->onRelease();
					}
				}
			}
		}
	}
	else {
		TObject* temp;
		switch (tindex) {
		case 0:
			temp = choiceFactory->create();
			temp->setPos(pos.x, pos.y);
			container.add(temp);
			break;
		case 1:
			temp = buttonFactory->create();
			temp->setPos(pos.x, pos.y);
			container.add(temp);
			break;
		case 2:
			temp = assessFactory->create();
			temp->setPos(pos.x, pos.y);
			container.add(temp);
			break;
		case 3:
			temp = progressFactory->create();
			temp->setPos(pos.x, pos.y);
			container.add(temp);
			break;
	    case 4:
			temp = inputFactory->create();
			temp->setPos(pos.x, pos.y);
			container.add(temp);
			break;
		}
	}
}
void Field::onRightClick(Vector2f pos) {
	int index = -1;
	for (int i = container.size() - 1; i >= 0; i--) {
		if (container[i]->contains(pos)) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		container.erase(index);
	}
}
void Field::onLeftRelease() {
	ContainerIter iter(container);
	while (auto it = iter++) {
		if (TButton* derivedPtr = dynamic_cast<TButton*>(it)) {
			derivedPtr->onRelease();
		}
	}
}
void Field::onKeyPress(Keyboard::Key key) {
	if (key == Keyboard::Up) {
		jump();
	}
	else {
		ContainerIter iter(container);
		while (auto it = iter++) {
			if (TInput* derivedPtr = dynamic_cast<TInput*>(it)) {
				derivedPtr->onKeyPress(key);
			}
		}
	}
}
void Field::draw(RenderWindow& win) {
	int x, y;
	int w, h;
	ContainerIter iter(container);
	while (auto it = iter++) {
		it->getPos(x, y);
		it->getSize(w, h);
		if (x + w > 300 && x < 1200) {
			it->draw(win);
		}
	}
	player->draw(win);
}
void Field::jump() {
	if (drag && ground) {
		ground = false;
		player->setV(-14);
	}
}
void Field::moveX(int step) {
	ground = false;
	int x, y;
	y = player->getY();
	x = 600;

	int tx, ty, w, h;
	bool flag = false;
	ContainerIter iter(container);
	while (auto elem = iter++) {
		elem->getPos(tx, ty);
		elem->getSize(w, h);
		if ((x + 85 / 2 - step >= tx) && (x - 85 / 2 <= tx + w + step) && (ty <= y + 102 / 2) && (ty + h >= y - 102 / 2)) {
			flag = true;
			break;
		}
	}
	if (!flag) {
		iter.setstart();
		while (auto elem = iter++) {
			elem->getPos(x, y);
			elem->setPos(x + step, y);
		}
	}

	if (player->inverted ^ (step > 0)) {
		player->invert();
	}
	if (count == 0) {
		player->setNext();
	}
	count = (count + 1) % COUNT;


}
void Field::moveY() {
	int py = player->getY();
	int px = 600 - 85 / 2;

	float vy;
	int tx, ty;
	int w, h;
	player->getV(vy);

	py += vy;
	ContainerIter iter(container);
	while (auto elem = iter++) {
		elem->getPos(tx, ty);
		elem->getSize(w, h);
		if ((px <= tx + w - 5) && (px + 85 >= tx + 5) && (py - 102 / 2 <= ty + h) && (py + 102 / 2 >= ty - 2)) {
			py -= vy;
			if (py > ty) {
				py = ty + h + 102 / 2 + 1;
			}
			else {
				py = ty - 102 / 2 - 1;
				ground = true;
			}
			vy = 0;
			player->setV(0);
			player->move(py);
			break;
		}
	}
	
	if (py >= 600 && vy >= 0) {
		player->setV(0);
		player->move(600);
		ground = true;
	}
	else if (!ground) {
		player->move(py);
		player->setV(vy + 0.4);
	}
}
void Field::save() {
#ifdef JSON
	container.jsonSerialize();

#else
	container.serialize();
#endif
}
void Field::load() {
	container.clear();
#ifdef JSON
	container.jsonDeserialize();
#else
	container.deserialize();
#endif
}