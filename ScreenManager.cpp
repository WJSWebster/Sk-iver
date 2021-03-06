//
// Created by William Webster on 15/11/2017.
//

#include "ScreenManager.h"

ScreenManager &ScreenManager::getInstance(){
    static ScreenManager instance;
    return instance;
}

//constructor
ScreenManager::ScreenManager() = default;

//destructor
ScreenManager::~ScreenManager() = default;

void ScreenManager::setText(string text){
    this->text = text;

    //return this; // chaining?
}

void ScreenManager::drawText(){
    cout << this->text << endl;
}