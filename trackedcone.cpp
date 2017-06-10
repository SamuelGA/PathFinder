#include "trackedcone.h"
#include <iostream>
#include <math.h>


TrackedCone::TrackedCone(double posX, double posY, int color) :
posX(posX),
posY(posY),
color(color)
{
}

TrackedCone TrackedCone::middleCone(TrackedCone *another)
{
    double leftX = this->getXPos();
    double leftY = this->getYPos();
    double rightX = another->getXPos();
    double rightY = another->getYPos();

    double middleX = leftX - (leftX - rightX) / 2;

    double middleY = leftY - ((leftY - rightY) / 2);

    std::cout << "leftY: " << leftY << " rightY: " << rightY << " middleY: " << middleY << std::endl;

    TrackedCone *middleCone = new TrackedCone(middleX, middleY, 42);
    return *middleCone;
}

bool TrackedCone::isSimilar(TrackedCone *comparedCone)
{
    if (this->posX == comparedCone->posX && this->posY == comparedCone->posY && this->color == comparedCone->color)
    {
        return true;
    }
    return false;
}

TrackedCone::TrackedCone()
{

}

void TrackedCone::print()
{
    std::cout << "posX: " << posX << " posY: " << posY << " color: " << color << std::endl;
}

double TrackedCone::distanceToCone(TrackedCone *cone)
{
    double leftX = cone->getXPos();
    double leftY = cone->getYPos();
    double rightX = this->getXPos();
    double rightY = this->getYPos();

    double distance = sqrt(pow(abs(leftX - rightX), 2) + pow(abs(leftY - rightY), 2));
    return distance;
}


int TrackedCone::getColor()
{
    return this->color;
}

double TrackedCone::getXPos()
{
    return this->posX;
}

double TrackedCone::getYPos()
{
    return this->posY;
}
