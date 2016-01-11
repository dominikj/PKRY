/********************************************************************************
** Form generated from reading UI file 'nowaaukcja.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOWAAUKCJA_H
#define UI_NOWAAUKCJA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NowaAukcja
{
public:
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QTextEdit *textEdit;
    QLabel *label_3;
    QDateTimeEdit *dateTimeEdit;
    QLabel *label_4;
    QDateTimeEdit *dateTimeEdit_2;
    QLabel *label_5;
    QListWidget *listWidget;
    QLabel *label_6;
    QLineEdit *lineEdit_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QLabel *label_7;

    void setupUi(QDialog *NowaAukcja)
    {
        if (NowaAukcja->objectName().isEmpty())
            NowaAukcja->setObjectName(QStringLiteral("NowaAukcja"));
        NowaAukcja->resize(433, 541);
        pushButton_2 = new QPushButton(NowaAukcja);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(40, 500, 80, 23));
        pushButton_3 = new QPushButton(NowaAukcja);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(120, 500, 80, 23));
        layoutWidget = new QWidget(NowaAukcja);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 40, 381, 401));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        textEdit = new QTextEdit(layoutWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, textEdit);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        dateTimeEdit = new QDateTimeEdit(layoutWidget);
        dateTimeEdit->setObjectName(QStringLiteral("dateTimeEdit"));
        dateTimeEdit->setCalendarPopup(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, dateTimeEdit);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        dateTimeEdit_2 = new QDateTimeEdit(layoutWidget);
        dateTimeEdit_2->setObjectName(QStringLiteral("dateTimeEdit_2"));
        dateTimeEdit_2->setCalendarPopup(true);

        formLayout->setWidget(4, QFormLayout::FieldRole, dateTimeEdit_2);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_5);

        listWidget = new QListWidget(layoutWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        formLayout->setWidget(5, QFormLayout::FieldRole, listWidget);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_6);

        lineEdit_2 = new QLineEdit(layoutWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_2);

        layoutWidget1 = new QWidget(NowaAukcja);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(30, 450, 371, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_4 = new QPushButton(layoutWidget1);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout->addWidget(pushButton_4);

        label_7 = new QLabel(NowaAukcja);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 10, 221, 21));

        retranslateUi(NowaAukcja);

        QMetaObject::connectSlotsByName(NowaAukcja);
    } // setupUi

    void retranslateUi(QDialog *NowaAukcja)
    {
        NowaAukcja->setWindowTitle(QApplication::translate("NowaAukcja", "Stw\303\263rz nowy przetarg", 0));
        pushButton_2->setText(QApplication::translate("NowaAukcja", "Stw\303\263rz", 0));
        pushButton_3->setText(QApplication::translate("NowaAukcja", "Wr\303\263\304\207", 0));
        label->setText(QApplication::translate("NowaAukcja", "Nazwa przetargu:", 0));
        label_2->setText(QApplication::translate("NowaAukcja", "Opis przetargu:", 0));
        label_3->setText(QApplication::translate("NowaAukcja", "Data rozpocz\304\231cia:", 0));
        label_4->setText(QApplication::translate("NowaAukcja", "Data zako\305\204czenia:", 0));
        label_5->setText(QApplication::translate("NowaAukcja", "Kryteria przetargu:", 0));
        label_6->setText(QApplication::translate("NowaAukcja", "Numer przetargu:", 0));
        pushButton->setText(QApplication::translate("NowaAukcja", "Dodaj nowe kryterium", 0));
        pushButton_4->setText(QApplication::translate("NowaAukcja", "Usu\305\204 zaznaczone", 0));
        label_7->setText(QApplication::translate("NowaAukcja", "Podaj dane tworzonego przetargu:", 0));
    } // retranslateUi

};

namespace Ui {
    class NowaAukcja: public Ui_NowaAukcja {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOWAAUKCJA_H
