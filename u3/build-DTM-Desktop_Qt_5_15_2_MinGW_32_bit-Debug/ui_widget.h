/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "draw.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QHBoxLayout *horizontalLayout;
    Draw *Canvas;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_7;
    QPushButton *pushButton_12;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pushButton_11;
    QPushButton *pushButton_4;
    QSpacerItem *verticalSpacer_6;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1062, 681);
        horizontalLayout = new QHBoxLayout(Widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Canvas = new Draw(Widget);
        Canvas->setObjectName(QString::fromUtf8("Canvas"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(Canvas->sizePolicy().hasHeightForWidth());
        Canvas->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(Canvas);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_3->addWidget(pushButton);

        verticalSpacer = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_3->addWidget(label);

        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout_3->addWidget(lineEdit);

        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_3->addWidget(label_2);

        lineEdit_2 = new QLineEdit(Widget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        verticalLayout_3->addWidget(lineEdit_2);

        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_3->addWidget(label_3);

        lineEdit_3 = new QLineEdit(Widget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        verticalLayout_3->addWidget(lineEdit_3);

        pushButton_7 = new QPushButton(Widget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        verticalLayout_3->addWidget(pushButton_7);

        pushButton_12 = new QPushButton(Widget);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));

        verticalLayout_3->addWidget(pushButton_12);

        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_3->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(Widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout_3->addWidget(pushButton_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);

        pushButton_11 = new QPushButton(Widget);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));

        verticalLayout_3->addWidget(pushButton_11);

        pushButton_4 = new QPushButton(Widget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        verticalLayout_3->addWidget(pushButton_4);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_6);


        horizontalLayout->addLayout(verticalLayout_3);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "DTM", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "Load points", nullptr));
        label->setText(QCoreApplication::translate("Widget", "Z_min [m]", nullptr));
        lineEdit->setText(QCoreApplication::translate("Widget", "0", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "Z_max [m]", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("Widget", "500", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "Interval z [m]", nullptr));
        lineEdit_3->setText(QCoreApplication::translate("Widget", "10", nullptr));
        pushButton_7->setText(QCoreApplication::translate("Widget", "Contour lines", nullptr));
        pushButton_12->setText(QCoreApplication::translate("Widget", "Clear contours", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "Analyze DTM", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Widget", "Clear analysis", nullptr));
        pushButton_11->setText(QCoreApplication::translate("Widget", "Clear Points", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Widget", "Clear all", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
