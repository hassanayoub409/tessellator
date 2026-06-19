/************************************************
    Written by  : Hassan Ayoub                  *
    Date        : 23 December, 2024             *
    Purpose     : Implementing class Penrose    * 
************************************************/
#include "Penrose.h"
#include <thread>
#include <random>

#include "Enum.h"
extern Screens currentScreen;

#define PI 3.14159265358979323846264338327950288
const float GOLDEN_RATIO = (1 + std::sqrt(5)) / 2;

// Constructor for penroseTessellator
penroseTessellator :: penroseTessellator(RenderWindow &window, Button *ptr, Button *setButton, 
Slider *redSlider, Slider *greenSlider, Slider *blueSlider, Button *reset, Font &font, Text *slider, Text *rgb_in, Button *retButton) : 
window(window), triangleSize(550), slider(slider), returnButton(retButton),
redSlider(redSlider), greenSlider(greenSlider), blueSlider(blueSlider), setButton(setButton), resetButton(reset)
{
    // Predefined colors
    colors = { Color::Black, Color::Magenta };

    tessellateButton = ptr;

    showSize_Subdivisions.setFont(font);
    showSize_Subdivisions.setCharacterSize(20);
    showSize_Subdivisions.setColor(Color::Black);
    showSize_Subdivisions.setPosition(90, window.getSize().y / 2);

    textInstruction = new Text;
    textInstruction->setFont(font);
    textInstruction->setString("Set Size and Subdivisions");
    textInstruction->setCharacterSize(20);
    textInstruction->setColor(Color::Black);
    textInstruction->setPosition(260, 10);

    subdivisionsSlider = new Text;
    subdivisionsSlider->setFont(font);
    subdivisionsSlider->setString("Subdivisions");
    subdivisionsSlider->setCharacterSize(17);
    subdivisionsSlider->setColor(Color::Black);
    subdivisionsSlider->setPosition(615, 60);

    scrollbar = new Slider(200, 20, 290, 700, 100);
    subDivisions = new Slider(200, 20, 1, 10, 60);
    for (int i = 0 ; i < 3; i++)
    {
        rgb[i] = rgb_in;
        rgb_in++;
    }
}

// Method to handle events
void penroseTessellator :: processEvents(const Event &event)
{
    if (event.type == Event::Closed)
    {
        window.close();
    }
    if (currentScreen == PENROSE_SIZE_COLOR && event.type == Event :: MouseButtonPressed && tessellateButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
    {
        tessellate();  
    }
    if (currentScreen == PENROSE_SIZE_COLOR && event.type == Event :: MouseButtonPressed && returnButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
    {
        currentScreen = MENU;  
    }
    if (currentScreen == PENROSE_SIZE_COLOR && event.type == Event :: MouseButtonPressed && setButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
    {
        if (currentColor > 1)
        {
            currentColor = 0;
        }
        if (currentColor < 2)
        {
            colors[currentColor] = Color(redSlider->getCurrentValue(), greenSlider->getCurrentValue(), blueSlider->getCurrentValue());
        }
        currentColor++;  
    }
    if (currentScreen == PENROSE_SIZE_COLOR)
    {
        scrollbar->handleMouseInput(event);
        subDivisions->handleMouseInput(event);
        redSlider->handleMouseInput(event);
        blueSlider->handleMouseInput(event);
        greenSlider->handleMouseInput(event);
    }
}
// Method to generate triangles
void penroseTessellator :: generateShapes()
{
    triangles.clear();
    for (int i = 0; i < 10; i++) 
    {
        // Adjust the polar coordinates to have a wheel pattern
        Vector2f B = Vector2f(cos((2 * i - 1) * PI / 10) * triangleSize, sin((2 * i - 1) * PI / 10) * triangleSize);
        Vector2f C = Vector2f(cos((2 * i + 1) * PI / 10) * triangleSize, sin((2 * i + 1) * PI / 10) * triangleSize);
        if (i % 2 == 0)         // mirror every second triangle
        {
            Vector2f temp;
            temp = B;
            B = C;
            C = temp;
        }
        // Position the center at the window center
        triangles.push_back({0, Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), B + sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), C + sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f)});
    }
    for (int i = 0; i < subdivisions; i++)
    {
        triangles = subdivide();
    }
}

