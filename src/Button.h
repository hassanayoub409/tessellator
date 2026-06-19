/************************************************
    Written by  : Hassan Ayoub                  *
    Date        : 23 December, 2024             *
    Purpose     : Declaring class Button        * 
************************************************/
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;

class Button
{
    private:
        RectangleShape shape;
        Text textInsideButton;
        Font fontForButton;

    public:
        // Constructor for Button
        Button(const Vector2f &, const Vector2f &, const string , const Font &, Color);
        // Method to check whether a button is Clicked
        bool isClicked(Vector2f) const;
        // method to draw the button
        void draw(RenderWindow &window) const;
};// end of class Button
#endif