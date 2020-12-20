#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <vector>
#include <QtGui>
#include <fstream>

#include "qpoint3d.h"
#include "edge.h"
#include "triangle.h"
#include "widget.h"

class Draw : public QWidget
{
    Q_OBJECT

private:
    std::vector <QPoint3D> points;
    std::vector <Edge> dt;
    std::vector <Edge> contours, label_contours, main_contours;
    std::vector <Triangle> dtm, aspect_dtm;
    int style;

public:
    explicit Draw(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void setPoints(std::vector<QPoint3D> &points_){points=points_;}
    std::vector<QPoint3D> & getPoints(){return points;}
    void setDT(std::vector<Edge> &dt_){dt = dt_;}
    std::vector<Edge> & getDT(){return dt;}
    void setContours(std::vector<Edge> &contours_){contours = contours_;}
    std::vector<Edge> & getContours(){return contours;}
    void setDTM(std::vector<Triangle> &dtm_){dtm = dtm_;}
    std::vector<Triangle> & getDTM(){return dtm;}
    void loadFile(std::string &path);
    void setMainContours(std::vector<Edge> &main_contours_){main_contours = main_contours_;}
    void setLabelContours(std::vector<Edge> &label_contours_){label_contours = label_contours_;}
    std::vector<Edge>& getMainContours() {return main_contours;}
    std::vector<Edge>& getContoursLabel() {return label_contours;}
    void setAspectDTM(std::vector<Triangle> &aspect_dtm_){aspect_dtm = aspect_dtm_;}
    std::vector<Triangle>&getAspectDTM() {return aspect_dtm;}
    void setStyle (int style_){style=style_;}

signals:

public slots:
};

#endif // DRAW_H
