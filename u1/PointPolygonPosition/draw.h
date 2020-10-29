#ifndef DRAW_H
#define DRAW_H

#include <vector>
#include <QWidget>
#include <QtGui>

class Draw : public QWidget
{
    Q_OBJECT
private:
    bool draw_mode;  //true = polygon, false = point
    std::vector <QPoint> polygon;
    QPoint q;
    std::vector<int> result;
    std::vector<QPolygonF> polygons;

public:
    explicit Draw(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    QPoint & getPoint(){return q;}
    void loadPolygon(std::string &path);
    void setPolygon(std::vector<int> res){result=res;}
    std::vector<QPolygonF> getPolygons(){return polygons;}

};

#endif // DRAW_H
