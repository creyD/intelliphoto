#ifndef INTELLIHELPER_H
#define INTELLIHELPER_H

#include<QPoint>


class IntelliHelper{
public:
    //checks for orientation:
    //  0 - colinear
    //  1 - clockwise
    //  2 - counter clockwise
    static int orientation(QPoint& p1, QPoint& p2, QPoint& p3);

    //checks if q is on segment p1-p2
    static bool onSegment(QPoint& p1, QPoint& q, QPoint& p2);

    //cheks if p1-q1 intersects with p2-q2
    static bool hasIntersection(QPoint& p1, QPoint& q1, QPoint& p2, QPoint& q2);
};

#endif
