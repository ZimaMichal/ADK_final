#include "draw.h"
#include <fstream>
#include <QWidget>
#include <QtGui>
Draw::Draw(QWidget *parent) : QWidget(parent)
{
    //Set default draw mode
    draw_mode = true;

    //Draw point outside Canvas
    q.setX(-50);
    q.setY(-50);
}


void Draw::paintEvent(QPaintEvent *e)
{
    //Start drawing
    QPainter painter(this);
    painter.begin(this);
    //Draw loaded polygons
    for(unsigned int i = 0; i < polygons.size(); i++)
    {
        QPolygonF poly_in_polygons = polygons[i];
        painter.drawPolygon(poly_in_polygons);
    }
    //Set color of highlighted polygon
    QBrush brush;
    brush.setStyle(Qt::CrossPattern);
    QPainterPath path;
    QPolygonF highlighted_polygon;
    //Draw polygon with point inside
    for(unsigned int i = 0; i < result.size(); i++)
    {
        if(result[i] == 1)
        {   brush.setColor(Qt::cyan);
            highlighted_polygon << polygons[i];
            path.addPolygon(highlighted_polygon);
            painter.fillPath(path, brush);
            painter.drawPolygon(highlighted_polygon);
            highlighted_polygon.clear();
        }

        if(result[i] == -1)
        {
            brush.setColor(Qt::red);
            highlighted_polygon << polygons[i];
            path.addPolygon(highlighted_polygon);
            painter.fillPath(path, brush);
            painter.drawPolygon(highlighted_polygon);
            highlighted_polygon.clear();
        }

        if(result[i] == -2)
        {
            brush.setColor(Qt::red);
            highlighted_polygon << polygons[i];
            path.addPolygon(highlighted_polygon);
            painter.fillPath(path, brush);
            painter.drawPolygon(highlighted_polygon);
            highlighted_polygon.clear();
        }
    }
    //Draw q point
    int r = 5;
    painter.drawEllipse(q.x()-5, q.y()-5, 2 * r, 2 *r);
    //End drawing
    painter.end();
}
void Draw::mousePressEvent(QMouseEvent *e)
{
    //Cursor position
    double x = e->pos().x();
    double y = e->pos().y();

        //Change coordinates of q
        q.setX(x);
        q.setY(y);


    repaint();
}


void Draw::loadPolygon(std::string &path)
{
    polygons.clear();
    result.clear();
    repaint();
    int id;
    double x;
    double y;
    QPolygon polygon;

    //Load data form file
    std::ifstream data(path);

    if(data.is_open())
    {
        while(data >> id >> x>>y)
        {
            if (id==1)
            {
                if (polygon.isEmpty()==0)
                {
                    polygons.push_back(polygon);
                }
                polygon.clear();
                polygon <<QPoint(x,y);
            }
            else
                polygon <<QPoint(x,y);
        }
        polygons.push_back(polygon);

        data.close();
    }

    repaint();
}
