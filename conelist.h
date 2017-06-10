#ifndef CONELIST_HPP
#define CONELIST_HPP

#include "trackedcone.h"
#include <vector>

class ConeList : public std::vector<TrackedCone>
{
    public:
        void print();

        TrackedCone nearestCone(TrackedCone cone);
        void generateDriveLine(ConeList *list, ConeList *resultLine);
        double calculateLength();
};

#endif
