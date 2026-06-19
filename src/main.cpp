/********************************************************
    Written by  : Hassan Ayoub                          *
    Date        : 20 December, 2024                     *
    Purpose     : Implement Driver function             *
                  for the application "The Tessellator" * 
********************************************************/
/****************************************************************
    Compile :  g++ -std=c++11 main.cpp Menu.cpp FrameShape.cpp  * 
    Slider.cpp Triangle.cpp Button.cpp Square.cpp Hexagon.cpp   *
    Varanoi.cpp Sierpinski.cpp Penrose.cpp -I../SFML-2.1/include*
    -o main -L../SFML-2.1/lib -lsfml-graphics -lsfml-window     *
    -lsfml-system -lsfml-audio                                  *
                                                                *
    Run : ./main                                                *
****************************************************************/
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Tessellator.h"
#include "FrameShape.h"
#include "Menu.h"
#include "Slider.h"
#include "Triangle.h"
#include "Square.h"
#include "Hexagon.h"
#include "Varanoi.h"
#include "Sierpinski.h"
#include "Penrose.h"
#include "Button.h"
#include "Enum.h"
#include <iostream>
#include <string>
#include <thread>

using namespace std;
using namespace sf;

void displayMenu(RenderWindow &);
void displayEnd(RenderWindow &);

Screens currentScreen = MENU;

// execution of main function starts from here
int main() 
{
    // Creating the window
    RenderWindow window(VideoMode(800, 600), "The Tessellator");
    
    // Creating fonts to be used
    Font font, menuLine;
    if (!font.loadFromFile("../assets/fonts/font/font.ttf")) {
        cout << "Error loading font\n";
        exit(0);
    }
    if (!menuLine.loadFromFile("../assets/fonts/font/Rainbow After Rain.ttf")) {
        cout << "Error loading font\n";
        exit(0);
    }
   
    // Load textures
    Texture squareTexture, triangleTexture, hexagonalTexture, varanoiTexture, sierpinskiTexture, penroseTexture;
    squareTexture.loadFromFile("../assets/images/square.png");
    triangleTexture.loadFromFile("../assets/images/triangle.png");
    hexagonalTexture.loadFromFile("../assets/images/hexagon.png");
    varanoiTexture.loadFromFile("../assets/images/varanoi.png");
    sierpinskiTexture.loadFromFile("../assets/images/sierpinski.png");
    penroseTexture.loadFromFile("../assets/images/penrose.png");

    // Creating a button for tessellate selection, setting color, resettingToMenu
    Button tessellationButton(Vector2f(150, 30), Vector2f(100, window.getSize().y - 100 + 10), "Tessellate", font, Color::Blue);
    Button setButton(Vector2f(65, 20), Vector2f(650, 440), "Set Color", font, Color(128, 64, 192));
    Button resetButton(Vector2f(50, 30), Vector2f(20, 530), "Reset", font, Color(176, 190, 197));
    Button exitButton(Vector2f(65, 20), Vector2f(700, 540), "Exit", font, Color(120, 20, 20));
    Button returnButton(Vector2f(65, 20), Vector2f(650, 510), "Return", font, Color (128, 64, 192));

    // Creatign a slider for colors, and size
    Slider scrollbar(200, 20, 20, 200, 100);
    Slider redSlider(200, 20, 0, 255, 200);
    Slider greenSlider(200, 20, 0, 255, 300);
    Slider blueSlider(200, 20, 0, 255, 400);

    // Creating a text for instruction
    Text textInstruction;
    textInstruction.setFont(font);
    textInstruction.setString("Set the Size and Color of Tile");
    textInstruction.setCharacterSize(20);
    textInstruction.setColor(Color::Black);
    textInstruction.setPosition(260, 10);

    // Creating text instructions for sliders
    Text size;
    size.setFont(font);
    size.setString("SIZE");
    size.setCharacterSize(17);
    size.setColor(Color::Black);
    size.setPosition(650, 100);
    Text rgb[3];
    rgb[0].setString("RED");
    rgb[0].setPosition(650, 200);
    rgb[1].setString("GREEN");
    rgb[1].setPosition(650, 300);
    rgb[2].setString("BLUE");
    rgb[2].setPosition(650, 400);
    for (int i = 0; i < 3; i++)
    {
        rgb[i].setFont(font);
        rgb[i].setCharacterSize(17);
        rgb[i].setColor(Color::Black);
    }

    // Create the menu
    Menu menu(window, font, menuLine, exitButton);
    menu.addShape("Square", squareTexture);
    menu.addShape("Triangle", triangleTexture);
    menu.addShape("Hexagon", hexagonalTexture);
    menu.addShape("Varanoi Cells", varanoiTexture);
    menu.addShape("Sierpinski Triangle", sierpinskiTexture);
    menu.addShape("Penrose Tiling", penroseTexture);

    // Achieve polymorphism using this pointer
    Tessellator *tessellator = nullptr;
    displayMenu(window);

    // Application loop
    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed) 
            {
                window.close();
            }
            else if (currentScreen == MENU) 
            {
                menu.handleEvent(event);
            }
            else if (currentScreen == TRIANGLE_SIZE_COLOR)
            {
                if (tessellator != nullptr)
                {
                    tessellator->processEvents(event);
                }
                else
                {
                    tessellator = new triangleTessellator(window, &tessellationButton, &setButton, &scrollbar, &redSlider, &greenSlider, 
                    &blueSlider, &textInstruction, &resetButton, &size, rgb, &returnButton);
                }
            }
            else if (currentScreen == SQUARE_SIZE_COLOR)
            {
                if (tessellator != nullptr)
                {
                    tessellator->processEvents(event);
                }
                else
                {
                    tessellator = new squareTessellator(window, &tessellationButton, &setButton, &scrollbar, &redSlider, &greenSlider, 
                    &blueSlider, &textInstruction, &resetButton, &size, rgb, &returnButton);
                }
            }
            else if (currentScreen == HEXAGON_SIZE_COLOR)
            {
                if (tessellator != nullptr)
                {
                    tessellator->processEvents(event);
                }
                else
                {
                    tessellator = new hexagonTessellator(window, &tessellationButton, &setButton, &scrollbar, &redSlider, &greenSlider, 
                    &blueSlider, &textInstruction, &resetButton, &size, rgb, &returnButton);
                }
            }
            else if (currentScreen == VARANOI_SIZE_COLOR)
            {
                if (tessellator != nullptr)
                {
                    tessellator->processEvents(event);
                }
                else
                {
                    tessellator = new varanoiTessellator(window, &tessellationButton, &setButton, &redSlider, 
                    &greenSlider, &blueSlider, &resetButton, font, rgb, &returnButton);
                }
            }
            else if (currentScreen == SIERPINSKI_SIZE_COLOR)
            {
                if (tessellator != nullptr)
                {
                    tessellator->processEvents(event);
                }
                else
                {
                    tessellator = new sierpinskiTessellator(window, &tessellationButton, &setButton, &redSlider, 
                    &greenSlider, &blueSlider, &resetButton, font, &size, rgb, &returnButton);
                }
            }
            else if (currentScreen == PENROSE_SIZE_COLOR)
            {
                if (tessellator != nullptr)
                {
                    tessellator->processEvents(event);
                }
                else
                {
                    tessellator = new penroseTessellator(window, &tessellationButton, &setButton, &redSlider, 
                    &greenSlider, &blueSlider, &resetButton, font, &size, rgb, &returnButton);
                }
            }
        }
        window.clear(Color::White);  

        if (currentScreen == MENU) 
        {
            menu.draw();
            if (tessellator != nullptr)
            {
                delete tessellator;
                tessellator = nullptr;
            }
        }
        else if (tessellator != nullptr)
        {
                window.clear(Color::White);  
                tessellator->draw();             
        }
        else if (currentScreen == EXIT)
        {
            displayEnd(window);
        }
        window.display();  
    }
}// main function ends here


