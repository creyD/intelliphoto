#ifndef INTELLIHELPER_H
#define INTELLIHELPER_H

#include<QPoint>
#include<vector>

/*!
 * \brief The Triangle struct holds the 3 vertices of a triangle.
 */
struct Triangle{
    QPoint A,B,C;
};


namespace IntelliHelper {

    /*!
     * \brief A function to get the 2*area of a traingle, using its determinat.
     * \param p1    - The Point to check its side.
     * \param p2    - The first Point of the spanning Line
     * \param p3    - The second Point of the spanning line.
     * \return Returns the area of the traingle*2
     */
    inline float sign(QPoint& p1, QPoint& p2, QPoint& p3){
        return (p1.x()-p3.x())*(p2.y()-p3.y())-(p2.x()-p3.x())*(p1.y()-p3.y());
    }

    /*!
     * \brief A function to check if a given point is in a triangle.
     * \param tri   - The triangle to check, if it contains the point.
     * \param P     - The point to check if it is in the triangle.
     * \return Returns true if the point is in the triangle, false otheriwse
     */
    inline bool isInTriangle(Triangle& tri, QPoint& P){
        float val1, val2, val3;
        bool neg, pos;

        val1 = IntelliHelper::sign(P,tri.A,tri.B);
        val2 = IntelliHelper::sign(P,tri.B,tri.C);
        val3 = IntelliHelper::sign(P,tri.C,tri.A);

        neg = (val1<0.f) || (val2<0.f) || (val3<0.f);
        pos = (val1>0.f) || (val2>0.f) || (val3>0.f);

        return !(neg && pos);
    }

    /*!
     * \brief A function to split a polygon in its spanning traingles by using Meisters Theorem of graph theory by clipping ears of a planar graph.
     * \param polyPoints    - The Vertices of the polygon.
     * \return Returns a Container of disjoint Triangles, which desribe the polygon area.
     */
    std::vector<Triangle> calculateTriangles(std::vector<QPoint> polyPoints);

    /*!
     * \brief A function to check if a point lies in a polygon by checking its spanning triangles.
     * \param triangles - The spanning triangles of the planar polygon.
     * \param point     - The point to checl, if it lies in the polygon.
     * \return Returns true if the point lies in the üpolygon, otherwise false.
     */
    bool isInPolygon(std::vector<Triangle> &triangles, QPoint &point);

}

#endif
