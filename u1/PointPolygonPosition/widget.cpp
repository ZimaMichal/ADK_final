#include "widget.h"
#include "algorithms.h"
#include "ui_widget.h"
#include "draw.h"
#include <QFileDialog>
#include <QFile>
#include <fstream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}


Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QString path(QFileDialog::getOpenFileName(this, tr("Open file with polygons"), "../", tr("Text Files (*.txt)")));
    std::string path_std = path.toStdString();
    ui->Canvas->loadPolygon(path_std);
}


void Widget::on_pushButton_2_clicked()
{
    //Analyze point and polygon position
    QPointF q = ui->Canvas->getPoint();
    std::vector<QPolygonF> polygons = ui->Canvas->getPolygons();
    std::vector<int> result;
    int p = 0;
    std::vector<QPointF> pol;
    QPolygonF one_polygon;
    int res = 0;
    Algorithms alg;

    //Get one polygon
    for (unsigned int j = 0; j < polygons.size(); j++) {
        one_polygon = polygons[j];
        for (int  i= 0; i< one_polygon.size(); i++) {

            pol.push_back(one_polygon[i]);

        }

        for (unsigned int k = 0; k < pol.size(); k++) {
            if (q == pol[k])
                p += 1;
        }

            //Select method
            if (ui->comboBox->currentIndex() == 0)
            {
                res = alg.getPositionWinding(q,pol);
            }
            else
                res = alg.getPositionRay(q,pol);
            result.push_back(res);


        int position = 0;
        int position_vertex = 0;

        for(unsigned int i = 0; i < result.size(); i++)
        {
            if(result[i] == -2)
                position_vertex += 1;
            if(result[i] == -1)
                position = -result.size()-10;
            if(result[i] == 1)
            {
              position += 1;

             }
            else
              position += 0;
        }
        //Print results
        if (position_vertex >0)
            ui->label->setText("Point on the vertex of polygon");
        else if (position < 0)
                ui->label->setText("Point on the edge");
        else if (position > 0)
                ui->label->setText("Inside");
        else
                ui->label->setText("Outside");

        pol.clear();
        p=0;
    }



    ui->Canvas->setPolygon(result);

    ui->Canvas->repaint();

}
