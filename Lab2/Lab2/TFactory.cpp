#include "TFactory.h"

TFactory::~TFactory() {};

TObject* TAssessFactory::create() {
    TAssessBar* temp = new TAssessBar();
    temp->setSize(300, 50);
    temp->setFirstColor(Color::White);
    temp->setSecondColor(Color::Black);
    temp->setThickness(5);
    temp->setValue(-2.8);
    return temp;
}

TObject* TProgressFactory::create() {
    TProgressBar* temp = new TProgressBar();
    temp->setSize(300, 50);
    temp->setFirstColor(Color::Green);
    temp->setSecondColor(Color::White);
    temp->setThickness(5);
    temp->setValue(0.7);
    return temp;
}

TObject* TChoiceFactory::create() {
    TChoice* temp = new TChoice();
    temp->setSize(30, 30);
    temp->setThickness(5);
    return temp;
}

TObject* TButtonFactory::create() {
    TButton* temp = new TButton();
    temp->setSize(200, 90);
    temp->setColor(Color::Green);
    temp->setThickness(5);
    temp->setText("Click me");
    return temp;
}

TObject* TInputFactory::create() {
    TInput* temp = new TInput();
    temp->setSize(300, 40);
    temp->setThickness(5);
    temp->setLimit(18);
    return temp;
}