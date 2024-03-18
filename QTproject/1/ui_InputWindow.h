/********************************************************************************
** Form generated from reading UI file 'InputWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTWINDOW_H
#define UI_INPUTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InputWindow
{
public:
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_3;
    QLineEdit *lineEditTemperature;
    QLineEdit *lineEditHumidity;
    QLineEdit *lineEditAltitude;
    QLineEdit *lineEditIllumination;
    QLineEdit *lineEditPressure;
    QLineEdit *lineEditWindSpeed;
    QLineEdit *lineEditWindDirection;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *InputWindow)
    {
        if (InputWindow->objectName().isEmpty())
            InputWindow->setObjectName(QString::fromUtf8("InputWindow"));
        InputWindow->resize(428, 226);
        label_8 = new QLabel(InputWindow);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 60, 91, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\226\260\351\255\217"));
        font.setPointSize(12);
        label_8->setFont(font);
        label_9 = new QLabel(InputWindow);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 100, 71, 16));
        label_9->setFont(font);
        label_10 = new QLabel(InputWindow);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 140, 101, 16));
        label_10->setFont(font);
        label_11 = new QLabel(InputWindow);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 180, 111, 16));
        label_11->setFont(font);
        label_12 = new QLabel(InputWindow);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(240, 20, 81, 16));
        label_12->setFont(font);
        label_13 = new QLabel(InputWindow);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(240, 60, 71, 16));
        label_13->setFont(font);
        label_3 = new QLabel(InputWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 20, 71, 16));
        label_3->setFont(font);
        lineEditTemperature = new QLineEdit(InputWindow);
        lineEditTemperature->setObjectName(QString::fromUtf8("lineEditTemperature"));
        lineEditTemperature->setGeometry(QRect(120, 20, 91, 21));
        lineEditTemperature->setFont(font);
        lineEditTemperature->setLayoutDirection(Qt::LeftToRight);
        lineEditTemperature->setEchoMode(QLineEdit::Normal);
        lineEditTemperature->setAlignment(Qt::AlignCenter);
        lineEditHumidity = new QLineEdit(InputWindow);
        lineEditHumidity->setObjectName(QString::fromUtf8("lineEditHumidity"));
        lineEditHumidity->setGeometry(QRect(120, 60, 91, 21));
        lineEditHumidity->setFont(font);
        lineEditHumidity->setLayoutDirection(Qt::LeftToRight);
        lineEditHumidity->setEchoMode(QLineEdit::Normal);
        lineEditHumidity->setAlignment(Qt::AlignCenter);
        lineEditAltitude = new QLineEdit(InputWindow);
        lineEditAltitude->setObjectName(QString::fromUtf8("lineEditAltitude"));
        lineEditAltitude->setGeometry(QRect(120, 100, 91, 21));
        lineEditAltitude->setFont(font);
        lineEditAltitude->setLayoutDirection(Qt::LeftToRight);
        lineEditAltitude->setEchoMode(QLineEdit::Normal);
        lineEditAltitude->setAlignment(Qt::AlignCenter);
        lineEditIllumination = new QLineEdit(InputWindow);
        lineEditIllumination->setObjectName(QString::fromUtf8("lineEditIllumination"));
        lineEditIllumination->setGeometry(QRect(120, 140, 91, 21));
        lineEditIllumination->setFont(font);
        lineEditIllumination->setLayoutDirection(Qt::LeftToRight);
        lineEditIllumination->setEchoMode(QLineEdit::Normal);
        lineEditIllumination->setAlignment(Qt::AlignCenter);
        lineEditPressure = new QLineEdit(InputWindow);
        lineEditPressure->setObjectName(QString::fromUtf8("lineEditPressure"));
        lineEditPressure->setGeometry(QRect(120, 180, 91, 21));
        lineEditPressure->setFont(font);
        lineEditPressure->setLayoutDirection(Qt::LeftToRight);
        lineEditPressure->setEchoMode(QLineEdit::Normal);
        lineEditPressure->setAlignment(Qt::AlignCenter);
        lineEditWindSpeed = new QLineEdit(InputWindow);
        lineEditWindSpeed->setObjectName(QString::fromUtf8("lineEditWindSpeed"));
        lineEditWindSpeed->setGeometry(QRect(330, 20, 91, 21));
        lineEditWindSpeed->setFont(font);
        lineEditWindSpeed->setLayoutDirection(Qt::LeftToRight);
        lineEditWindSpeed->setEchoMode(QLineEdit::Normal);
        lineEditWindSpeed->setAlignment(Qt::AlignCenter);
        lineEditWindDirection = new QLineEdit(InputWindow);
        lineEditWindDirection->setObjectName(QString::fromUtf8("lineEditWindDirection"));
        lineEditWindDirection->setGeometry(QRect(330, 60, 91, 21));
        lineEditWindDirection->setFont(font);
        lineEditWindDirection->setLayoutDirection(Qt::LeftToRight);
        lineEditWindDirection->setEchoMode(QLineEdit::Normal);
        lineEditWindDirection->setAlignment(Qt::AlignCenter);
        pushButtonOK = new QPushButton(InputWindow);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(240, 172, 75, 31));
        pushButtonCancel = new QPushButton(InputWindow);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(330, 172, 75, 31));

        retranslateUi(InputWindow);

        QMetaObject::connectSlotsByName(InputWindow);
    } // setupUi

    void retranslateUi(QDialog *InputWindow)
    {
        InputWindow->setWindowTitle(QCoreApplication::translate("InputWindow", "Dialog", nullptr));
        label_8->setText(QCoreApplication::translate("InputWindow", "\346\271\277\345\272\246(%RH)\357\274\232", nullptr));
        label_9->setText(QCoreApplication::translate("InputWindow", "\346\265\267\346\213\224(m)\357\274\232", nullptr));
        label_10->setText(QCoreApplication::translate("InputWindow", "\345\205\211\347\205\247\345\272\246(kLux)\357\274\232", nullptr));
        label_11->setText(QCoreApplication::translate("InputWindow", "\346\260\224\345\216\213(kPa)\357\274\232", nullptr));
        label_12->setText(QCoreApplication::translate("InputWindow", "\351\243\216\351\200\237(m/s)\357\274\232", nullptr));
        label_13->setText(QCoreApplication::translate("InputWindow", "\351\243\216\345\220\221(\302\260)\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("InputWindow", "\346\270\251\345\272\246(\342\204\203)\357\274\232", nullptr));
        lineEditTemperature->setText(QCoreApplication::translate("InputWindow", "9600", nullptr));
        lineEditHumidity->setText(QCoreApplication::translate("InputWindow", "9600", nullptr));
        lineEditAltitude->setText(QCoreApplication::translate("InputWindow", "9600", nullptr));
        lineEditIllumination->setText(QCoreApplication::translate("InputWindow", "9600", nullptr));
        lineEditPressure->setText(QCoreApplication::translate("InputWindow", "9600", nullptr));
        lineEditWindSpeed->setText(QCoreApplication::translate("InputWindow", "9600", nullptr));
        lineEditWindDirection->setText(QCoreApplication::translate("InputWindow", "9600", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("InputWindow", "\347\241\256\345\256\232", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("InputWindow", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputWindow: public Ui_InputWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTWINDOW_H
