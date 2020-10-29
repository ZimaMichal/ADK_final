#include "algorithms.h"
#include <cmath>


Algorithms::Algorithms()
{

}

int Algorithms::getPointLinePosition(QPointF &q, QPointF &p1, QPointF &p2)
{
    //Point in the left halfplane -> return 1
    //Point in the right halfplane -> return 0
    //Point on the line -> return -1
    //Point on vertex -> return -2

    //Distance P1Q
    double p1q=sqrt((q.x() - p1.x())*(q.x() - p1.x()) + (q.y() - p1.y())*(q.y() - p1.y()));
    //Distance P1P2
    double p1p2=sqrt((p2.x() - p1.x())*(p2.x() - p1.x()) + (p2.y() - p1.y())*(p2.y() - p1.y()));
    //Distance P2Q
    double p2q=sqrt((q.x() - p2.x())*(q.x() - p2.x()) + (q.y() - p2.y())*(q.y() - p2.y()));

    //Point on vertex
    if ((p1q < 5) || (p2q <5)) //tolerance is 4 because app draw point q as circle with radius 5
        return -2;

    //Point on line
    if (fabs((p1q+p2q)-p1p2) <= 0.2)

        return -1;

    //Get point and line position
    double ux = p2.x() - p1.x();
    double uy = p2.y() - p1.y();
    double vx = q.x() - p1.x();
    double vy = q.y() - p1.y();

    //Determinant
    double t = ux * vy - uy * vx;


    //Point in the left halfplane
    if ( t > 0)
         return 1;

    //Point in the right halfplane
    if (t < 0)
        return 0;

}

double Algorithms::getAngle(QPointF &p1, QPointF &p2, QPointF &p3, QPointF &p4)
{
    //Get vectors u, v
    double ux = p2.x() - p1.x();
    double uy = p2.y() - p1.y();
    double vx = p4.x() - p3.x();
    double vy = p4.y() - p3.y();

    //Norms
    double nu = sqrt(ux * ux + uy * uy);
    double nv = sqrt(vx * vx + vy * vy);

    //Dot product
    double dot = ux * vx + uy * vy;

    return fabs(acos(dot/(nu*nv)));
}

int Algorithms::getPositionWinding(QPointF &q, std::vector<QPointF> &pol)
{
    //Position of a point and polygon: Winding Number Algorithm
    //q inside P: 1
    //q outside P: 0
    //q on P boundary: -1
    //q on P vertex: -2

    double Omega = 0.0;
    int edge, vertex;
    //Set tolerance
    const double eps = 1.0e-6;

    //Amount of polygon vertices
    const int n = pol.size();

    //Process all vertices of the polygon
    for (int i = 0; i < n; i++)
    {

        //Get angle omega
        double om = getAngle(q,pol[i],q,pol[(i+1)%n]);

        //Get orientation of q and pol[i], pol[i+1]
        int orientation = getPointLinePosition(q, pol[i], pol[(i+1)%n]);
        //Point on vertex
        if (orientation == -2)
            vertex = 1;  //true, on vertex
        //Point on the edge
        if (orientation == -1)
            edge = -1;
        //Point in the left halfplane
        if (orientation == 1)
            Omega += om;

        //Point in the right halfplane
        else
            Omega -= om;
    }

    //Point on vertex
    if (vertex == 1)
        return -2;
    //Point on the edge
    if (edge == -1)
        return -1;

    //Point q inside polygon
    else if (fabs(fabs(Omega) - 2*M_PI) < eps)
        return 1;


    //Point q outside polygon
    else
    return 0;

}


int Algorithms::getPositionRay(QPointF &q, std::vector<QPointF> &pol)
{
    //Position of a point and polygon: Ray Crossing Algorithm
    //q inside P: 1
    //q outside P: 0
    //q on P boundary: -1
    //q on P vertex: -2

    //Amount of intersections
    int k = 0;
    int vertex=0;

    //Amount of polygon vertices
    const int n = pol.size();

    //Process all vertices of the polygon
    for (int i = 1; i < n + 1 ; i++)
    {

        //Compute xi, yi, xii, yii
        double xir = pol[i%n].x() - q.x();
        double yir = pol[i%n].y() - q.y();
        double xiir = pol[i-1].x() - q.x();
        double yiir = pol[i-1].y() - q.y();

        //Distance P1P2
        double p1q=sqrt((pol[i%n].x() - q.x())*(pol[i%n].x() - q.x()) + (pol[i%n].y() - q.y())*(pol[i%n].y() - q.y()));
        //Distance P2Q
        double p2q=sqrt((pol[i-1].x() - q.x())*(pol[i-1].x() - q.x()) + (pol[i-1].y() - q.y())*(pol[i-1].y() - q.y()));

        //Point on vertex
        if ((p1q < 5) || (p2q <5)) //tolerance is 4 because app draw point q as circle with radius 5
            vertex += 1;


        //Does segment (pi-1, pi) intersect ray
        if ((yir > 0) && (yiir <= 0) || (yiir > 0) && (yir <= 0))
        {
            //Compute x coordinate of intersection
            double xm = (xir * yiir - xiir * yir)/(yir - yiir);

            //Point q in the right halfplane
            if (xm > 0)
                k += 1;
        }
    }
    if (vertex >0)
        return -2;
    else

    //Get amount of intersections: odd or even
    return k%2;
}
