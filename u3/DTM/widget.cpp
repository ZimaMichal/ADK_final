#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"
#include "triangle.h"
#include "draw.h"
#include <QFileDialog>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    z_min = 0;
    z_max = 500;
    dz = 10;
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_7_clicked()
{
    //Create contour lines
    Algorithms a;
    std::vector<Edge> dt;
    std::vector<QPoint3D> points=ui->Canvas->getPoints();
    if (points.empty())
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Load points from file");
            messageBox.setFixedSize(500,200);
        }
        else
    {
    //DT needs to be created
    if(dt.size() == 0)
    {
        //Get points
        std::vector<QPoint3D> points = ui->Canvas->getPoints();

        //Create DT
        dt = a.DT(points);

        //Set DT
        ui->Canvas->setDT(dt);
    }

    //Create contour lines
    std::vector<Edge> contours = a.contourLines(dt, z_min, z_max, dz);
    std::vector<Edge> main_contours = a.contourLines(dt, z_min, z_max, dz * 5);

    //Set contours
    ui->Canvas->setContours(contours);
    ui->Canvas->setMainContours(main_contours);

    //Repaint
    repaint();
}
}


void Widget::on_pushButton_11_clicked()
{
    //Get points
    std::vector<QPoint3D> &points = ui->Canvas->getPoints();

    //Clear points
    points.clear();

    //Repaint
    repaint();
}


void Widget::on_pushButton_12_clicked()
{
    //Get DT and contours
    std::vector<Edge> &dt = ui->Canvas->getDT();
    std::vector<Edge> &contours = ui->Canvas->getContours();
    std::vector<Edge> &main_contours = ui->Canvas->getMainContours();
    std::vector<Edge> &label_contours = ui->Canvas->getContoursLabel();

    //Clear DT and contour lines, main contour and contour label
    dt.clear();
    contours.clear();
    main_contours.clear();
    label_contours.clear();

    //Repaint
    repaint();
}

void Widget::on_lineEdit_editingFinished()
{
    //Set z_min
    z_min = ui -> lineEdit -> text().toDouble();
}


void Widget::on_lineEdit_2_editingFinished()
{
    //Set z_max
    z_max = ui -> lineEdit_2 -> text().toDouble();
}


void Widget::on_lineEdit_3_editingFinished()
{
    //Set dz
    dz = ui -> lineEdit_3 -> text().toDouble();
}


void Widget::on_pushButton_2_clicked()
{
    int style;
    if (ui->comboBox->currentIndex()==0)
    {
        style = 1;
    }
    else if (ui->comboBox->currentIndex()==1)
    {
        style = 2;
    }
    else if (ui->comboBox->currentIndex()==2)
    {
        style = 3;
    }
    else
        style = 4;
    ui->Canvas->setStyle(style);

    Algorithms a;
    std::vector<Edge> dt;
    std::vector<QPoint3D> points=ui->Canvas->getPoints();
    if (points.empty())
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Load points from file");
            messageBox.setFixedSize(500,200);
        }
        else
    {
    //DT needs to be created
    if(dt.size() == 0)
    {
        //Get points
        std::vector<QPoint3D> points = ui->Canvas->getPoints();

        //Create DT
        dt = a.DT(points);

        //Set DT
        ui->Canvas->setDT(dt);
    }

    //Analyze DTM
    std::vector<Triangle> dtm = a.analyzeDTM(dt);

    //Set analysis
    ui->Canvas->setDTM(dtm);

    //Repaint
    repaint();
}
}


void Widget::on_pushButton_3_clicked()
{
    //Clear DTM analysis
    std::vector<Edge> &dt = ui->Canvas->getDT();
    std::vector<Triangle> &dtm = ui->Canvas->getDTM();

    //Clear DTM
    dt.clear();
    dtm.clear();

    //Repaint
    repaint();
}


void Widget::on_pushButton_4_clicked()
{
    //Get all
    std::vector<QPoint3D> &points = ui->Canvas->getPoints();
    std::vector<Edge> &dt = ui->Canvas->getDT();
    std::vector<Edge> &contours = ui->Canvas->getContours();
    std::vector<Triangle> &dtm = ui->Canvas->getDTM();
    std::vector<Edge> &main_contours = ui->Canvas->getMainContours();
    std::vector<Edge> &label_contours = ui->Canvas->getContoursLabel();
    std::vector<Triangle> &aspect_dtm = ui->Canvas->getAspectDTM();

    //Clear all
    points.clear();
    dt.clear();
    contours.clear();
    dtm.clear();
    main_contours.clear();
    label_contours.clear();
    aspect_dtm.clear();

    //Repaint
    repaint();
}

void Widget::on_pushButton_clicked()
{
    //Get all
    std::vector<QPoint3D> &points = ui->Canvas->getPoints();
    std::vector<Edge> &dt = ui->Canvas->getDT();
    std::vector<Edge> &contours = ui->Canvas->getContours();
    std::vector<Triangle> &dtm = ui->Canvas->getDTM();
    std::vector<Edge> &main_contours = ui->Canvas->getMainContours();
    std::vector<Edge> &label_contours = ui->Canvas->getContoursLabel();
    std::vector<Triangle> &aspect_dtm = ui->Canvas->getAspectDTM();

    //Clear all
    points.clear();
    dt.clear();
    contours.clear();
    dtm.clear();
    main_contours.clear();
    label_contours.clear();
    aspect_dtm.clear();

    QString path(QFileDialog::getOpenFileName(this, tr("Open file with points"), "../", tr("Text Files (*.txt)")));
    std::string path_std = path.toStdString();
    ui->Canvas->loadFile(path_std);
}

void Widget::on_pushButton_5_clicked()
{
    std::vector<Edge> label_contours = ui->Canvas->getMainContours();

    ui->Canvas->setLabelContours(label_contours);
    repaint();

}

void Widget::on_pushButton_6_clicked()
{
    int style;
    if (ui->comboBox->currentIndex()==0)
    {
        style = 1;
    }
    else if (ui->comboBox->currentIndex()==1)
    {
        style = 2;
    }
    else if (ui->comboBox->currentIndex()==2)
    {
        style = 3;
    }
    else
        style = 4;
    ui->Canvas->setStyle(style);


    std::vector<Edge> dt;

    //Create triangulation

    std::vector<QPoint3D> points = ui->Canvas->getPoints();

    if (points.empty())
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Load points from file");
            messageBox.setFixedSize(500,200);
        }
        else
    {
    Algorithms a;
    dt = a.DT(points);
    ui->Canvas->setDT(dt);
    //Analyze DTM aspect
    std::vector<Triangle> aspect_dtm = a.analyzeDTM(dt);
    ui->Canvas->setAspectDTM(aspect_dtm);
    repaint();
    }
}

void Widget::on_pushButton_8_clicked()
{
    //Clear DTM Aspect
    std::vector<Triangle> &aspect_dtm = ui->Canvas->getAspectDTM();
    aspect_dtm.clear();

    //Repaint
    repaint();
}
