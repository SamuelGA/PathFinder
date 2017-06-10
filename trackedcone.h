#ifndef TRACKEDCONE_HPP
#define TRACKEDCONE_HPP

class TrackedCone
{
    public:
        TrackedCone(double posX, double posY, int color);
        TrackedCone();

        int getColor();
        double getXPos();
        double getYPos();

        double distanceToCone(TrackedCone *cone);
        TrackedCone middleCone(TrackedCone *another);

        bool isSimilar(TrackedCone *comparedCone);
        void print();

    private:
        double posX;
        double posY;
        int color;
};
#endif
