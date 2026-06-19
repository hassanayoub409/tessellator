/****************************************************
    Written by  : Hassan Ayoub                      *
    Date        : 22 December, 2024                 *
    Purpose     : Implementing class FrameShape     * 
****************************************************/

#include "FrameShape.h"

// Parametrized Constructor of FrameShape
FrameShape :: FrameShape(const string &name, const Texture &texture, Vector2f position, Vector2f size, const Font &font)
{
    frame.setPosition(position);                        // setting position of frame
    frame.setSize(size);                                // setting size of frame
    frame.setOutlineColor(Color::Black);                // setting outline color of frame
    frame.setOutlineThickness(0);                       // setting outline thickness of frame
    frame.setFillColor(Color::White);                   // filling frame with color

    image.setTexture(texture);                          // setting texture of sprite "image"
    image.setPosition(position);                        // setting position of image
                                                        // scaling the sprite according to the frame
    image.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y);     

    text.setFont(font);                                 // setting font for text
    text.setString(name);                               // setting string
    text.setCharacterSize(20);                          // setting character size
    text.setColor(Color::Black);                        // setting color for text
    
    // Center the text below the frame
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(position.x + size.x / 2 - textBounds.width / 2, position.y + size.y + 5);
}

// Method to draw a frame on window
void FrameShape :: draw(sf::RenderWindow& window) const 
{
    window.draw(frame);
    window.draw(image);
    window.draw(text);
}

// Method to check if mouse clicked a certain frame
bool FrameShape :: isClicked(Vector2f mousePosition) const 
{
    return frame.getGlobalBounds().contains(mousePosition);
}