// displayMenu starts from here
void displayMenu(RenderWindow &window)
{
    Music music;
    // Load the music file
    if (!music.openFromFile("../assets/music/vivaldi.flac")) 
    {
        cout << "Error: Could not load the music file!" << endl;
        exit(0);
    }

    Texture backgroundTexture;
    backgroundTexture.loadFromFile("../assets/images/background.png");
    Sprite background(backgroundTexture);

    // Adjust background scaling to fit the window
    background.setScale(static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );
    Font font;
    if (!font.loadFromFile("../assets/fonts/darkcastle/Darkcastle_PERSONAL_USE_ONLY.otf")) 
    { 
        cout << "Error loading font\n";
        exit(0);
    }
    Font anotherFont;
    if (!anotherFont.loadFromFile("../assets/fonts/Bleeding_Cowboys.ttf"))
    {
        cout << "Error loading font\n";
        exit(0);
    }
    string title = "The Tessellator";
    vector<Text> letters;
    float startX = 16;                      // Starting x position for the first letter
    float startY = 250;                     // Y position for the text
    float letterSpacing = 50;               // Spacing between letters

    Text name;
    name.setString("Brought to life by Hassan Ayoub");
    name.setFont(anotherFont);
    name.setCharacterSize(20);
    name.setPosition(Vector2f(500, 550));
    name.setColor(Color(255, 223, 0));

    int index = 0;
    for (int i = 0; i < title.length(); i++) 
    {
        Text letter(title[i], font, 60);
        letter.setPosition(startX + i * letterSpacing, startY);
        letter.setColor(sf::Color::White); 
        letters.push_back(letter);
    }
    music.play();
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
   
        window.clear();
        window.draw(background);

        for (int i = 0; i <= index && i < letters.size(); i++) 
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    window.close();
                }
            }
            window.draw(letters[i]);
            
        }
        if (index == letters.size())
        {
            this_thread::sleep_for(chrono::milliseconds(200));
            window.draw(name);
            window.display();
            this_thread::sleep_for(chrono::seconds(2));
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(150));
        window.display();
        index++;
    }
}// displayMenu ends here


// displayEnd starts here
void displayEnd(RenderWindow &window)
{
    Music music;
    // Load the music file
    if (!music.openFromFile("../assets/music/vivaldiEnd.flac")) 
    {
        cout << "Error: Could not load the music file!" << endl;
        exit(0);
    }

    Texture backgroundTexture;
    backgroundTexture.loadFromFile("../assets/images/background.png");
    Sprite background(backgroundTexture);

    // Adjust background scaling to fit the window
    background.setScale(static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    Font font;
    if (!font.loadFromFile("../assets/fonts/lemon_tuesday/Lemon Tuesday.otf")) 
    { 
        cout << "Error loading font\n";
        exit(0);
    }

    Text str;
    str.setString("Goodbye");
    str.setFont(font);
    str.setCharacterSize(50);
    str.setPosition(Vector2f(300, 250));
    str.setColor(Color(255, 140, 0));
    music.play();
    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
        }
   
        window.clear();
        window.draw(background);
        window.draw(str);
        window.display();
        this_thread::sleep_for(chrono::seconds(2));
        window.close();
    }
}// displayEnd ends here