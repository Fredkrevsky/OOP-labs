#include <SFML/Graphics.hpp>
#include "MyContainer.h";
#define JSON

using namespace sf;

Font font;

int main()
{
    std::vector<Text*> vText;
    std::vector<TChoice*> vChoice;
    MyContainer vObjects;

    setlocale(LC_ALL, "Rus");
    RenderWindow win(VideoMode(1200, 800), "Lab2", Style::Close);
    win.setFramerateLimit(150);
    win.setVerticalSyncEnabled(true);
    
    font.loadFromFile("Fonts/arialmt.ttf");

    RectangleShape menu;
    menu.setPosition(0, 0);
    menu.setSize(Vector2f(300, 800));
    menu.setFillColor(Color(230, 230, 230));
    menu.setOutlineColor(Color::Black);
    menu.setOutlineThickness(7);

    RectangleShape drawspace;
    drawspace.setSize(Vector2f(900, 800));
    drawspace.setPosition(300, 0);
    drawspace.setFillColor(Color(230, 230, 230));

    Text menuT("Choose what to draw:", font, 24);
    menuT.setFillColor(Color::Black);
    menuT.setPosition(25, 20);

    Text drawspaceT("Draw here:", font, 24);
    drawspaceT.setFillColor(Color::Black);
    drawspaceT.setPosition(690, 20);

    Text choiceT("Choice", font, 24);
    choiceT.setFillColor(Color::Black);
    choiceT.setPosition(20, 100);

    Text buttonT("Button", font, 24);
    buttonT.setFillColor(Color::Black);
    buttonT.setPosition(20, 175);

    Text assessT("Assess bar", font, 24);
    assessT.setFillColor(Color::Black);
    assessT.setPosition(20, 250);

    Text progressT("Progress bar", font, 24);
    progressT.setFillColor(Color::Black);
    progressT.setPosition(20, 325);

    Text inputT("Input", font, 24);
    inputT.setFillColor(Color::Black);
    inputT.setPosition(20, 400);

    vText.push_back(&menuT);
    vText.push_back(&drawspaceT);
    vText.push_back(&choiceT);
    vText.push_back(&buttonT);
    vText.push_back(&assessT);
    vText.push_back(&progressT);
    vText.push_back(&inputT);

    TChoice choice1;
    choice1.setStatus(true);
    choice1.setThickness(3);
    choice1.setSize(20, 20);
    choice1.setPos(230, 105);

    TChoice choice2;
    choice2.setThickness(3);
    choice2.setSize(20, 20);
    choice2.setPos(230, 180);

    TChoice choice3;
    choice3.setThickness(3);
    choice3.setSize(20, 20);
    choice3.setPos(230, 255);

    TChoice choice4;
    choice4.setThickness(3);
    choice4.setSize(20, 20);
    choice4.setPos(230, 330);

    TChoice choice5;
    choice5.setThickness(3);
    choice5.setSize(20, 20);
    choice5.setPos(230, 405);


    vChoice.push_back(&choice1);
    vChoice.push_back(&choice2);
    vChoice.push_back(&choice3);
    vChoice.push_back(&choice4);
    vChoice.push_back(&choice5);

    win.clear();
    win.draw(drawspace);
    win.draw(menu);
    for (const auto& elem : vText) {
        win.draw(*elem);
    }
    for (const auto& elem : vChoice) {
        elem->draw(win);
    }

#ifdef JSON
    vObjects.jsonDeserialize("data.json");
#else
    vObjects.deserialize("data.bin");
#endif

    win.display();

    while (win.isOpen()) {
        Event event;
        while (win.pollEvent(event)) {
            if (event.type == Event::Closed) {
#ifdef JSON
                vObjects.jsonSerialize("data.json");
#else
                vObjects.serialize("data.bin");
#endif
                win.close();
            }
            else if (event.type == Event::MouseButtonPressed) {
                Vector2f mousePos = Vector2f(Mouse::getPosition(win));
                if (menu.getGlobalBounds().contains(mousePos)) {
                    int index = -1;
                    for (int i = 0; i < vChoice.size(); i++) {
                        if (vChoice[i]->isPressed(mousePos)) {
                            index = i;
                            break;
                        }
                    }
                    if (index != -1) {
                        vChoice[index]->onPress();
                        for (int i = 0; i < vChoice.size(); i++) {
                            if (i != index) {
                                vChoice[i]->setStatus(false);
                            }
                        }
                    }
                }
                else if (drawspace.getGlobalBounds().contains(mousePos)) {
                    if (event.mouseButton.button == Mouse::Left) {
                        int index = -1;
                        for (int i = 0; i < vChoice.size(); i++) {
                            if (vChoice[i]->getStatus()) {
                                index = i;
                                break;
                            }
                        }
                        vObjects.onLeftClick(mousePos, index);
                    }
                    else {
                        vObjects.onRightClick(mousePos);
                    }                 
                }
            }
            else if (event.type == Event::MouseButtonReleased) {
                if (event.mouseButton.button == Mouse::Left) {
                    vObjects.onLeftRelease();
                }
            }
            else if (event.type == Event::KeyPressed) {
                Keyboard::Key key = event.key.code;
                vObjects.onKeyPress(key);
            }
            win.clear();
            win.draw(drawspace);
            win.draw(menu);
            for (const auto& elem : vText) {
                win.draw(*elem);
            }
            for (const auto& elem : vChoice) {
                elem->draw(win);
            }
            for (int i = 0; i < vObjects.size(); i++) {
                vObjects[i]->draw(win);
            }
            win.display();
        }

    }

    return 0;
}

