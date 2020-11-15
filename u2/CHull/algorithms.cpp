#include "algorithms.h"
#include "sortbyy.h"
#include "sortbyx.h"
#include <cmath>

Algorithms::Algorithms()
{

}

double Algorithms::getAngle(QPoint &p1, QPoint &p2, QPoint &p3, QPoint &p4)
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


int Algorithms::getPointLinePosition(QPoint &q,QPoint &p1,QPoint &p2)
{
    //Analyze point and line position
    //1 point in the left half plane
    //0 point in the right half plane
    //-1 point on the line
    double ux = p2.x() - p1.x();
    double uy = p2.y() - p1.y();

    double vx = q.x() - p1.x();
    double vy = q.y() - p1.y();

    double t = ux * vy - uy * vx;

    //Point in the left half plane
    if (t>0)
        return 1;
    if (t<0)
        return 0;
    return -1;
}

double Algorithms::getPointLineDist(QPoint &a,QPoint &p1,QPoint &p2)
{
    //Compute distance of point a from line p(p1, p2)
    double numerator = a.x()* (p1.y() - p2.y()) + p1.x()*(p2.y() - a.y()) +
                      p2.x()*(a.y() - p1.y());

    //Coordinate differences
    double dx = p1.x() - p2.x();
    double dy = p1.y() - p2.y();

    //Point and line distance
    return fabs(numerator)/sqrt(dx*dx + dy*dy);
}


QPolygon Algorithms::jarvis(QPolygon &points)
{
    //Create Convex Hull using Jarvis Scan Algorithm
    QPolygon ch;

    //Sort points by y
    std::sort(points.begin(), points.end(), sortByY());

    //Create q
    QPoint q = points[0];

    //Create r
    QPoint r(0,q.y());

    //Initialize pj, pjj
    QPoint pj = q;
    QPoint pjj = r;

    //Add q into Convex Hull
    ch.push_back(q);

    //Find all points of Convex hull
    do {

        //Initialize i_max, om_max
        int i_max = -1;
        double o_max = 0;

        //Find suitable point maximizing angle omega
        for (int i = 0; i < points.size(); i++)
        {
            //Compute omega
            double omega = getAngle(pj, pjj, pj, points[i]);

            //Actualize maximum
            if (omega > o_max)
            {
                o_max = omega;
                i_max = i;
            }
        }

        //Add point to convex hull
        ch.push_back(points[i_max]);

        //Assign points
        pjj = pj;
        pj = points[i_max];

    } while ((pj!=q));

return ch;
}


QPolygon Algorithms::qhull(QPolygon &points)
{
    //Create Convex Hull using QHull Algorithm (Global procedure)
    QPolygon ch;
    QPolygon upoints, lpoints;

    //Sort points according to x coordinate
    std::sort(points.begin(), points.end(), sortByX());

    //Create q1, q3
    QPoint q1 = points[0];
    QPoint q3 = points.back();

    //Add q1, q3 to upoints/lpoints
    upoints.push_back(q1);
    upoints.push_back(q3);
    lpoints.push_back(q1);
    lpoints.push_back(q3);

    //Split points to upoints/lpoints
    for (int i = 0; i < points.size(); i++)
    {
        //Add point to upoints
        if (getPointLinePosition(points[i], q1,q3) == 1)
            upoints.push_back(points[i]);

        //Otherwise, add point to lpoints
        else if(getPointLinePosition(points[i], q1,q3) == 0)
            lpoints.push_back(points[i]);
    }

    //Add q3 to CH
    ch.push_back(q3);

    //Recursion for upoints
    qh(1, 0, upoints,ch);

    //Add q1 to CH
    ch.push_back(q1);

    //Recursion for lpoints
    qh(0, 1, lpoints,ch);

    return ch;
}


void Algorithms::qh(int s, int e, QPolygon &points, QPolygon &ch)
{
    //Create Convex Hull using QHull Algorithm (Local procedure)
    int i_max = -1;
    double d_max = 0;

    //Browse all points
    for (int i = 2; i < points.size(); i++)
    {
        //Point in the right halfplane
        if (getPointLinePosition(points[i], points[s], points[e]) == 0)
        {
            double distance = getPointLineDist(points[i], points[s], points[e]);

            //Actualize i_max, d_max
            if (distance > d_max)
            {
                d_max=distance;
                i_max=i;
            }
        }
    }

    //Suitable point has been found
    if(i_max!=-1)
    {
        //Process first segment using recursion
        qh(s, i_max, points, ch);

        //Add furthest p to CH
        ch.push_back(points[i_max]);

        //Process second segment using recursion
        qh(i_max, e, points, ch);
    }
}

QPolygon Algorithms::sweepLine(QPolygon &points)
{
    //Increment method, sweep line
    QPolygon ch;

    unsigned int m = points.size();

    //List of predecessors
    std::vector<int> p(m);

    //List of successors
    std::vector<int> n(m);

    //Sort points by X
    std::sort(points.begin(),points.end(),sortByX());

    // Create initial aproximation
    n[0] = 1;
    n[1] = 0;
    p[0] = 1;
    p[1] = 0;

    // Process all points according to x coordinates
    for (unsigned int i = 2; i < m; i++)
       {
           //Point i lies in the upper half plane
           if(points[i].y() > points[i-1].y()){
               //Link i and its predecessor and successor
               p[i] = i-1;
               n[i] = n[i-1];
           }

           //Point i lies in the lower half plane
           else
           {
               //Link i and its predecessor and successor
               p[i] = p[i-1];
               n[i] = i - 1;
           }

           //Link predecessor and successor and i
           p[n[i]] = i;
           n[p[i]] = i;

           //Fix upper tangent
           while (getPointLinePosition(points[n[n[i]]], points[i], points[n[i]]) == 0)
           {
               //Change predecessor and successor
               p[n[n[i]]] = i;
               n[i] = n[n[i]];
           }

           //Fix lower tangent
           while (getPointLinePosition(points[p[p[i]]], points[i], points[p[i]]) == 1)
           {
               //Change predecessor and successor
               n[p[p[i]]] = i;
               p[i] = p[p[i]];
           }
       }

       //Convert successors to ch
       ch.push_back(points[0]);

       //Second point of CH
       int index = n[0];

       //Repeat until the first point is found
       while(index != 0)
       {
           //Add to the polygon
           ch.push_back(points[index]);

           //Find its successor
           index = n[index];
       }

    return ch;
}


QPolygon Algorithms::removeDuplicate(QPolygon &points)
{
    //Correct points
    QPolygon points_c;

    //Sort by X
    std::sort(points.begin(), points.end(), sortByX());
    int n = points.size();
    int i = 0;
    //Finding duplicate points
    while (i < n)
    {
        int dx = points[i].x();
        while ((dx == points[i%n].x()) && (i < n))
        {
            if ((points[i].y() != points[(i+1)%n].y()))
                points_c.push_back(points[i]);
            i++;
        }
    }
    //Retrun correct points
    return points_c;
}