// Method to subdivide the triangles
vector<penroseTessellator::Triangle> penroseTessellator :: subdivide()
{
    vector<Triangle> result;

    for (const Triangle& triangle : triangles) 
    {
        if (triangle.color == 0) 
        { // Red triangle
            Vector2f P = triangle.A + (triangle.B - triangle.A) / GOLDEN_RATIO;
            result.push_back({0, triangle.C, P, triangle.B}); // Red triangle
            result.push_back({1, P, triangle.C, triangle.A}); // Blue triangle
        } 
        else 
        { // Blue triangle
            Vector2f Q = triangle.B + (triangle.A - triangle.B) / GOLDEN_RATIO;
            Vector2f R = triangle.B + (triangle.C - triangle.B) / GOLDEN_RATIO;
            result.push_back({1, R, triangle.C, triangle.A}); // Blue triangle
            result.push_back({1, Q, R, triangle.B});          // Blue triangle
            result.push_back({0, R, Q, triangle.A});          // Red triangle
        }
    }
    return result;
}


// Method to draw the tessellation on screen
void penroseTessellator :: tessellate()
{
    generateShapes();                           // Generate the triangles
    createTriangles();
    currentScreen = PENROSE_TESSELLATION;
    int triangleIndex = 0;

    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event))
        {
            processEvents(event);  // Handle any events related to SIZE_COLOR_SCREEN
            if (currentScreen == PENROSE_TESSELLATION && event.type == Event::MouseButtonPressed && resetButton->isClicked(Vector2f(event.mouseButton.x, event.mouseButton.y)))
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
            window.draw(actualTriangles[i]);
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
    subDivisions->reset();
    redSlider->reset();
    greenSlider->reset();
    blueSlider->reset();
}

// method to create actual triangles
void penroseTessellator :: createTriangles()
{
    for (int i = 0; i < triangles.size(); i++)
    {
        ConvexShape shape;
        shape.setPointCount(3);
        shape.setPoint(0, triangles[i].A);
        shape.setPoint(1, triangles[i].B);
        shape.setPoint(2, triangles[i].C);
        
        if (triangles[i].color == 0) 
        {                                                   // Red triangle
            shape.setFillColor(colors[1]);         
        } 
        else 
        {                                                   // Blue triangle
            shape.setFillColor(colors[0]);    
        }

        shape.setOutlineColor(Color(50, 50, 50));           // Outline color
        shape.setOutlineThickness(1);
        actualTriangles.push_back(shape);
    }

    // Shuffle the triangles for random animation
    random_device rd;           // like srand(), provides seed for random number generator
    mt19937 g(rd());            // like rand(), provides a random number
    shuffle(actualTriangles.begin(), actualTriangles.end(), g);
}


// Method to draw the screen before it tessellates
void penroseTessellator :: draw()
{
    window.draw(*textInstruction);
    tessellateButton->draw(window);
    setButton->draw(window);
    scrollbar->draw(window);  
    subDivisions->draw(window);
    window.draw(*slider);  
    redSlider->draw(window);
    greenSlider->draw(window);
    blueSlider->draw(window);
    for (int i = 0; i < 3; i++)
    {
        window.draw(*rgb[i]);
    }
    window.draw(*subdivisionsSlider);
    returnButton->draw(window);
    handleSizeColor();
}

// Method to handle size_color screen
void penroseTessellator :: handleSizeColor()
{
    // Update triangle_size based on the current value of the scrollbar
    triangleSize = round(scrollbar->getCurrentValue());  // Get the current size from the scrollbar
    subdivisions = round(subDivisions->getCurrentValue());

    showSize_Subdivisions.setString(to_string(triangleSize) + " pixels" + "  and  " + to_string(subdivisions) + " subdivisions");

    RectangleShape square;

    square.setSize(Vector2f(30, 30));
    square.setPosition(500, 300);
    square.setFillColor(Color(redSlider->getCurrentValue(), greenSlider->getCurrentValue(), blueSlider->getCurrentValue()));
    window.draw(square);
    window.draw(showSize_Subdivisions);
}

// Destructor for penrose
penroseTessellator :: ~penroseTessellator()
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
    if (subDivisions != nullptr)
    {
        delete subDivisions;
        subDivisions = nullptr;       
    }
    if (subdivisionsSlider != nullptr)
    {
        delete subdivisionsSlider;
        subdivisionsSlider = nullptr;
    }
}