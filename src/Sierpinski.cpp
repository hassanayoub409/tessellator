/************************************************
    Written by  : Hassan Ayoub                  *
    Date        : 23 December, 2024             *
    Purpose     : Implementing class seirpinski * 
************************************************/
#include "Sierpinski.h"
#include <thread>
#include <random>

#include "Enum.h"
extern Screens currentScreen;

// Constructor for Varanoi Tessellator
sierpinskiTessellator :: sierpinskiTessellator(RenderWindow &window, Button *ptr, Button *setButton, 
Slider *redSlider, Slider *greenSlider, Slider *blueSlider, Button *reset, Font &font, Text *slider, Text* rgb_in, Button *retButton) : 
window(window), triangleSize(300), returnButton (retButton),
triangleHeight(300 * sqrt(3) / 2), redSlider(redSlider), slider(slider),
greenSlider(greenSlider), blueSlider(blueSlider), setButton(setButton), resetButton(reset)
{
    // Predefined colors
    colors = { Color::Green, Color::Blue, Color::Magenta, Color::Cyan, Color::Yellow };

    tessellateButton = ptr;

    showPixels.setFont(font);
    showPixels.setCharacterSize(20);
    showPixels.setColor(Color::Black);
    showPixels.setPosition(200, window.getSize().y / 2);

    textInstruction = new Text;
    textInstruction->setFont(font);
    textInstruction->setString("Set the size and Color");
    textInstruction->setCharacterSize(20);
    textInstruction->setColor(Color::Black);
    textInstruction->setPosition(260, 10);

    scrollbar = new Slider(200, 20, 300, 1000, 100);
    for (int i = 0 ; i < 3; i++)
    {
        rgb[i] = rgb_in;
        rgb_in++;
    }
}

// Method to handle events
void sierpinskiTessellator :: processEvents(const Event &event)
{
    if (event.type == Event::Closed)
    {
        window.close();
    }
    if (currentScreen == SIERPINSKI_SIZE_COLOR && event.type == Event :: MouseButtonPressed && tessellateButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
    {
        tessellate();  
    }
    if (currentScreen == SIERPINSKI_SIZE_COLOR && event.type == Event :: MouseButtonPressed && returnButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
    {
        currentScreen = MENU;  
    }
    if (currentScreen == SIERPINSKI_SIZE_COLOR && event.type == Event :: MouseButtonPressed && setButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
    {
        if (currentColor < 5)
        {
            colors[currentColor] = Color(redSlider->getCurrentValue(), greenSlider->getCurrentValue(), blueSlider->getCurrentValue());
        }
        else
        {
            colors.push_back(Color(redSlider->getCurrentValue(), greenSlider->getCurrentValue(), blueSlider->getCurrentValue()));
        }
        currentColor++;  
    }
    if (currentScreen == SIERPINSKI_SIZE_COLOR)
    {
        scrollbar->handleMouseInput(event);
        redSlider->handleMouseInput(event);
        blueSlider->handleMouseInput(event);
        greenSlider->handleMouseInput(event);
    }
}

// Method to generate seirpinsky triangles
void sierpinskiTessellator :: generateShapes()
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
    // Define the vertices of the initial large triangle

    random_device rd;           // like srand(), provides seed for random number generator
    mt19937 g(rd());            // like rand(), provides a random number
    shuffle(triangles.begin(), triangles.end(), g);
}

// Method to create the triangles
void sierpinskiTessellator :: createTriangle(float x, float y)
{
    sierpinski(Vector2f(x, y), Vector2f(x + triangleSize, y), Vector2f(x + triangleSize / 2, y + triangleHeight), depth);
    sierpinski(Vector2f(x + triangleSize / 2, y + triangleHeight), Vector2f(x + triangleSize * 1.5, y + triangleHeight), 
    Vector2f(x + triangleSize, y), depth);
}

// Method to create seirpinsky triangles
void sierpinskiTessellator :: sierpinski(Vector2f p1, Vector2f p2, Vector2f p3, int depth_detail)
{
    if (depth_detail == 0) 
    {
        // Base case: Create and store the triangle
        ConvexShape triangle;
        triangle.setPointCount(3);
        triangle.setPoint(0, p1);
        triangle.setPoint(1, p2);
        triangle.setPoint(2, p3);
        triangle.setFillColor(colors[rand() % colors.size()]);
        triangle.setOutlineColor(Color::Black);
        triangle.setOutlineThickness(1);
        triangles.push_back(triangle);
    } 
    else 
    {
        // Find midpoints of each side
        Vector2f mid1((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
        Vector2f mid2((p2.x + p3.x) / 2, (p2.y + p3.y) / 2);
        Vector2f mid3((p1.x + p3.x) / 2, (p1.y + p3.y) / 2);

        // Recursive calls for three smaller triangles
        sierpinski(p1, mid1, mid3, depth_detail - 1);
        sierpinski(mid1, p2, mid2, depth_detail - 1);
        sierpinski(mid3, mid2, p3, depth_detail - 1);
    }
}

// Method to draw the tessellation on screen
void sierpinskiTessellator :: tessellate()
{
    generateShapes();                   // Generate the triangles
    currentScreen = SIERPINSKI_TESSELATION;
    int triangleIndex = 0;

    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event))
        {
            processEvents(event);  // Handle any events related to SIZE_COLOR_SCREEN
            if (currentScreen == SIERPINSKI_TESSELATION && event.type == Event::MouseButtonPressed && resetButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
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

        this_thread::sleep_for(chrono::nanoseconds(1));      // Introduce a delay
        triangleIndex++;
    } 
    scrollbar->reset();
    redSlider->reset();
    greenSlider->reset();
    blueSlider->reset();
}

// Method to draw the screen before it tessellates
void sierpinskiTessellator :: draw()
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

// Method to handle size_color screen
void sierpinskiTessellator :: handleSizeColor()
{
    // Update triangle_size based on the current value of the scrollbar
    triangleSize = round(scrollbar->getCurrentValue());  // Get the current size from the scrollbar

    triangleHeight = triangleSize * sqrt(3) / 2;  

    showPixels.setString(to_string(triangleSize) + " pixels");

    RectangleShape square;

    square.setSize(Vector2f(30, 30));
    square.setPosition(500, 300);
    square.setFillColor(Color(redSlider->getCurrentValue(), greenSlider->getCurrentValue(), blueSlider->getCurrentValue()));
    window.draw(square);
    window.draw(showPixels);
}

sierpinskiTessellator :: ~sierpinskiTessellator()
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
}