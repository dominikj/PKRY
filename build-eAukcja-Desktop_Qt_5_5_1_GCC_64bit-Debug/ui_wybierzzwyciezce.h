/********************************************************************************
** Form generated from reading UI file 'wybierzzwyciezce.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WYBIERZZWYCIEZCE_H
#define UI_WYBIERZZWYCIEZCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WybierzZwyciezce
{
public:
    QLabel *label;
    QTextEdit *textEdit;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QPushButton *pushButton;

    void setupUi(QDialog *WybierzZwyciezce)
    {
        if (WybierzZwyciezce->objectName().isEmpty())
            WybierzZwyciezce->setObjectName(QStringLiteral("WybierzZwyciezce"));
        WybierzZwyciezce->resize(570, 561);
        label = new QLabel(WybierzZwyciezce);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 371, 16));
        textEdit = new QTextEdit(WybierzZwyciezce);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(20, 100, 501, 371));
        textEdit->setReadOnly(true);
        label_2 = new QLabel(WybierzZwyciezce);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 70, 59, 15));
        label_3 = new QLabel(WybierzZwyciezce);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 480, 121, 16));
        widget = new QWidget(WybierzZwyciezce);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 500, 501, 25));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);


        retranslateUi(WybierzZwyciezce);

        QMetaObject::connectSlotsByName(WybierzZwyciezce);
    } // setupUi

    void retranslateUi(QDialog *WybierzZwyciezce)
    {
        WybierzZwyciezce->setWindowTitle(QApplication::translate("WybierzZwyciezce", "Rozstrzygnij przetarg", 0));
        label->setText(QApplication::translate("WybierzZwyciezce", "Aukcja zako\305\204czona. Czas na wyb\303\263r najkorzystniejszej oferty.", 0));
        label_2->setText(QApplication::translate("WybierzZwyciezce", "Oferty:", 0));
        label_3->setText(QApplication::translate("WybierzZwyciezce", "Numer oferenta:", 0));
        pushButton->setText(QApplication::translate("WybierzZwyciezce", "Wybierz zwyci\304\231zc\304\231", 0));
    } // retranslateUi

};

namespace Ui {
    class WybierzZwyciezce: public Ui_WybierzZwyciezce {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WYBIERZZWYCIEZCE_H
