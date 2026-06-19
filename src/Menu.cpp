/************************************************
    Written by  : Hassan Ayoub                  *
    Date        : 22 December, 2024             *
    Purpose     : Implementing class Menu       * 
************************************************/
#include "Menu.h"
#include "Enum.h"
#include <iostream>
using namespace std;
// maxColumns defines how many frames fit in a row
#define MAX_FRAMES 3;

extern Screens currentScreen;
// Constructor of Menu
Menu :: Menu(RenderWindow &window, const Font &font, const Font &lineFont, Button &button) : window(window), font(font), exitButton(button)
{
    firstLine.setFont(lineFont);
    firstLine.setString("Click a Tile to Tessellate");
    firstLine.setCharacterSize(40);
    firstLine.setColor(Color::Black);
    firstLine.setPosition(200, 15);
}

// Methood to add shape to vector items
void Menu :: addShape(const string &name, const Texture &texture) 
{
    // Column determines how many present items will go to next row considering max_frames
    // row determines how many rows my present items take to fill considering max_frames
    int column = items.size() % MAX_FRAMES;  
    int row = items.size() / MAX_FRAMES;

    float xPosition = column * (frameSize.x + frameSpacing) + 140;       // Horizontal position
    float yPosition = row * (frameSize.y + topMargin) + 140;             // Vertical position

    FrameShape item(name, texture, {xPosition, yPosition}, frameSize, font);
    items.push_back(item);
}

// Methood to draw the menu
void Menu :: draw() 
{
    window.draw(firstLine);
    for (int i = 0; i < items.size(); i++) 
    {
        items[i].draw(window);
    }
    exitButton.draw(window);
}

// Method to handle event (clicking the frame)
void Menu :: handleEvent(const Event &event)
{
    if (event.type == Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == Mouse::Left)
        {
            Vector2i mousePos = Mouse::getPosition(window);

            for (int i = 0; i < items.size(); i++)
            {
                FloatRect bounds = items[i].getBounds();

                if (bounds.contains(mousePos.x, mousePos.y))
                {
                    if (i == 0)
                    {
                        currentScreen = SQUARE_SIZE_COLOR;
                    }
                    else if (i == 1)
                    {
                        currentScreen = TRIANGLE_SIZE_COLOR;
                    }
                    else if (i == 2)
                    {
                        currentScreen = HEXAGON_SIZE_COLOR;
                    }
                    else if (i == 3)
                    {
                        currentScreen = VARANOI_SIZE_COLOR;
                    }
                    else if (i == 4)
                    {
                        currentScreen = SIERPINSKI_SIZE_COLOR;
                    }
                    else if (i == 5)
                    {
                        currentScreen = PENROSE_SIZE_COLOR;
                    }
                    return;
                }
            }
            if (exitButton.isClicked(Vector2f(mousePos)))
            {
                currentScreen = EXIT;
                return;
            }
        }
        
    }
}