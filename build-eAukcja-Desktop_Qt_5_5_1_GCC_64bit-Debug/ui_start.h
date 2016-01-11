/********************************************************************************
** Form generated from reading UI file 'start.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_START_H
#define UI_START_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Start
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_5;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Start)
    {
        if (Start->objectName().isEmpty())
            Start->setObjectName(QStringLiteral("Start"));
        Start->resize(880, 567);
        centralWidget = new QWidget(Start);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 401, 101));
        QFont font;
        font.setPointSize(30);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 100, 471, 16));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(250, 230, 151, 121));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font1;
        font1.setPointSize(10);
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_4->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout->addWidget(label_4);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout->addWidget(label_3);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(420, 360, 168, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget1);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(420, 230, 241, 131));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEdit_3 = new QLineEdit(layoutWidget2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        verticalLayout_2->addWidget(lineEdit_3);

        lineEdit = new QLineEdit(layoutWidget2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout_2->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(layoutWidget2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        lineEdit_2->setMaxLength(50);
        lineEdit_2->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(lineEdit_2);

        Start->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Start);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 880, 20));
        Start->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Start);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Start->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Start);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Start->setStatusBar(statusBar);

        retranslateUi(Start);

        QMetaObject::connectSlotsByName(Start);
    } // setupUi

    void retranslateUi(QMainWindow *Start)
    {
        Start->setWindowTitle(QApplication::translate("Start", "eAukcja :: zaloguj", 0));
        label->setText(QApplication::translate("Start", "Witamy w eAukcji", 0));
        label_5->setText(QApplication::translate("Start", "Do zalgowania potrzebujesz adresu serwera oraz otrzymanych loginu i has\305\202a", 0));
        label_4->setText(QApplication::translate("Start", "Adres serwera:", 0));
        label_2->setText(QApplication::translate("Start", "Login:", 0));
        label_3->setText(QApplication::translate("Start", "Has\305\202o:", 0));
        pushButton->setText(QApplication::translate("Start", "Zaloguj", 0));
        pushButton_2->setText(QApplication::translate("Start", "Wyczy\305\233\304\207", 0));
    } // retranslateUi

};

namespace Ui {
    class Start: public Ui_Start {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_H
