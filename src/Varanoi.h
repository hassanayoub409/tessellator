/********************************************************
    Written by  : Hassan Ayoub                          *
    Date        : 25 December, 2024                     *
    Purpose     : Declaring class varanoiTessellator    * 
********************************************************/
#ifndef VARANOI_H
#define VARANOI_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Slider.h"
#include "Tessellator.h"
#include <vector>
using namespace std;
using namespace sf;

class varanoiTessellator : public Tessellator
{
    public:
        struct Point 
        {
            float x, y;
            Point(float x = 0, float y = 0) : x(x), y(y) {}
        };
    private:
        RenderWindow &window;
        vector < Point > seeds;
        Image varanoiDiagram;
        int no_of_seeds;
        vector<Color> colors;
        int defaultColor = 10;
        int currentColor = 0;

        Button *tessellateButton;
        Button *setButton, *resetButton, *returnButton;
        Slider *scrollbar;  
        Slider *redSlider, *greenSlider, *blueSlider;
        Text *textInstruction, *slider;
        Text showSeeds;
        Text *rgb[3];
    public:
        // Constructor for Varanoi Tessellator
        varanoiTessellator(RenderWindow &, Button *, Button *, Slider *, Slider *, Slider *, Button *, Font &, Text *, Button *);
        // Method to handle events
        void processEvents(const Event &) override;
        // Method to generate seeds
        void generateShapes() override;
        // Method to create varanoi diagram
        void createVaranoiDiagram();
        // Method to find the distance between two points
        double findDistance(Point &, Point &);
        // Method to draw the tessellation on screen
        void tessellate() override;
        // Method to draw the screen before it tessellates
        void draw() override;
        // Method to give the functionality of resizing and color selection
        void handleSizeColor() override;
        // Destructor for varanoi
        ~varanoiTessellator();
};
#endif