/************************************************
    Written by  : Hassan Ayoub                  *
    Date        : 23 December, 2024             *
    Purpose     : Implementing class Hexagon    * 
************************************************/
#include "Hexagon.h"
#include <thread>
#include <random>
#include <cmath>
#include "Enum.h"
#include <iostream>
extern Screens currentScreen;

// Constructor for hexagon
hexagonTessellator :: hexagonTessellator(RenderWindow &window, Button *ptr, Button *setButton, Slider *scrollBar, 
Slider *redSlider, Slider *greenSlider, Slider *blueSlider, Text *textInstr, Button *reset, Text *slider, Text *rgb_in, Button *retButton) : 
window(window), radius(100), slider(slider), returnButton (retButton),
scrollbar(scrollBar), redSlider(redSlider), greenSlider(greenSlider), blueSlider(blueSlider), setButton(setButton), resetButton(reset)
{
    // Predefined color
    colors = { Color(232, 156, 5) };

    tessellateButton = ptr;
    textInstruction = textInstr;
    for (int i = 0 ; i < 3; i++)
    {
        rgb[i] = rgb_in;
        rgb_in++;
    }
}

// Method to handle events
void hexagonTessellator :: processEvents(const Event &event)
{
    if (event.type == Event::Closed)
    {
        window.close();
    }
    if (currentScreen == HEXAGON_SIZE_COLOR && event.type == Event :: MouseButtonPressed && tessellateButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
    {
        tessellate();  
    }
    if (currentScreen == HEXAGON_SIZE_COLOR && event.type == Event :: MouseButtonPressed && returnButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
    {
        currentScreen = MENU;  
    }
    if (currentScreen == HEXAGON_SIZE_COLOR && event.type == Event :: MouseButtonPressed && setButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
    {
        if (currentColor < maxColor)
        {
            if (currentColor < 1)
            {
                colors[currentColor] = Color(redSlider->getCurrentValue(), greenSlider->getCurrentValue(), blueSlider->getCurrentValue());
            }
            else
            {
                colors.push_back(Color(redSlider->getCurrentValue(), greenSlider->getCurrentValue(), blueSlider->getCurrentValue()));
            }
            currentColor++;  
        }
    }
    if (currentScreen == HEXAGON_SIZE_COLOR)
    {
        scrollbar->handleMouseInput(event);
        redSlider->handleMouseInput(event);
        blueSlider->handleMouseInput(event);
        greenSlider->handleMouseInput(event);
    }
}

// Method to generate shapes
void hexagonTessellator :: generateShapes()
{
    hexagons.clear();
    for (float y = 0; y < window.getSize().y + radius * sqrt(3); y += radius * sqrt(3) * 2) 
    {
        for (float x = -radius; x < window.getSize().x + radius; x += radius * 3) 
        {
            // Create the center hexagon
            createHexagon(x, y);

            // Create surrounding hexagons (6)
            createHexagon(x + radius + radius / 2, y + radius * sqrt(3) / 2);  
            createHexagon(x, y - radius * sqrt(3));  
            createHexagon(x + radius + radius / 2, y - radius * sqrt(3) / 2);  
            createHexagon(x, y + radius * sqrt(3));  
            createHexagon(x - radius - radius / 2, y - radius * sqrt(3) / 2);  
            createHexagon(x - radius - radius / 2, y + radius * sqrt(3) / 2); 
        }
    }       

    // Shuffle the triangles for random animation
    random_device rd;           // like srand(), provides seed for random number generator
    mt19937 g(rd());            // like rand(), provides a random number
    shuffle(hexagons.begin(), hexagons.end(), g);
}

// Method to create the hexagons
void hexagonTessellator::createHexagon(float x, float y)
{
    const float PI = 3.14159265f;
    ConvexShape hexagon(6);
    float angles[6] = {0, 60, 120, 180, 240, 300}; // Angles in degrees

    for (int i = 0; i < 6; i++) 
    {
        float rad = angles[i] * (PI / 180); // Convert angle to radians
        hexagon.setPoint(i, Vector2f(x + radius * cos(rad), y + radius * sin(rad)));
    }

    // Assign a random color
    hexagon.setFillColor(colors[rand() % colors.size()]);
    if (colors[0] != Color(232, 156, 5) || colors.size() > 1)
    {
        hexagon.setOutlineColor(Color::Black);
        hexagon.setOutlineThickness(1);
    }
    else
    {
        hexagon.setOutlineThickness(2);
        hexagon.setOutlineColor(Color(255, 217, 122));
    }
    // Add the hexagon to the vector
    hexagons.push_back(hexagon);
}


// Method to tessellate
void hexagonTessellator :: tessellate()
{
    generateShapes();                   // Generate the hexagons
    currentScreen = HEXAGON_TESSELLATION;
    int hexagonIndex = 0;
    
    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event))
        {
            processEvents(event);  // Handle any events related to SIZE_COLOR_SCREEN
            if (currentScreen == HEXAGON_TESSELLATION && event.type == Event::MouseButtonPressed && resetButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
            {
                currentScreen = MENU;
                break;
            }
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        window.clear(Color::White);

        for (int i = 0; i <= hexagonIndex && i < hexagons.size(); i++) 
        {
            window.draw(hexagons[i]);
        }
        if (hexagonIndex > hexagons.size() / 2)
        {
            resetButton->draw(window);
        }
        if (currentScreen == MENU)
        {
            break;
        }
        window.display();

        this_thread::sleep_for(chrono::milliseconds(10));      // Introduce a delay
        hexagonIndex++;
    } 
    scrollbar->reset();
    redSlider->reset();
    greenSlider->reset();
    blueSlider->reset();
}
// Method to draw the screen before it tessellates
void hexagonTessellator :: draw()
{
    window.draw(*textInstruction);
    tessellateButton->draw(window);
    setButton->draw(window);
    scrollbar->draw(window); 
    window.draw(*slider);   
    redSlider->draw(window);
    greenSlider->draw(window);
    blueSlider->draw(window);
    for (int i = 0; i < 3; i++)
    {
        window.draw(*rgb[i]);
    }
    returnButton->draw(window);
    handleSizeColor(); 
}

// Method to draw the resized hexagon
void hexagonTessellator :: handleSizeColor()
{
    // Update hexagon size based on the current value of the scrollbar
    radius = scrollbar->getCurrentValue();  // Get the current size from the scrollbar

    // Calculate the center position of the hexagon
    float centerX = window.getSize().x / 2;
    float centerY = window.getSize().y / 2 - 10;

    // Draw the resized hexagon at the center of the screen
    ConvexShape hexagon;
    hexagon.setPointCount(6);

    const float PI = 3.14159265f;
    float angles[6] = {0, 60, 120, 180, 240, 300}; // Angles in degrees

    for (int i = 0; i < 6; ++i) 
    {
        float rad = angles[i] * (PI / 180); // Convert angle to radians
        hexagon.setPoint(i, Vector2f(centerX + radius * cos(rad), centerY + radius * sin(rad)));
    }

    hexagon.setFillColor(Color(redSlider->getCurrentValue(), greenSlider->getCurrentValue(), blueSlider->getCurrentValue()));
    window.draw(hexagon);
}