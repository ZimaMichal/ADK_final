#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <vector>
#include <QtGui>

class Draw : public QWidget
{
    Q_OBJECT
private:
    QPolygon points;     //Input points
    QPolygon ch;                    //Convex Hull

public:
    explicit Draw(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    QPolygon getPoints(){return points;}
    QPolygon getCH() {return ch;}
    void setCH(QPolygon &ch_){ch = ch_;}
    void setPoints(QPolygon Points){points = Points;}
    QPolygon generateRandom(int n, int height, int width);
    void clearCH(){ch.clear(); repaint();}
    void clearPoints(){points.clear(); repaint();}
    QPolygon generateGrid(int n, int height, int width);
    QPolygon generateCircle(int n, int height, int width);
signals:

};

#endif // DRAW_H

