/************************************************
    Written by  : Hassan Ayoub                  *
    Date        : 23 December, 2024             *
    Purpose     : Implementing class Triangle   * 
************************************************/
#include "Triangle.h"
#include <thread>
#include <random>

#include "Enum.h"
extern Screens currentScreen;

// Constructor for triangle
triangleTessellator :: triangleTessellator(RenderWindow &window, Button *ptr, Button *setButton, Slider *scrollBar, 
Slider *redSlider, Slider *greenSlider, Slider *blueSlider, Text *textInstr, Button *reset, Text *slider, Text *rgb_in, Button *retButton) : 
window(window), triangleSize(100), slider(slider), returnButton(retButton),
triangleHeight(100 * sqrt(3) / 2), scrollbar(scrollBar), redSlider(redSlider), 
greenSlider(greenSlider), blueSlider(blueSlider), setButton(setButton), resetButton(reset)
{                                                       
    // Predefined colors
    colors = { Color::Red, Color::Green, Color::Blue };

    tessellateButton = ptr;
    textInstruction = textInstr;
    for (int i = 0 ; i < 3; i++)
    {
        rgb[i] = rgb_in;
        rgb_in++;
    }
}

// Method to handle events
void triangleTessellator :: processEvents(const Event &event) 
{
    if (event.type == Event::Closed)
    {
        window.close();
    }
    if (currentScreen == TRIANGLE_SIZE_COLOR && event.type == Event :: MouseButtonPressed && tessellateButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
    {
        tessellate();  
    }
    if (currentScreen == TRIANGLE_SIZE_COLOR && event.type == Event :: MouseButtonPressed && returnButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
    {
        currentScreen = MENU;  
    }
    if (currentScreen == TRIANGLE_SIZE_COLOR && event.type == Event :: MouseButtonPressed && setButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
    {
        if (currentColor < maxColor)
        {
            if (currentColor < 3)
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
    if (currentScreen == TRIANGLE_SIZE_COLOR)
    {
        scrollbar->handleMouseInput(event);
        redSlider->handleMouseInput(event);
        blueSlider->handleMouseInput(event);
        greenSlider->handleMouseInput(event);
    }
}

// Method to generate triangles
void triangleTessellator :: generateShapes() 
{
    // Generate tessellated triangles
    triangles.clear();
    for (float y = 0; y < window.getSize().y + triangleHeight; y += triangleHeight) 
    {
        for (float x = -triangleSize / 2; x < window.getSize().x + triangleSize; x += triangleSize)
        {
            createTriangle(x, y);
        }
    }
    // Shuffle the triangles for random animation
    random_device rd;           // like srand(), provides seed for random number generator
    mt19937 g(rd());            // like rand(), provides a random number
    shuffle(triangles.begin(), triangles.end(), g);
}
// Method to create the triangles
void triangleTessellator :: createTriangle(float x, float y) 
{
    // Create two triangles (upright and inverted) to cover the space
    createSingleTriangle(x, y, true);
    createSingleTriangle(x, y, false);
}
// Method to create two triangles
void triangleTessellator :: createSingleTriangle(float x, float y, bool isUpright) 
{
    ConvexShape triangle;
    triangle.setPointCount(3);

    if (isUpright) 
    {
        triangle.setPoint(0, Vector2f(x, y));
        triangle.setPoint(1, Vector2f(x + triangleSize, y));
        triangle.setPoint(2, Vector2f(x + triangleSize / 2, y + triangleHeight));
    } 
    else 
    {
        triangle.setPoint(0, Vector2f(x + triangleSize / 2, y + triangleHeight));
        triangle.setPoint(1, Vector2f(x + triangleSize * 1.5, y + triangleHeight));
        triangle.setPoint(2, Vector2f(x + triangleSize, y));
    }
    triangle.setOutlineColor(Color::Black);
    triangle.setOutlineThickness(0.5);
    // Assign one of colors
    triangle.setFillColor(colors[rand() % colors.size()]);
    triangles.push_back(triangle);
}
// Method to draw the tessellation on screen
void triangleTessellator :: tessellate() 
{
    generateShapes();                   // Generate the triangles
    currentScreen = TRIANGLE_TESSELLATION;
    int triangleIndex = 0;
    
    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event))
        {
            processEvents(event);  // Handle any events related to SIZE_COLOR_SCREEN
            if (currentScreen == TRIANGLE_TESSELLATION && event.type == Event::MouseButtonPressed && resetButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
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

        for (int i = 0; i <= triangleIndex && i < triangles.size(); i++) 
        {
            window.draw(triangles[i]);
        }
        if (triangleIndex > triangles.size() / 2)
        {
            resetButton->draw(window);
        }
        if (currentScreen == MENU)
        {
            break;
        }
        window.display();

        this_thread::sleep_for(chrono::milliseconds(10));      // Introduce a delay
        triangleIndex++;
    } 
    scrollbar->reset();
    redSlider->reset();
    greenSlider->reset();
    blueSlider->reset();
}
// Method to draw the screen before it tessellates
void triangleTessellator :: draw()
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
// Method to draw the triangle being resized
void triangleTessellator :: handleSizeColor() 
{
    // Update triangle size based on the current value of the scrollbar
    triangleSize = scrollbar->getCurrentValue();  // Get the current size from the scrollbar
    triangleHeight = triangleSize * sqrt(3) / 2;  // Adjust height for the triangle

    // Calculate the center position of the triangle
    float centerX = window.getSize().x / 2;
    float centerY = window.getSize().y / 2 - 10;

    // Draw the resized triangle at the center of the screen
    ConvexShape triangle;
    triangle.setPointCount(3);
    // Calculate the center offset (we want the triangle's center to remain fixed)
    float offsetX = triangleSize / 2;
    float offsetY = triangleHeight / 2;

    // Set the three points for the upright triangle, keeping the center fixed
    triangle.setPoint(0, Vector2f(centerX - offsetX, centerY + offsetY)); // Left corner
    triangle.setPoint(1, Vector2f(centerX + offsetX, centerY + offsetY)); // Right corner
    triangle.setPoint(2, Vector2f(centerX, centerY - offsetY)); // Top corner 

    triangle.setFillColor(Color(redSlider->getCurrentValue(), greenSlider->getCurrentValue(), blueSlider->getCurrentValue()));
    window.draw(triangle);
}