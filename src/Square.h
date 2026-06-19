/********************************************************
    Written by  : Hassan Ayoub                          *
    Date        : 23 December, 2024                     *
    Purpose     : Declaring class triangleTessellator   * 
********************************************************/
#ifndef SQUARE_H
#define SQUARE_H

#include <SFML/Graphics.hpp>
#include "Tessellator.h"
#include "Button.h"
#include "Slider.h"
#include <vector>
using namespace std;
using namespace sf;

class squareTessellator : public Tessellator
{
    private:
        RenderWindow &window;
        vector <RectangleShape> squares;
        float squareSize;
        vector<Color> colors;
        int maxColor = 5;
        int currentColor = 0;

        Button *tessellateButton;
        Button *setButton, *resetButton;
        Button *returnButton;
        Slider *scrollbar;  
        Slider *redSlider, *greenSlider, *blueSlider;
        Text *textInstruction, *slider;
        Text *rgb[3];
    
    public:
        // Constructor for squareTessellator
        squareTessellator(RenderWindow &, Button *, Button *, Slider *, Slider *, Slider *, Slider *, Text *, Button *, Text *, Text *, Button *);

        // Method to handle events
        void processEvents(const Event &) override;

        // Method to generate squares
        void generateShapes() override;

        // Method to create a square
        void createSquare(float, float);

        // Method to tessellate
        void tessellate() override;

        // Method to draw the screen before it tesselates
        void draw() override;

        // Method to draw the resized square
        void handleSizeColor() override;
};
#endif