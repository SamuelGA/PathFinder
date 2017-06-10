#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include "trackedcone.h"
#include "vector"
#include "conelist.h"
#include "udp_send.h"

/*
    Author: Samuel Gassauer
    date : 06.06.2017
*/

class PathFinder
{

    public:
        PathFinder(UDP_SEND *udpGW);
        ~PathFinder();

        //inserts new cones into an already existing static list. cones which are similar are going to be combined
        void addNewCones(ConeList coneList);
        //draws for each line of cones a line by using a spline algorithm over time [time,x,y] and
        //generates a list of vectors which should navigate the car on the middle of the track
        void iterate();

        //prints all cones with their parameters
        void debugConeList();

        //one list for each side


    private:
        ConeList leftCones;
        ConeList rightCones;
        UDP_SEND *udpGW;

        //creates for given colornumbers the two cone lists;
        void createLeftRightConeList();

        void splineConeList(double precision, ConeList coneList, ConeList *resultList);

        void validateCones();

        void generateSimpleMiddleLine(ConeList *resultList, ConeList *rightCones, ConeList *leftCones);

        //a list of all cones given by the tracker
        ConeList coneList;
};

#endif
