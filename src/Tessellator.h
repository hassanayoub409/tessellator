/********************************************************
    Written by  : Hassan Ayoub                          *
    Date        : 24 December, 2024                     *
    Purpose     : Declaring class Tessellator           * 
********************************************************/
#ifndef Tessellator_H
#define Tessellator_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Tessellator
{
    public:
        virtual void processEvents(const Event &) = 0;
        virtual void generateShapes() = 0;
        virtual void tessellate() = 0;
        virtual void draw() = 0;
        virtual void handleSizeColor() = 0;
        virtual ~Tessellator() {}
};
#endif