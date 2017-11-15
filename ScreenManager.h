//
// Created by William Webster on 15/11/2017.
//

#ifndef SK_IVER_SCREENMANAGER_H
#define SK_IVER_SCREENMANAGER_H

#include <string>
#include <iostream>

using namespace std;

class ScreenManager
{
    public:
        ~ScreenManager();
        static ScreenManager &getInstance();

        void setText(string text);
        void drawText();

    protected:
    private: // means that this is a true singleton class
        ScreenManager();
        ScreenManager(ScreenManager const&);
        void operator= (ScreenManager const&);

        string text;
};

#endif //SK_IVER_SCREENMANAGER_H
