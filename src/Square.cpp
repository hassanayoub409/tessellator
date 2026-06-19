/************************************************
    Written by  : Hassan Ayoub                  *
    Date        : 23 December, 2024             *
    Purpose     : Implementing class Square     * 
************************************************/
#include "Square.h"
#include <thread>
#include <random>

#include "Enum.h"
extern Screens currentScreen;

// Constructor for squareTessellator
squareTessellator :: squareTessellator(RenderWindow &window, Button *ptr, Button *setButton, Slider *scrollBar, 
Slider *redSlider, Slider *greenSlider, Slider *blueSlider, Text *textInstr, Button *reset, Text *slider, Text *rgb_in, Button *retButton) : 
window(window), squareSize(100), returnButton(retButton),
scrollbar(scrollBar), redSlider(redSlider), slider(slider),
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
void squareTessellator :: processEvents(const Event &event)
{
    if (event.type == Event::Closed)
    {
        window.close();
    }
    if (currentScreen == SQUARE_SIZE_COLOR && event.type == Event :: MouseButtonPressed && tessellateButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
    {
        tessellate();  
    }
    if (currentScreen == SQUARE_SIZE_COLOR && event.type == Event :: MouseButtonPressed && returnButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
    {
        currentScreen = MENU;  
    }
    if (currentScreen == SQUARE_SIZE_COLOR && event.type == Event :: MouseButtonPressed && setButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
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
    if (currentScreen == SQUARE_SIZE_COLOR)
    {
        scrollbar->handleMouseInput(event);
        redSlider->handleMouseInput(event);
        blueSlider->handleMouseInput(event);
        greenSlider->handleMouseInput(event);
    }
}
// Method to generate squares
void squareTessellator :: generateShapes()
{
    squares.clear();
    for (float y = 0; y < window.getSize().y + squareSize; y += squareSize) 
    {
        for (float x = -squareSize / 2; x < window.getSize().x + squareSize; x += squareSize)
        {
            createSquare(x, y);
        }
    }
    // Shuffle the squares for random animation
    random_device rd;           // like srand(), provides seed for random number generator
    mt19937 g(rd());            // like rand(), provides a random number
    shuffle(squares.begin(), squares.end(), g);
}
// Method to create a square
void squareTessellator :: createSquare(float x, float y)
{
    RectangleShape square(Vector2f(squareSize, squareSize));
    square.setPosition(x, y);
    square.setFillColor(colors[rand() % colors.size()]);
    square.setOutlineColor(Color::Black);
    square.setOutlineThickness(1);
    squares.push_back(square);
}

// Method to tessellate
void squareTessellator :: tessellate()
{
    generateShapes();                       // Generate the squares
    currentScreen = SQUARE_TESSELLATION;
    int squareIndex = 0;
    
    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event))
        {
            processEvents(event);                           // Handle any events related to SIZE_COLOR_SCREEN
            if (currentScreen == SQUARE_TESSELLATION && event.type == Event::MouseButtonPressed && resetButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
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

        for (int i = 0; i <= squareIndex && i < squares.size(); i++) 
        {
            window.draw(squares[i]);
        }
        if (squareIndex > squares.size() / 2)
        {
            resetButton->draw(window);
        }
        if (currentScreen == MENU)
        {
            break;
        }
        window.display();

        this_thread::sleep_for(chrono::milliseconds(10));      // Introduce a delay
        squareIndex++;
    } 
    scrollbar->reset();
    redSlider->reset();
    greenSlider->reset();
    blueSlider->reset();
}

// Method to draw the screen before it tesselates
void squareTessellator :: draw()
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

// Method to draw the resized square
void squareTessellator :: handleSizeColor()
{
    // Update square size based on the current value of the scrollbar
    squareSize = scrollbar->getCurrentValue();  // Get the current size from the scrollbar

    // Calculate the center position of the square
    float centerX = window.getSize().x / 2;
    float centerY = window.getSize().y / 2 - 10;

    // Draw the resized square at the center of the screen
    RectangleShape square;
    // Calculate the center offset (we want the square's center to remain fixed)
    float offsetX = squareSize / 2;
    float offsetY = squareSize / 2;

    square.setSize(Vector2f(squareSize, squareSize));
    square.setPosition(centerX - offsetX, centerY - offsetY);
    square.setFillColor(Color(redSlider->getCurrentValue(), greenSlider->getCurrentValue(), blueSlider->getCurrentValue()));
    window.draw(square);
}