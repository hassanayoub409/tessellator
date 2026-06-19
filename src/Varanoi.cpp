/************************************************
    Written by  : Hassan Ayoub                  *
    Date        : 25 December, 2024             *
    Purpose     : Implementing class Varanoi    * 
************************************************/
#include "Varanoi.h"
#include <thread>
#include <random>
#include <cmath>

#include "Enum.h"
extern Screens currentScreen;

varanoiTessellator :: varanoiTessellator(RenderWindow &window, Button *ptr, Button *setButton, 
Slider *redSlider, Slider *greenSlider, Slider *blueSlider, Button *reset, Font &font, Text *rgb_in, Button *retButton) : 
window(window), no_of_seeds(50), returnButton (retButton),
redSlider(redSlider), 
greenSlider(greenSlider), blueSlider(blueSlider), setButton(setButton), resetButton(reset)
{
    // Predefined colors
    colors = { Color::Red, Color::Green, Color::Blue, Color::Magenta, Color::Cyan, Color::Yellow, Color(192, 234, 10)
                , Color (207, 151, 215), Color(254, 171, 185), Color(140, 212, 122) };

    tessellateButton = ptr;

    showSeeds.setFont(font);
    showSeeds.setCharacterSize(20);
    showSeeds.setColor(Color::Black);
    showSeeds.setPosition(350, window.getSize().y / 2);

    textInstruction = new Text;
    textInstruction->setFont(font);
    textInstruction->setString("Set the No. of Seeds and Color");
    textInstruction->setCharacterSize(20);
    textInstruction->setColor(Color::Black);
    textInstruction->setPosition(260, 10);

    slider = new Text;
    slider->setFont(font);
    slider->setString("NO OF SEEDS");
    slider->setCharacterSize(17);
    slider->setColor(Color::Black);
    slider->setPosition(620, 100);

    scrollbar = new Slider(200, 20, 1, 3000, 100);
    for (int i = 0 ; i < 3; i++)
    {
        rgb[i] = rgb_in;
        rgb_in++;
    }
}

// Method to handle events
void varanoiTessellator :: processEvents(const Event &event)
{
    if (event.type == Event::Closed)
    {
        window.close();
    }
    if (currentScreen == VARANOI_SIZE_COLOR && event.type == Event :: MouseButtonPressed && tessellateButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
    {
        tessellate();  
    }
    if (currentScreen == VARANOI_SIZE_COLOR && event.type == Event :: MouseButtonPressed && returnButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
    {
        currentScreen = MENU;  
    }
    if (currentScreen == VARANOI_SIZE_COLOR && event.type == Event :: MouseButtonPressed && setButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
    {
        if (currentColor < defaultColor)
        {
            colors[currentColor] = Color(redSlider->getCurrentValue(), greenSlider->getCurrentValue(), blueSlider->getCurrentValue());
        }
        else
        {
            colors.push_back(Color(redSlider->getCurrentValue(), greenSlider->getCurrentValue(), blueSlider->getCurrentValue()));
        }
        currentColor++; 
    }
    
    if (currentScreen == VARANOI_SIZE_COLOR)
    {
        scrollbar->handleMouseInput(event);
        redSlider->handleMouseInput(event);
        blueSlider->handleMouseInput(event);
        greenSlider->handleMouseInput(event);
    }
}

// Method to generate seeds
void varanoiTessellator :: generateShapes()
{
    seeds.clear();
    for (int i = 0; i < no_of_seeds; i++)
    {
        Point point(rand() % 800, rand() % 600);
        seeds.push_back(point);
    }
    seeds.shrink_to_fit();
    createVaranoiDiagram();
}

// Method to create varanoi diagram
void varanoiTessellator :: createVaranoiDiagram()
{
    varanoiDiagram.create(window.getSize().x, window.getSize().y, Color::White);

    for (int j = 0; j < window.getSize().y; j++)
    {
        for (int i = 0; i < window.getSize().x; i++)
        {
            Point point(i, j);
            double minDistance = numeric_limits<float>::infinity();
            int seedIndex = -1;

            for (int k = 0; k < seeds.size(); k++)
            {
                double distance = findDistance(point, seeds[k]);
                if (distance < minDistance)
                {
                    minDistance = distance;
                    seedIndex = k;
                }
            }
            varanoiDiagram.setPixel(i, j, colors[seedIndex%colors.size()]);
        }
    }
}

// Method to find the distance between two points
double varanoiTessellator :: findDistance(Point &p1, Point &p2)
{
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

// Method to draw the tessellation on screen
void varanoiTessellator :: tessellate()
{
    generateShapes();                   // Generate the varnoi cells
    currentScreen = VARANOI_TESSELLATION;
    Texture texture;
    texture.create(varanoiDiagram.getSize().x, varanoiDiagram.getSize().y); // Create a texture with the same size as the image
    Sprite sprite;
    // Temporary image to store progressively drawn pixels
    Image tempImage;
    tempImage.create(varanoiDiagram.getSize().x, varanoiDiagram.getSize().y, Color::White); // Start with a blank image
    int rowsDrawn = 0; 

    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event))
        {
            processEvents(event);  // Handle any events related to SIZE_COLOR_SCREEN
            if (currentScreen == VARANOI_TESSELLATION && event.type == Event::MouseButtonPressed && resetButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
            {
                currentScreen = MENU;
                break;
            }
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        if (currentScreen == MENU)
        {
            break;
        }

        if (rowsDrawn < varanoiDiagram.getSize().y) 
        {
            for (int x = 0; x < varanoiDiagram.getSize().x; x++) 
            {
                tempImage.setPixel(x, rowsDrawn, varanoiDiagram.getPixel(x, rowsDrawn));
            }
            rowsDrawn++;                        // Move to the next row
            texture.update(tempImage);          // Update the texture with the new pixels
        }
        // Clear and draw
        window.clear(Color::White);
        sprite.setTexture(texture);
        window.draw(sprite);
        window.display();
        if (rowsDrawn > varanoiDiagram.getSize().y / 2)
        {
            resetButton->draw(window);
        }
        this_thread::sleep_for(chrono::milliseconds(10));      // Introduce a delay
        
    } 
    scrollbar->reset();
    redSlider->reset();
    greenSlider->reset();
    blueSlider->reset();
}

// Method to draw the screen before it tessellates
void varanoiTessellator :: draw()
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
    window.draw(*slider);
    returnButton->draw(window);
    handleSizeColor(); 
}

// Method to give the functionality of resizing and color selection
void varanoiTessellator :: handleSizeColor()
{
    // Update no_of_pixels based on the current value of the scrollbar
    no_of_seeds = scrollbar->getCurrentValue();  // Get the current size from the scrollbar
    
    showSeeds.setString(to_string(no_of_seeds));

    RectangleShape square;

    square.setSize(Vector2f(30, 30));
    square.setPosition(500, 300);
    square.setFillColor(Color(redSlider->getCurrentValue(), greenSlider->getCurrentValue(), blueSlider->getCurrentValue()));
    window.draw(square);
    window.draw(showSeeds);
}

varanoiTessellator :: ~varanoiTessellator()
{
    if (textInstruction != nullptr)
    {
        delete textInstruction;
        textInstruction = nullptr;
    }
    if (scrollbar != nullptr)
    {
        delete scrollbar;
        scrollbar = nullptr;
    }
    if (slider != nullptr)
    {
        delete slider;
        slider = nullptr;
    }
}