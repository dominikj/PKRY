/********************************************************************************
** Form generated from reading UI file 'zlozoferte.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZLOZOFERTE_H
#define UI_ZLOZOFERTE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_zlozOferte
{
public:
    QTableWidget *tableWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *zlozOferte)
    {
        if (zlozOferte->objectName().isEmpty())
            zlozOferte->setObjectName(QStringLiteral("zlozOferte"));
        zlozOferte->resize(414, 507);
        tableWidget = new QTableWidget(zlozOferte);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(30, 130, 361, 321));
        layoutWidget = new QWidget(zlozOferte);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 30, 361, 81));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        layoutWidget1 = new QWidget(zlozOferte);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(40, 460, 168, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget1);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        retranslateUi(zlozOferte);

        QMetaObject::connectSlotsByName(zlozOferte);
    } // setupUi

    void retranslateUi(QDialog *zlozOferte)
    {
        zlozOferte->setWindowTitle(QApplication::translate("zlozOferte", "Sk\305\202adanie oferty", 0));
        label->setText(QApplication::translate("zlozOferte", "Sk\305\202adasz swoj\304\205 ofert\304\231 w przetargu:", 0));
        label_2->setText(QApplication::translate("zlozOferte", "nazwa_przetargu", 0));
        label_3->setText(QApplication::translate("zlozOferte", "Data zako\305\204czenia:", 0));
        label_4->setText(QApplication::translate("zlozOferte", "data_zak", 0));
        pushButton->setText(QApplication::translate("zlozOferte", "Z\305\202\303\263\305\274 ofert\304\231", 0));
        pushButton_2->setText(QApplication::translate("zlozOferte", "Wr\303\263\304\207", 0));
    } // retranslateUi

};

namespace Ui {
    class zlozOferte: public Ui_zlozOferte {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZLOZOFERTE_H
