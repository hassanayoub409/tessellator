/********************************************************
    Written by  : Hassan Ayoub                          *
    Date        : 23 December, 2024                     *
    Purpose     : Declaring class hexagonTessellator    * 
********************************************************/
#ifndef HEXAGON_H
#define HEXAGON_H

#include <SFML/Graphics.hpp>
#include "Tessellator.h"
#include "Button.h"
#include "Slider.h"
#include <vector>
using namespace std;
using namespace sf;

class hexagonTessellator : public Tessellator
{
    private:    
        RenderWindow &window;
        float radius;
        vector <ConvexShape> hexagons;
        vector<Color> colors;
        int maxColor = 5;
        int currentColor = 0;

        Button *tessellateButton;
        Button *setButton, *resetButton, *returnButton;
        Slider *scrollbar;  
        Slider *redSlider, *greenSlider, *blueSlider;
        Text *textInstruction, *slider;
        Text *rgb[3];

    public:
        // Constructor for hexagon
        hexagonTessellator(RenderWindow &, Button *, Button *, Slider *, Slider *, Slider *, Slider *, Text *, Button *, Text *, Text *, Button *);
        // Method to handle events
        void processEvents(const Event &) override;
        // Method to generate shapes
        void generateShapes() override;
        // Method to create the hexagons 
        void createHexagon(float, float);
        // Method to tessellate
        void tessellate() override;
        // Method to draw the screen before it tessellates
        void draw() override;
        // Method to draw the resized hexagon
        void handleSizeColor() override;
};
#endif