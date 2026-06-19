/********************************************************
    Written by  : Hassan Ayoub                          *
    Date        : 23 December, 2024                     *
    Purpose     : Declaring class triangleTessellator   * 
********************************************************/
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Slider.h"
#include "Tessellator.h"
#include <vector>
using namespace std;
using namespace sf;

class triangleTessellator : public Tessellator
{
    private:
        RenderWindow &window;
        float triangleSize;
        float triangleHeight;
        vector<ConvexShape> triangles;
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
        // Constructor for triangle 
        triangleTessellator(RenderWindow &, Button *, Button *, Slider *, Slider *, Slider *, Slider *, Text *, Button *, Text *, Text *, Button *);
        // Method to handle events
        void processEvents(const Event &) override;
        // Method to generate triangles
        void generateShapes() override;
        // Method to draw the tessellation on screen
        void tessellate() override;
        // Method to draw the screen before it tessellates
        void draw() override;
        // Method to create the triangles
        void createTriangle(float x, float y);
        // Method to create two triangles
        void createSingleTriangle(float x, float y, bool isUpright);
        // Method to draw the resized triangle
        void handleSizeColor() override;
};
#endif