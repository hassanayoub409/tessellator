/********************************************************
    Written by  : Hassan Ayoub                          *
    Date        : 25 December, 2024                     *
    Purpose     : Declaring class seirpinskyTessellator * 
********************************************************/
#ifndef SEIRPINSKY_H
#define SEIRPINSKY_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Slider.h"
#include "Tessellator.h"
#include <vector>
using namespace std;
using namespace sf;

class sierpinskiTessellator : public Tessellator
{
    private:
        RenderWindow &window;
        float triangleSize;
        float triangleHeight;
        vector<ConvexShape> triangles;
        vector<Color> colors;
        int maxColor = 10;
        int currentColor = 0;
        int depth = 5;

        Button *tessellateButton;
        Button *setButton, *resetButton, *returnButton;
        Slider *scrollbar;  
        Slider *redSlider, *greenSlider, *blueSlider;
        Text *textInstruction, *slider;
        Text showPixels;
        Text *rgb[3];
    public:
        // Constructor for seirpinskiTessellator
        sierpinskiTessellator(RenderWindow &, Button *, Button *, Slider *, Slider *, Slider *, Button *, Font &, Text *, Text *, Button *);
        // Method to handle events
        void processEvents(const Event &) override;
        // Method to generate seirpinsky triangles
        void generateShapes() override;
        // Method to create the triangles
        void createTriangle(float x, float y);
        // Method to create seirpinsky triangles
        void sierpinski(Vector2f , Vector2f, Vector2f, int);
        // Method to draw the tessellation on screen
        void tessellate() override;
        // Method to draw the screen before it tessellates
        void draw() override;
        // Method to handle size_color screen
        void handleSizeColor() override;
        // Destructor for sierpinski
        ~sierpinskiTessellator();
};
#endif