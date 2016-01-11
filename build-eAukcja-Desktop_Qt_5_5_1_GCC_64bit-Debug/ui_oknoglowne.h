/********************************************************************************
** Form generated from reading UI file 'oknoglowne.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OKNOGLOWNE_H
#define UI_OKNOGLOWNE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OknoGlowne
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButton;
    QLabel *label_2;
    QPushButton *pushButton_2;
    QListWidget *listWidget;
    QPushButton *pushButton_3;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *OknoGlowne)
    {
        if (OknoGlowne->objectName().isEmpty())
            OknoGlowne->setObjectName(QStringLiteral("OknoGlowne"));
        OknoGlowne->resize(1115, 706);
        centralwidget = new QWidget(OknoGlowne);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 131, 18));
        QFont font;
        font.setPointSize(11);
        label->setFont(font);
        plainTextEdit = new QPlainTextEdit(centralwidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(284, 41, 811, 391));
        QFont font1;
        font1.setPointSize(12);
        plainTextEdit->setFont(font1);
        plainTextEdit->setFrameShadow(QFrame::Plain);
        plainTextEdit->setReadOnly(true);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(281, 631, 91, 26));
        pushButton->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(280, 20, 80, 18));
        label_2->setFont(font);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(11, 631, 128, 26));
        pushButton_2->setFont(font);
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(15, 40, 261, 581));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(970, 630, 121, 23));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(280, 440, 811, 181));
        OknoGlowne->setCentralWidget(centralwidget);
        menubar = new QMenuBar(OknoGlowne);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1115, 20));
        OknoGlowne->setMenuBar(menubar);
        statusbar = new QStatusBar(OknoGlowne);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        OknoGlowne->setStatusBar(statusbar);

        retranslateUi(OknoGlowne);

        QMetaObject::connectSlotsByName(OknoGlowne);
    } // setupUi

    void retranslateUi(QMainWindow *OknoGlowne)
    {
        OknoGlowne->setWindowTitle(QApplication::translate("OknoGlowne", "eAukcja", 0));
        label->setText(QApplication::translate("OknoGlowne", "Dost\304\231pne aukcje:", 0));
        pushButton->setText(QApplication::translate("OknoGlowne", "We\305\272 udzia\305\202", 0));
        label_2->setText(QApplication::translate("OknoGlowne", "Szczeg\303\263\305\202y:", 0));
        pushButton_2->setText(QApplication::translate("OknoGlowne", "Stw\303\263rz przetarg", 0));
        pushButton_3->setText(QApplication::translate("OknoGlowne", "Wybierz zwyci\304\231zc\304\231", 0));
    } // retranslateUi

};

namespace Ui {
    class OknoGlowne: public Ui_OknoGlowne {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OKNOGLOWNE_H
