/************************************************
    Written by  : Hassan Ayoub                  *
    Date        : 23 December, 2024             *
    Purpose     : Implementing class Slider     * 
************************************************/
#include "Slider.h"
#include <iostream>
// Constructor for slider
Slider :: Slider(float width, float height, float minValue, float maxValue, float posY) : width(width), height(height), minValue(minValue), 
                                                                                maxValue(maxValue), currentValue(minValue) 
{ 
    initialY = posY;
    initialX = 580;        
    // Rectangle for the SLIDER track
    track.setSize(Vector2f(width, height));
    track.setFillColor(Color(200, 200, 200));  
    track.setPosition(initialX, initialY);  

    // Rectangle for the thumb (the draggable part)
    thumb.setSize(Vector2f(20, height));        // Thumb is thinner than the track
    thumb.setFillColor(Color(0, 128, 255));     
    thumb.setPosition(initialX, initialY);       
}

// Function to handle mouse input for the slider (dragging behavior)
void Slider :: handleMouseInput(const Event& event) 
{
    if (event.type == Event::MouseButtonPressed) 
    {
        // Check if the mouse is clicking on the thumb
        if (thumb.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) 
        {
            isDragging = true;
            offsetX = event.mouseButton.x - thumb.getPosition().x;  // Store the offset from the mouse to the thumb's position
        }
    }       
    else if (event.type == Event::MouseButtonReleased) 
    {
        isDragging = false;  // Stop dragging when the mouse is released
    }
    if (event.type == Event::MouseMoved && isDragging) 
    {
        // Update thumb position as the mouse moves
        float newX = event.mouseMove.x - offsetX;
        // Constrain the thumb to stay within the track bounds
        if (newX < track.getPosition().x) 
        {
            newX = track.getPosition().x;  // Prevent thumb from going off the left side of the track
        } 
        else if (newX + thumb.getSize().x > track.getPosition().x + track.getSize().x) 
        {
            newX = track.getPosition().x + track.getSize().x - thumb.getSize().x;  // Prevent thumb from going off the right side
        }

        thumb.setPosition(newX, thumb.getPosition().y);  // Update thumb position
        updateCurrentValue();  // Update the current value based on thumb's position
    }
}

void Slider::updateCurrentValue() 
{
    float thumbStart = track.getPosition().x;
    float thumbEnd = track.getPosition().x + track.getSize().x - thumb.getSize().x;
    // This is the formula for Linear-Interpolation
    // Interpolated Value = Start + (Ratio) * (EndValue - StartValue)
    currentValue = minValue + (thumb.getPosition().x - thumbStart) * (maxValue - minValue) / (thumbEnd - thumbStart);
}

// Function to draw the scrollbar on the window
void Slider :: draw(sf::RenderWindow& window) 
{
    window.draw(track);  // Draw the track
    window.draw(thumb);  // Draw the thumb
}

// Function to get the current value (for resizing or other uses)
float Slider :: getCurrentValue() const 
{
    return currentValue;
}

// Method to reset the slider
void Slider :: reset()
{
    track.setPosition(initialX, initialY); 
    thumb.setPosition(initialX, initialY);  
    currentValue = minValue;      
}