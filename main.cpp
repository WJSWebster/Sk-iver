//
// Created by William Webster on 15/11/2017.
//
#include <iostream>
#include "ScreenManager.h"

using namespace std;

int main(){
    //cout << "Hello, World!" << endl;

    ScreenManager::getInstance().setText("Testing");
    ScreenManager::getInstance().drawText();

    cin.get(); // waits for input so not to immediately return & end
    return 0;
}