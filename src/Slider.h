/************************************************
    Written by  : Hassan Ayoub                  *
    Date        : 23 December, 2024             *
    Purpose     : Declaring class Slider        * 
************************************************/
#ifndef SLIDER_H
#define SLIDER_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Slider 
{
    private:
        RectangleShape track;  
        RectangleShape thumb;  
        float width, height; 
        float minValue, maxValue, currentValue;  
        bool isDragging = false;  
        float offsetX;  
        float initialX, initialY;
public:
    // Constructor for slider
    Slider(float , float , float , float , float);

    // Function to handle mouse input for the slider (dragging behavior)
    void handleMouseInput(const Event &);

    // Function to update the current value based on thumb's position
    void updateCurrentValue();

    // Function to draw the scrollbar on the window
    void draw(RenderWindow &);

    // Function to get the current value (for resizing or other uses)
    float getCurrentValue() const;
    // Method to reset the slider
    void reset();
};// end of Slider class 
#endif