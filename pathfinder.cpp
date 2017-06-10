#include "pathfinder.h"
#include "iostream"
#include "spline.cpp"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include "udp_send.h"


int main()
{
    UDP_SEND *udpSend = new UDP_SEND();
    PathFinder *pathfinder = new PathFinder(udpSend);

    //some random cone input....is going to be replaced by a textfile input
    TrackedCone *coneOneR = new TrackedCone(0,4, 0);
    TrackedCone *coneOneL = new TrackedCone(0,-4, 1);
    TrackedCone *coneTwoR = new TrackedCone(4,6, 0);
    TrackedCone *coneTwoL = new TrackedCone(4,-2, 1);
    TrackedCone *coneThreeR = new TrackedCone(8,5, 0);
    TrackedCone *cone3Li = new TrackedCone(8,-3, 1);
    TrackedCone *cone4R = new TrackedCone(12,2, 0);
    TrackedCone *cone4Li = new TrackedCone(12,-6, 1);
    TrackedCone *cone5R = new TrackedCone(16,3, 0);
    TrackedCone *cone5Li = new TrackedCone(16,-5, 1);
    TrackedCone *cone6R = new TrackedCone(20, 1, 0);
    TrackedCone *cone6Li = new TrackedCone(20, -9, 1);
    TrackedCone *cone7Li = new TrackedCone(22, -2, 0);
    TrackedCone *cone8Li = new TrackedCone(23, -4, 0);


    ConeList coneListInput;

    coneListInput.push_back(*coneOneL);
    coneListInput.push_back(*coneOneR);
    coneListInput.push_back(*coneTwoL);
    coneListInput.push_back(*coneTwoR);
    coneListInput.push_back(*cone3Li);
    coneListInput.push_back(*coneThreeR);
    coneListInput.push_back(*cone4Li);
    coneListInput.push_back(*cone4R);
    coneListInput.push_back(*cone5Li);
    coneListInput.push_back(*cone5R);
    coneListInput.push_back(*cone6Li);
    coneListInput.push_back(*cone6R);
    coneListInput.push_back(*cone7Li);
    coneListInput.push_back(*cone8Li);
    coneListInput.push_back(TrackedCone(20, -13, 1));
    coneListInput.push_back(TrackedCone(24, -5, 0));
    coneListInput.push_back(TrackedCone(24, -13, 0));
    coneListInput.push_back(TrackedCone(23, -16, 0));


    pathfinder->addNewCones(coneListInput);
    //**********************************************************************
    pathfinder->iterate();
    //pathfinder->debugConeList();

}


PathFinder::PathFinder(UDP_SEND *udpGW) :
    udpGW(udpGW)
{
}

void PathFinder::iterate()
{
    //first of all seperating the cones by their color
    this->createLeftRightConeList();

    //then spline both sides
    ConeList optimisedLeftSide;
    ConeList optimisedRightSide;

    double leftLength = ceil(leftCones.calculateLength());
    double rightLength = ceil(rightCones.calculateLength());

    //std::cout << "l: " << leftLength << " r: " << rightLength << std::endl;

    splineConeList(rightCones.size() * 1, leftCones, &optimisedLeftSide);
    splineConeList(rightCones.size() * 1, rightCones, &optimisedRightSide);

    //optimisedLeftSide.print();
    //optimisedRightSide.print();

    ConeList middleCones;
    //optimisedRightSide.generateDriveLine(&optimisedLeftSide, &middleCones);
    generateSimpleMiddleLine(&middleCones, &optimisedRightSide, &optimisedLeftSide);


    //middleCones.print();

    udpGW->sendOriginalTrack(leftCones, rightCones);
    udpGW->sendSplineLine(optimisedLeftSide);
    udpGW->sendSplineLine(optimisedRightSide);
    udpGW->sendSplineLine(middleCones);
}

void PathFinder::splineConeList(double precision, ConeList coneList, ConeList *resultList)
{
    int counter = 0;
    int color = coneList.begin()->getColor();
    std::vector<float> times;
    std::vector<glm::vec2> points;

    for (ConeList::iterator iteratorCone = coneList.begin(); iteratorCone != coneList.end(); ++ iteratorCone)
    {
        times.push_back(counter);
        points.push_back(glm::vec2(iteratorCone->getXPos(), iteratorCone->getYPos()));
        counter++;
    }

    /* Create the spline interpolating the position over time */
    Spline<float, glm::vec2> sp(times, points);

    /* Compute the interpolated position at time 0.75f */
    float step = counter / precision;

    for (double i = 0; i <= counter; i += step)
    {
        glm::vec2 value(sp[i]);
        resultList->push_back(*(new TrackedCone(value.x, value.y, color)));
    }


    return ;
}

void PathFinder::createLeftRightConeList()
{
    if (coneList.size() == 0) return;

    for (std::vector<TrackedCone>::iterator iteratorCone = this->coneList.begin(); iteratorCone != this->coneList.end(); ++iteratorCone)
    {
        if (iteratorCone->getColor() == 1) leftCones.push_back(*iteratorCone);
        else if (iteratorCone->getColor() == 0) rightCones.push_back(*iteratorCone);
    }
}

void PathFinder::addNewCones(ConeList coneList)
{

    for (std::vector<TrackedCone>::iterator iteratorCone = coneList.begin() ; iteratorCone != coneList.end(); ++iteratorCone)
    {
        bool isAlreadyInList = false;

        for (std::vector<TrackedCone>::iterator iteratorConeAlreadyIn = this->coneList.begin() ;
        iteratorConeAlreadyIn != this->coneList.end(); ++iteratorConeAlreadyIn)
        {
            if (iteratorCone->isSimilar(&(*iteratorConeAlreadyIn))) isAlreadyInList = true;
        }
        if (!isAlreadyInList)
        {
            this->coneList.push_back(*iteratorCone);
        }
    }
}

void PathFinder::generateSimpleMiddleLine(ConeList *resultList, ConeList *rightSide, ConeList *leftSide)
{
    ConeList::iterator leftIteratorCone = leftSide->begin();
    ConeList::iterator rightIteratorCone = rightSide->begin();

    while (leftIteratorCone < leftSide->end())
    {
        double leftX = leftIteratorCone->getXPos();
        double leftY = leftIteratorCone->getYPos();
        double rightX = rightIteratorCone->getXPos();
        double rightY = rightIteratorCone->getYPos();

        double middleX = leftX - (leftX - rightX) / 2;

        double middleY = leftY - ((leftY - rightY) / 2);

        std::cout << "leftY: " << leftY << " rightY: " << rightY << " middleY: " << middleY << std::endl;

        TrackedCone *middleCone = new TrackedCone(middleX, middleY, 42);
        resultList->push_back(*middleCone);

        leftIteratorCone++;
        rightIteratorCone++;
    }
};

void PathFinder::debugConeList()
{
    for (std::vector<TrackedCone>::iterator iteratorCone = this->coneList.begin() ; iteratorCone != this->coneList.end(); ++iteratorCone)
    {
        std::cout << "cone ";
        iteratorCone->print();
    }
    std::cout << std::endl << "leftCones: " << std::endl;
     for (std::vector<TrackedCone>::iterator iteratorCone = this->leftCones.begin() ; iteratorCone != this->leftCones.end(); ++iteratorCone)
    {
        std::cout << "cone ";
        iteratorCone->print();
    }
    std::cout << std::endl << "rightCones: " << std::endl;
     for (std::vector<TrackedCone>::iterator iteratorCone = this->rightCones.begin() ; iteratorCone != this->rightCones.end(); ++iteratorCone)
    {
        std::cout << "cone ";
        iteratorCone->print();
    }
}

