#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"

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
    Algorithms a;
    //Get points
    QPolygon points = ui->Canvas->getPoints();

    //Create Convex hull
    QPolygon ch;

    Algorithms alg;
    QElapsedTimer timer;
    timer.start();
    //Jarvis Scan
    if (ui->comboBox->currentIndex()==0)
        ch = alg.jarvis(points);

    //QHull
    else if (ui->comboBox->currentIndex()==1)
        ch = alg.qhull(points);

    //Sweep line
    else if (ui->comboBox->currentIndex()==2)
        ch = alg.sweepLine(points);

    //Graham scan
    else
        ch = alg.grahamScan(points);

    //Set Convex hull

    ui -> Canvas -> setCH(ch);
    //Repaint screen
    repaint();

    ui->label_3->setText("Time:" + QString::number(timer.elapsed()) + "ms");
}

void Widget::on_pushButton_2_clicked()
{
    //Clear CH
    ui->Canvas->clearCH();
}


void Widget::on_pushButton_4_clicked()
{
    QSize size = ui->Canvas->size();
    //Canvas height, width
    int height = size.height();
    int width = size.width();
    QPolygon random_points;
    int point_number = ui->lineEdit->text().toInt();

    //Random points
    if (ui->comboBox_2->currentIndex() == 0)
        random_points = ui->Canvas->generateRandom(point_number, height, width);
    //Grid
    if (ui->comboBox_2->currentIndex() == 1)
        random_points = ui->Canvas->generateGrid(point_number, height, width);
    //Circle
    if (ui->comboBox_2->currentIndex() == 2)
        random_points = ui->Canvas->generateCircle(point_number, height, width);
    //Show points
        ui->Canvas->setPoints(random_points);
        ui->Canvas->clearCH();
        ui->Canvas->repaint();


}

void Widget::on_pushButton_3_clicked()
{
    //Clear all
        ui->Canvas->clearPoints();
        ui->Canvas->clearCH();
        ui->Canvas->repaint();
}
