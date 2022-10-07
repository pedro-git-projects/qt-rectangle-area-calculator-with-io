#include "app.h"

#include <QTextStream>
#include <iostream>
#include <stdexcept>
#include "rectangle.h"

App::App() {
    this->isRunning = true;
}

void App::printPrompt() {
    QTextStream cout(stdout);
    cout << "-> Enter '-1' to exit" << Qt::endl;
    cout << "-> Please enter the rectangle width and length separated by space" << Qt::endl;
}

bool App::isNeagtive (float w, float l) {
    bool result = (l < 0 || w < 0) ? true : false;
    return result;
}

void App::readFloats() {
    QTextStream cin(stdin);
    this->printPrompt();
    cin >> tempW >> tempL;

    if(!(this->isNeagtive(tempW, tempL))) {
        this->w = tempW;
        this->l = tempL;
    } else {
        this->isRunning = false;
    }

    if(cin.status() != QTextStream::Ok) {
        cin.resetStatus();
        throw std::runtime_error("-> Please make sure you enter a float");
    }
}

Rectangle* App::createRect() {
    try {
        this->readFloats();
        Rectangle* r = new Rectangle{this->w, this->l};
        return r;
    }

    catch(const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        return nullptr;
    }
}

void App::addToList() {
    Rectangle* r = this->createRect();
    if(r == nullptr) throw std::runtime_error("");
    this->list.addToList(r);
}

void App::loop() {
    while(this->isRunning) {
        try {
            this->addToList();
        }
        catch(std::runtime_error& err) {
            std::cerr << err.what() << std::endl;
        }
    }
}
