#include "draw.h"
#include <algorithms.h>
#include <QDebug>
#include "widget.h"
#include <cmath>
#include <QRandomGenerator>

Draw::Draw(QWidget *parent) : QWidget(parent)
{

}
void Draw::mousePressEvent(QMouseEvent *e)
{
    //Get coordinates
    int x = e->x();
    int y = e->y();

    //Add point to the list
    QPoint p(x,y);
    points.push_back(p);

    //Repaint
    repaint();

}


void Draw::paintEvent(QPaintEvent *e)
{
    //Start draw
    QPainter qp(this);
    qp.begin(this);

    //Draw points
    int r = 2;
    for(int i = 0; i < points.size(); i++)
    {
        qp.drawEllipse(points[i].x() - r,points[i].y() - r, 2 * r, 2 * r);
    }

    //Coloured line
    qp.setPen(Qt::cyan);
    qp.drawPolygon(ch);
    //End draw
    qp.end();
}

QPolygon Draw::generateRandom(int n, int height, int width)
{
    Algorithms alg;
    QPolygon random_points;
    QPoint q;

    for (int i = 0; i < n; i++)
    {
        q.setX(QRandomGenerator::global()->bounded(10, width - 10));
        q.setY(QRandomGenerator::global()->bounded(10, height - 10));
        random_points.push_back(q);
    }
    random_points = alg.removeDuplicate(random_points);
    qDebug()<< random_points.size();

    return random_points;
}

QPolygon Draw::generateGrid(int n, int height, int width)
{
    QPolygon random_points;
    QPoint q;
    q.setX((width - height)/2);
    q.setY(10);

    for (int i = 0; i < n; i++)
    {
        for (int i = 0; i < n; i++)
        {
            q.setX((q.x()) + (height - 10)/n);
            random_points.push_back(q);
        }
        q.setX((width - height)/2);
        q.setY((q.y()) + (height - 10)/n);
    }

    random_points = Algorithms::removeDuplicate(random_points);
    qDebug()<< random_points.size();
    return random_points;
}

QPolygon Draw::generateCircle(int n, int height, int width)
{
    QPolygon random_points;
    QPoint s, q;
    s.setX(width/2);
    s.setY(height/2);
    double fi = 2 * M_PI / n;

    for (int i = 0; i < n; i++)
    {
         q.setX(s.x() + (height/2 - 10) * cos(fi*i));
         q.setY(s.y() + (height/2 - 10) * sin(fi*i));
         random_points.push_back(q);
    }

    random_points = Algorithms::removeDuplicate(random_points);
    qDebug()<< random_points.size();

    return random_points;
}
