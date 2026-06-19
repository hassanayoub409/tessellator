/************************************************
    Written by  : Hassan Ayoub                  *
    Date        : 22 December, 2024             *
    Purpose     : Declaring class Menu          * 
************************************************/
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "FrameShape.h"
#include "Button.h"
#include <vector>
using namespace std;
using namespace sf;

class Menu {
    private:
        RenderWindow &window;
        Font font;
        vector<FrameShape> items;
        Text firstLine;
        const float frameSpacing = 100;
        const float topMargin = 50;
        const Vector2f frameSize = {100, 100};
        Button exitButton;
    public:
        // Constructor of Menu
        Menu(RenderWindow &, const Font &, const Font &, Button &);
        // Methood to add shape to vector items
        void addShape(const string&, const Texture&);
        // Method to draw to whole menu
        void draw();
        // Method to handle event (clicking the frame)
        void handleEvent(const Event &);
};// end of class Menu

#endif