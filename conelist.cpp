

#include "conelist.h"
#include <iostream>
#include <cmath>

void ConeList::print()
{
    int counter = 0;
    for (std::vector<TrackedCone>::iterator iteratorCone = this->begin() ; iteratorCone != this->end(); ++iteratorCone)
    {
        std::cout << "cone " << counter << ":  ";
        iteratorCone->print();
        counter++;
    }
    std::cout << std::endl;
}

void ConeList::sortByDistance(int originalSize, ConeList *result, TrackedCone startCone)
{

    if (originalSize == result->size()) return;

    TrackedCone nearestCone = this->nearestCone(startCone);


    result->push_back(nearestCone);

    int counter = 0;
    for (TrackedCone cone : *this)
    {
        if (cone.getXPos() == nearestCone.getXPos() && cone.getYPos() == nearestCone.getYPos())
        {
            this->erase(this->begin() + counter);
        }
        counter++;
    }

    sortByDistance(originalSize, result, nearestCone);
}

TrackedCone ConeList::nearestCone(TrackedCone coneInput)
{
    double distance = 100000;
    TrackedCone nearest;

    for (TrackedCone cone : *this)
    {
        double newDistance = coneInput.distanceToCone(&cone);
        if (newDistance < distance)
        {
            nearest = cone;
            distance = newDistance;
        }
    }
    std::cout << "from: " ; coneInput.print();
    std::cout << distance << std::endl;
    std::cout << "next: " ; nearest.print();
    return nearest;
}

void ConeList::generateDriveLine(ConeList *list, ConeList *resultLine)
{
    for (TrackedCone cone : *this)
    {
        TrackedCone nearestCone = list->nearestCone(cone);

        std::cout << "nearestConeFrom: "; cone.print(); std::cout << " is "; nearestCone.print(); std::cout<< std::endl;;
        resultLine->push_back(cone.middleCone(&nearestCone));
    }
}

double ConeList::calculateLength()
{
    double length = 0;
    int coneNumber = this->size();

    std::vector<TrackedCone>::iterator iteratorCone = this->begin();
    int prevX;
    int prevY;
    int x;
    int y;

    prevX = iteratorCone->getXPos();
    prevY = iteratorCone->getYPos();

    iteratorCone++;

    for (int i = 1; i < coneNumber; i++)
    {
        x = iteratorCone->getXPos();
        y = iteratorCone->getYPos();

        length += sqrt(abs(prevX - x) + abs(prevY - y));

        prevX = x;
        prevY = y;
        iteratorCone++;
    }

}
