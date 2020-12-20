#include "draw.h"
#include "widget.h"

Draw::Draw(QWidget *parent) : QWidget(parent)
{

}

void Draw::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.begin(this);

    //Draw points
    for (int i = 0; i < points.size(); i++)
    {
        painter.drawEllipse(points[i].x() - 5, points[i].y() - 5, 10, 10);
    }

    //Draw Delaunay edges
    QPen p(Qt::green, 1);
    painter.setPen(p);

    for (int i = 0; i < dt.size(); i++)
    {
        painter.drawLine(dt[i].getStart(), dt[i].getEnd());
    }

    //Draw slope
    double k = 255/180.0;
    for (Triangle t : dtm)
    {

        //Get triangle vertices
        QPoint3D p1 = t.getP1();
        QPoint3D p2 = t.getP2();
        QPoint3D p3 = t.getP3();

        //Get slope
        int colorSlope;
        if (style == 1) //gray scale
        {
            colorSlope = 255 - t.getSlope()*k;

            //Create color and set brush
            QColor c(colorSlope,colorSlope,colorSlope, 120);
            painter.setBrush(c);
        }

        else if (style == 2) //blue scale
        {
            double slope=t.getSlope();
            //Set color brush

            if(((slope>=0.0) && (slope<15.0)))
            {
                QColor d(51, 51, 255, 140);
                painter.setBrush(d);
            }
            else if((slope>=15.0) && (slope<30.0))
            {
                QColor d(0, 0, 255, 140);
                painter.setBrush(d);
            }
            else if((slope>=30.0) && (slope<45.0))
            {
                QColor d(0, 0, 204, 140);
                painter.setBrush(d);
            }
            else if((slope>=45.0) && (slope<60.0))
            {
                QColor d(0, 0, 153, 140);
                painter.setBrush(d);
            }
            else if(((slope>=60.0) && (slope<75.0)))
            {
                QColor d(0, 0, 102, 140);
                painter.setBrush(d);
            }
            else if((slope>=75.0) && (slope<90.0))
            {
                QColor d(0, 0, 51, 140);
                painter.setBrush(d);
            }
        }

        else if (style == 3) // green scale
        {
            double slope=t.getSlope();
            //Set color brush

            if(((slope>=0.0) && (slope<15.0)))
            {
                QColor d(102, 255, 102, 140);
                painter.setBrush(d);
            }
            else if((slope>=15.0) && (slope<30.0))
            {
                QColor d(0, 255, 0, 140);
                painter.setBrush(d);
            }
            else if((slope>=30.0) && (slope<45.0))
            {
                QColor d(0, 204, 0, 140);
                painter.setBrush(d);
            }
            else if((slope>=45.0) && (slope<60.0))
            {
                QColor d(0, 153, 0, 140);
                painter.setBrush(d);
            }
            else if(((slope>=60.0) && (slope<75.0)))
            {
                QColor d(0, 102, 0, 140);
                painter.setBrush(d);
            }
            else if((slope>=75.0) && (slope<90.0))
            {
                QColor d(0, 51, 0, 140);
                painter.setBrush(d);
            }
        }
        else
        {
            double slope=t.getSlope();
            //Set color brush

            if(((slope>=0.0) && (slope<15.0)))
            {
                QColor d(0, 255, 0, 120);
                painter.setBrush(d);
            }
            else if((slope>=15.0) && (slope<30.0))
            {
                QColor d(255, 255, 0, 120);
                painter.setBrush(d);
            }
            else if((slope>=30.0) && (slope<45.0))
            {
                QColor d(255, 0, 0, 120);
                painter.setBrush(d);
            }
            else if((slope>=45.0) && (slope<60.0))
            {
                QColor d(255, 0, 255, 120);
                painter.setBrush(d);
            }
            else if(((slope>=60.0) && (slope<75.0)))
            {
                QColor d(0, 0, 255, 120);
                painter.setBrush(d);
            }
            else if((slope>=75.0) && (slope<90.0))
            {
                QColor d(0, 255, 255, 120);
                painter.setBrush(d);
            }
        }
        //Create triangle, add vertices
        QPolygonF triangle;
        triangle.append(QPointF(p1.x(), p1.y()));
        triangle.append(QPointF(p2.x(), p2.y()));
        triangle.append(QPointF(p3.x(), p3.y()));

        //Draw triangle
        painter.drawPolygon(triangle);

    }

    //Draw countour lines
    QPen q(Qt::gray, 1);
    painter.setPen(q);

    for (int i = 0; i < contours.size(); i++)
    {
        painter.drawLine(contours[i].getStart(), contours[i].getEnd());
    }

    //Draw main contour lines
    QPen q2(Qt::gray, 2);
    painter.setPen(q2);

    for (int i = 0; i < main_contours.size(); i++)
    {
        painter.drawLine(main_contours[i].getStart(), main_contours[i].getEnd());
    }

    //Draw contour labels
    QPen r(Qt::gray, 1);
    painter.setPen(r);

    for (int i = 0; i < label_contours.size(); i++)
    {
        Edge one_contour = label_contours[i];
        QPoint3D label_point1 = one_contour.getStart();
        QPoint3D label_point2 = one_contour.getEnd();
        QPointF label_point;
        label_point.setX((label_point1.x() + label_point2.x()) / 2);
        label_point.setY((label_point1.y() + label_point2.y()) / 2);
        double z = label_point1.getZ();
        QString z_string = QString::number(z);
        painter.drawText(label_point, z_string);
    }

    //Draw aspect
    for (Triangle t : aspect_dtm)
    {
        //Get triangle vertices
        QPoint3D p1 = t.getP1();
        QPoint3D p2 = t.getP2();
        QPoint3D p3 = t.getP3();
        double aspect = t.getAspect();

        //Set color brush
        if (style == 1) //gray scale
        {
            if(((aspect>=0.0) && (aspect<22.5)) || ((aspect>=-22.5) && (aspect<=0.0)))
            {
                QColor d(26, 26, 26, 120);
                painter.setBrush(d);
            }
            else if((aspect>=22.5) && (aspect<67.5))
            {
                QColor d(51, 51, 51, 120);
                painter.setBrush(d);
            }
            else if((aspect>=67.5) && (aspect<112.5))
            {
                QColor d(77, 77, 77, 120);
                painter.setBrush(d);
            }
            else if((aspect>=112.5) && (aspect<157.5))
            {
                QColor d(102, 102, 102, 120);
                painter.setBrush(d);
            }
            else if(((aspect>=157.5) && (aspect<180.0)) || ((aspect>=-180.0) && (aspect<-157.5)) )
            {
                QColor d(128, 128, 128, 120);
                painter.setBrush(d);
            }
            else if((aspect>=-157.5) && (aspect<-112.5))
            {
                QColor d(153, 153, 153, 120);
                painter.setBrush(d);
            }
            else if((aspect>=-112.5) && (aspect<-67.5))
            {
                QColor d(179, 179, 179, 120);
                painter.setBrush(d);
            }
            else if((aspect>=-67.5) && (aspect<-22.5))
            {
                QColor d(204, 204, 204, 120);
                painter.setBrush(d);
            }
        }

        else if (style == 2) //blue scale
        {
            if(((aspect>=0.0) && (aspect<22.5)) || ((aspect>=-22.5) && (aspect<=0.0)))
            {
                QColor d(0, 0, 51, 120);
                painter.setBrush(d);
            }
            else if((aspect>=22.5) && (aspect<67.5))
            {
                QColor d(0, 0, 102, 120);
                painter.setBrush(d);
            }
            else if((aspect>=67.5) && (aspect<112.5))
            {
                QColor d(0, 0, 153, 120);
                painter.setBrush(d);
            }
            else if((aspect>=112.5) && (aspect<157.5))
            {
                QColor d(0, 0, 204, 120);
                painter.setBrush(d);
            }
            else if(((aspect>=157.5) && (aspect<180.0)) || ((aspect>=-180.0) && (aspect<-157.5)) )
            {
                QColor d(0, 0, 255, 120);
                painter.setBrush(d);
            }
            else if((aspect>=-157.5) && (aspect<-112.5))
            {
                QColor d(51, 51, 255, 120);
                painter.setBrush(d);
            }
            else if((aspect>=-112.5) && (aspect<-67.5))
            {
                QColor d(102, 102, 255, 120);
                painter.setBrush(d);
            }
            else if((aspect>=-67.5) && (aspect<-22.5))
            {
                QColor d(153, 153, 255, 120);
                painter.setBrush(d);
            }
        }

        else if (style == 3) // green scale
        {
            if(((aspect>=0.0) && (aspect<22.5)) || ((aspect>=-22.5) && (aspect<=0.0)))
            {
                QColor d(0, 51, 0, 120);
                painter.setBrush(d);
            }
            else if((aspect>=22.5) && (aspect<67.5))
            {
                QColor d(0, 102, 0, 120);
                painter.setBrush(d);
            }
            else if((aspect>=67.5) && (aspect<112.5))
            {
                QColor d(0, 153, 0, 120);
                painter.setBrush(d);
            }
            else if((aspect>=112.5) && (aspect<157.5))
            {
                QColor d(0, 204, 0, 120);
                painter.setBrush(d);
            }
            else if(((aspect>=157.5) && (aspect<180.0)) || ((aspect>=-180.0) && (aspect<-157.5)) )
            {
                QColor d(0, 255, 0, 120);
                painter.setBrush(d);
            }
            else if((aspect>=-157.5) && (aspect<-112.5))
            {
                QColor d(51, 255, 51, 120);
                painter.setBrush(d);
            }
            else if((aspect>=-112.5) && (aspect<-67.5))
            {
                QColor d(102, 255, 102, 120);
                painter.setBrush(d);
            }
            else if((aspect>=-67.5) && (aspect<-22.5))
            {
                QColor d(153, 255, 153, 120);
                painter.setBrush(d);
            }
        }
        else //Al lcolours
        {
        if(((aspect>=0.0) && (aspect<22.5)) || ((aspect>=-22.5) && (aspect<=0.0)))
        {
            QColor d(0, 255, 0, 120);
            painter.setBrush(d);
        }
        else if((aspect>=22.5) && (aspect<67.5))
        {
            QColor d(255, 255, 0, 120);
            painter.setBrush(d);
        }
        else if((aspect>=67.5) && (aspect<112.5))
        {
            QColor d(255, 165, 0, 120);
            painter.setBrush(d);
        }
        else if((aspect>=112.5) && (aspect<157.5))
        {
            QColor d(255, 0, 0, 120);
            painter.setBrush(d);
        }
        else if(((aspect>=157.5) && (aspect<180.0)) || ((aspect>=-180.0) && (aspect<-157.5)) )
        {
            QColor d(255, 0, 255, 120);
            painter.setBrush(d);
        }
        else if((aspect>=-157.5) && (aspect<-112.5))
        {
            QColor d(139, 0, 255, 120);
            painter.setBrush(d);
        }
        else if((aspect>=-112.5) && (aspect<-67.5))
        {
            QColor d(0, 255, 255, 120);
            painter.setBrush(d);
        }
        else if((aspect>=-67.5) && (aspect<-22.5))
        {
            QColor d(0, 0, 255, 120);
            painter.setBrush(d);
        }
        }

        //Create polygon
        QPolygonF triangle_asp;
        triangle_asp.append(QPointF(p1.x(), p1.y()));
        triangle_asp.append(QPointF(p2.x(), p2.y()));
        triangle_asp.append(QPointF(p3.x(), p3.y()));

        painter.drawPolygon(triangle_asp);
}
    painter.end();
}



void Draw::mousePressEvent(QMouseEvent *event)
{
    //Get coordinates of cursor
    QPoint3D p;
    p.setX(event ->x());
    p.setY(event ->y());
    double random = std::rand() * 200.0 / RAND_MAX;
    p.setZ(random);

    //Add point to the list
    points.push_back(p);

    repaint();
};

void Draw::loadFile(std::string &path)
{
    points.clear();
    repaint();
    double x;
    double y;
    double z;

    //Load data from .txt file
    std::ifstream data(path);

    if(data.is_open())
    {
        //Fill the vectors
        while(data >> x >> y >> z)
        {
            QPoint3D point;
            point.setX(x);
            point.setY(y);
            point.setZ(z);
            points.push_back(point);
        }

        data.close();
    }
    repaint();
}
