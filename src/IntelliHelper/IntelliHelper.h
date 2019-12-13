#ifndef INTELLIHELPER_H
#define INTELLIHELPER_H

#include<QPoint>


class IntelliHelper{

public:

    static inline float sign(QPoint& p1, QPoint& p2, QPoint& p3){
        return (p1.x()-p3.x())*(p2.y()-p3.y())-(p2.x()-p3.x())*(p1.y()-p3.y());
    }

    static inline bool isInTriangle(QPoint& A, QPoint& B, QPoint& C, QPoint& P){
        float val1, val2, val3;
        bool neg, pos;

        val1 = IntelliHelper::sign(P,A,B);
        val2 = IntelliHelper::sign(P,B,C);
        val3 = IntelliHelper::sign(P,C,A);

        neg = (val1<0.f) || (val2<0.f) || (val3<0.f);
        pos = (val1>0.f) || (val2>0.f) || (val3>0.f);

        return !(neg && pos);
    }
};

#endif
