/************************************************
    Written by  : Hassan Ayoub                  *
    Date        : 23 December, 2024             *
    Purpose     : Implementing class Button     * 
************************************************/
#include "Button.h"

// Constructor for Button
Button :: Button(const Vector2f &size, const Vector2f &position, const string label, const Font &font, Color color) : shape(size), fontForButton(font)
{
    shape.setPosition(position);
    shape.setFillColor(color); 

    textInsideButton.setFont(font);
    textInsideButton.setString(label);
    textInsideButton.setCharacterSize(20); 
    textInsideButton.setColor(Color::Black); 

    // Center the text in the button
    sf::FloatRect textBounds = textInsideButton.getLocalBounds();
    textInsideButton.setPosition(position.x + size.x / 2 - textBounds.width / 2, position.y + size.y + 5);
}

// Method to check whether a button is Clicked
bool Button :: isClicked(Vector2f mousePos) const
{
    return shape.getGlobalBounds().contains(mousePos);
}

// Method to check whether a button is Clicked
void Button :: draw(RenderWindow &window) const
{
    window.draw(shape);
    window.draw(textInsideButton);
}
