/********************************************************
    Written by  : Hassan Ayoub                          *
    Date        : 26 December, 2024                     *
    Purpose     : Declaring class penroseTessellator    * 
********************************************************/
#ifndef PENROSE_H
#define PENROSE_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Slider.h"
#include "Tessellator.h"
#include <vector>
using namespace std;
using namespace sf;

class penroseTessellator : public Tessellator
{
    public:
        struct Triangle 
        {
            int color; // 0 for red, 1 for blue
            Vector2f A, B, C; // Vertices
        };
    private:
        RenderWindow &window;
        float triangleSize;
        vector <Triangle> triangles;
        vector<ConvexShape> actualTriangles;
        vector<Color> colors;
        int currentColor = 0;
        int subdivisions = 5;

        Button *tessellateButton;
        Button *setButton, *resetButton, *returnButton;
        Slider *scrollbar, *subDivisions;  
        Slider *redSlider, *greenSlider, *blueSlider;
        Text *textInstruction, *slider, *subdivisionsSlider;
        Text showSize_Subdivisions;
        Text *rgb[3];

    public:
        // Constructor for penroseTessellator
        penroseTessellator(RenderWindow &, Button *, Button *, Slider *, Slider *, Slider *, Button *, Font &, Text *, Text*, Button*);
        // Method to handle events
        void processEvents(const Event &) override;
        // Method to generate triangles
        void generateShapes() override;
        // Method to subdivide the triangles
        vector<Triangle> subdivide();
        // Method to draw the tessellation on screen
        void tessellate() override;
        // Method to draw the screen before it tessellates
        void draw() override;
        // Method to handle size_color screen
        void handleSizeColor() override;
        // method to create actual triangles
        void createTriangles();
        // Destructor for penrose
        ~penroseTessellator();
};
#endif