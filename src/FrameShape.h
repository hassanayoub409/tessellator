/************************************************
    Written by  : Hassan Ayoub                  *
    Date        : 22 December, 2024             *
    Purpose     : Declaring class FrameShape    * 
************************************************/
#ifndef FRAMESHAPE_H
#define FRAMESHAPE_H

#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;

class FrameShape 
{
    private:
        RectangleShape frame;
        Sprite image;
        Text text;
    public:
        // Parametrized Constructor of FrameShape
        FrameShape(const string&, const Texture&, Vector2f, Vector2f, const Font&);
        // Method to draw a frame on window
        void draw(RenderWindow&) const;
        // Method to check if mouse clicked a certain frame
        bool isClicked(Vector2f) const;
        // Method to return the global bounds of frame
        FloatRect getBounds() const { return frame.getGlobalBounds(); }
};// end of class FrameShape

#endif