/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "gaugecompasspan.h"
#include "gaugesimple.h"
#include "imageswitch.h"
#include "lightpoint.h"
#include "navlabel.h"
#include "wavechart.h"
#include "xslider.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *readINIFile;
    QAction *writeINIFile;
    QAction *menuClose;
    QAction *menuGetRandomData;
    QAction *menuGetInputData;
    QAction *menuGetHardwareData;
    QAction *menuAbout;
    QWidget *centralwidget;
    QGroupBox *groupBoxUART;
    QLabel *label_7;
    QComboBox *comboBoxUart;
    QLabel *label_8;
    QLineEdit *lineEditBaudRate;
    QLabel *label_9;
    QPushButton *pushButtonOpenUart;
    QGroupBox *groupBox_2;
    QLabel *labelWeek;
    QLabel *labelCalendar;
    QLabel *labelTime;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox_3;
    QLabel *label_30;
    QLabel *labelTemperature;
    QLabel *label_3;
    QLabel *labelHumidity;
    QLabel *label_6;
    QLabel *label_25;
    QLabel *labelWindDirectionIcon;
    GaugeCompassPan *gaugeCompassPanWindDirectionIcon;
    QLabel *label_11;
    QLabel *label_34;
    QLabel *label_22;
    QLabel *labelWindSpeed;
    GaugeSimple *gaugeSimpleTemperature;
    GaugeSimple *gaugeSimpleHumidity;
    GaugeSimple *gaugeSimpleWindSpeed;
    NavLabel *navLabel;
    NavLabel *navLabelIllumination;
    NavLabel *navLabel_4;
    NavLabel *navLabelPressure;
    NavLabel *navLabel_7;
    NavLabel *navLabelAltitude;
    QGroupBox *groupBoxAlarm;
    QLabel *label_4;
    QLabel *label_19;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_26;
    QLabel *label_27;
    LightPoint *lightPoint;
    XSlider *xsliderWindSpeedLimit;
    XSlider *xsliderTemperatureLimit;
    XSlider *xsliderIlluminationLimit;
    ImageSwitch *imageSwitchAlarm;
    QGroupBox *groupBoxUART_2;
    QTextEdit *textEditLog;
    QPushButton *pushButtonClearLog;
    QGroupBox *groupBoxMode;
    QRadioButton *radioButtonManualMode;
    QRadioButton *radioButtonAutoMode;
    QPushButton *pushButtonGetInputData;
    QPushButton *pushButtonGetRandomData;
    QPushButton *pushButtonGetHardwareData;
    QWidget *tab2;
    WaveChart *waveChartTemperature;
    WaveChart *waveChartWindSpeed;
    WaveChart *waveChartHumidity;
    WaveChart *waveChartIllumination;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_D;
    QMenu *menu_A;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1069, 768);
        readINIFile = new QAction(MainWindow);
        readINIFile->setObjectName(QString::fromUtf8("readINIFile"));
        writeINIFile = new QAction(MainWindow);
        writeINIFile->setObjectName(QString::fromUtf8("writeINIFile"));
        menuClose = new QAction(MainWindow);
        menuClose->setObjectName(QString::fromUtf8("menuClose"));
        menuGetRandomData = new QAction(MainWindow);
        menuGetRandomData->setObjectName(QString::fromUtf8("menuGetRandomData"));
        menuGetInputData = new QAction(MainWindow);
        menuGetInputData->setObjectName(QString::fromUtf8("menuGetInputData"));
        menuGetHardwareData = new QAction(MainWindow);
        menuGetHardwareData->setObjectName(QString::fromUtf8("menuGetHardwareData"));
        menuAbout = new QAction(MainWindow);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBoxUART = new QGroupBox(centralwidget);
        groupBoxUART->setObjectName(QString::fromUtf8("groupBoxUART"));
        groupBoxUART->setGeometry(QRect(0, 0, 611, 111));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\226\260\351\255\217"));
        font.setPointSize(12);
        groupBoxUART->setFont(font);
        groupBoxUART->setAutoFillBackground(true);
        label_7 = new QLabel(groupBoxUART);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 50, 111, 16));
        label_7->setFont(font);
        comboBoxUart = new QComboBox(groupBoxUART);
        comboBoxUart->addItem(QString());
        comboBoxUart->addItem(QString());
        comboBoxUart->addItem(QString());
        comboBoxUart->addItem(QString());
        comboBoxUart->addItem(QString());
        comboBoxUart->setObjectName(QString::fromUtf8("comboBoxUart"));
        comboBoxUart->setGeometry(QRect(140, 50, 91, 21));
        comboBoxUart->setFont(font);
        label_8 = new QLabel(groupBoxUART);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(260, 50, 61, 16));
        label_8->setFont(font);
        lineEditBaudRate = new QLineEdit(groupBoxUART);
        lineEditBaudRate->setObjectName(QString::fromUtf8("lineEditBaudRate"));
        lineEditBaudRate->setGeometry(QRect(330, 50, 81, 21));
        lineEditBaudRate->setFont(font);
        lineEditBaudRate->setLayoutDirection(Qt::LeftToRight);
        lineEditBaudRate->setEchoMode(QLineEdit::Normal);
        lineEditBaudRate->setAlignment(Qt::AlignCenter);
        label_9 = new QLabel(groupBoxUART);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(420, 50, 31, 16));
        label_9->setFont(font);
        pushButtonOpenUart = new QPushButton(groupBoxUART);
        pushButtonOpenUart->setObjectName(QString::fromUtf8("pushButtonOpenUart"));
        pushButtonOpenUart->setGeometry(QRect(470, 50, 111, 23));
        pushButtonOpenUart->setFont(font);
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(610, 0, 191, 111));
        groupBox_2->setFont(font);
        groupBox_2->setAutoFillBackground(true);
        labelWeek = new QLabel(groupBox_2);
        labelWeek->setObjectName(QString::fromUtf8("labelWeek"));
        labelWeek->setGeometry(QRect(70, 80, 51, 21));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Agency FB"));
        font1.setPointSize(12);
        labelWeek->setFont(font1);
        labelWeek->setAlignment(Qt::AlignCenter);
        labelCalendar = new QLabel(groupBox_2);
        labelCalendar->setObjectName(QString::fromUtf8("labelCalendar"));
        labelCalendar->setGeometry(QRect(50, 10, 91, 21));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Agency FB"));
        font2.setPointSize(16);
        labelCalendar->setFont(font2);
        labelCalendar->setAlignment(Qt::AlignCenter);
        labelTime = new QLabel(groupBox_2);
        labelTime->setObjectName(QString::fromUtf8("labelTime"));
        labelTime->setGeometry(QRect(40, 40, 111, 31));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Agency FB"));
        font3.setPointSize(26);
        labelTime->setFont(font3);
        labelTime->setAlignment(Qt::AlignCenter);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 110, 801, 461));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        groupBox_3 = new QGroupBox(tab);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 0, 801, 201));
        groupBox_3->setFont(font);
        groupBox_3->setAutoFillBackground(true);
        label_30 = new QLabel(groupBox_3);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(130, 150, 21, 16));
        label_30->setFont(font);
        labelTemperature = new QLabel(groupBox_3);
        labelTemperature->setObjectName(QString::fromUtf8("labelTemperature"));
        labelTemperature->setGeometry(QRect(87, 150, 41, 16));
        labelTemperature->setFont(font);
        labelTemperature->setLayoutDirection(Qt::LeftToRight);
        labelTemperature->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 150, 41, 16));
        label_3->setFont(font);
        labelHumidity = new QLabel(groupBox_3);
        labelHumidity->setObjectName(QString::fromUtf8("labelHumidity"));
        labelHumidity->setGeometry(QRect(290, 150, 31, 16));
        labelHumidity->setFont(font);
        labelHumidity->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(250, 150, 41, 16));
        label_6->setFont(font);
        label_25 = new QLabel(groupBox_3);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(320, 150, 41, 16));
        label_25->setFont(font);
        labelWindDirectionIcon = new QLabel(groupBox_3);
        labelWindDirectionIcon->setObjectName(QString::fromUtf8("labelWindDirectionIcon"));
        labelWindDirectionIcon->setGeometry(QRect(720, 170, 21, 16));
        labelWindDirectionIcon->setFont(font);
        gaugeCompassPanWindDirectionIcon = new GaugeCompassPan(groupBox_3);
        gaugeCompassPanWindDirectionIcon->setObjectName(QString::fromUtf8("gaugeCompassPanWindDirectionIcon"));
        gaugeCompassPanWindDirectionIcon->setGeometry(QRect(630, 10, 161, 161));
        QFont font4;
        font4.setPointSize(12);
        gaugeCompassPanWindDirectionIcon->setFont(font4);
        gaugeCompassPanWindDirectionIcon->setBgColor(QColor(255, 255, 255));
        gaugeCompassPanWindDirectionIcon->setTextColor(QColor(50, 50, 50));
        gaugeCompassPanWindDirectionIcon->setBorderColor(QColor(100, 100, 100));
        gaugeCompassPanWindDirectionIcon->setNorthDotColor(QColor(255, 107, 107));
        gaugeCompassPanWindDirectionIcon->setOtherDotColor(QColor(0, 0, 0));
        gaugeCompassPanWindDirectionIcon->setPointerColor(QColor(100, 100, 100));
        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(670, 170, 41, 16));
        label_11->setFont(font);
        label_34 = new QLabel(groupBox_3);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setGeometry(QRect(550, 150, 31, 16));
        label_34->setFont(font);
        label_22 = new QLabel(groupBox_3);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(450, 150, 41, 16));
        label_22->setFont(font);
        labelWindSpeed = new QLabel(groupBox_3);
        labelWindSpeed->setObjectName(QString::fromUtf8("labelWindSpeed"));
        labelWindSpeed->setGeometry(QRect(497, 150, 51, 16));
        labelWindSpeed->setFont(font);
        labelWindSpeed->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        gaugeSimpleTemperature = new GaugeSimple(groupBox_3);
        gaugeSimpleTemperature->setObjectName(QString::fromUtf8("gaugeSimpleTemperature"));
        gaugeSimpleTemperature->setGeometry(QRect(10, 20, 171, 141));
        gaugeSimpleTemperature->setInputMethodHints(Qt::ImhNone);
        gaugeSimpleTemperature->setMaxValue(50.000000000000000);
        gaugeSimpleHumidity = new GaugeSimple(groupBox_3);
        gaugeSimpleHumidity->setObjectName(QString::fromUtf8("gaugeSimpleHumidity"));
        gaugeSimpleHumidity->setGeometry(QRect(220, 20, 171, 141));
        gaugeSimpleWindSpeed = new GaugeSimple(groupBox_3);
        gaugeSimpleWindSpeed->setObjectName(QString::fromUtf8("gaugeSimpleWindSpeed"));
        gaugeSimpleWindSpeed->setGeometry(QRect(430, 20, 171, 141));
        gaugeSimpleWindSpeed->setMaxValue(50.000000000000000);
        navLabel = new NavLabel(groupBox_3);
        navLabel->setObjectName(QString::fromUtf8("navLabel"));
        navLabel->setGeometry(QRect(230, 170, 161, 21));
        navLabel->setAlignment(Qt::AlignCenter);
        navLabel->setBackground(QColor(100, 100, 100));
        navLabel->setShowArrow(false);
        navLabelIllumination = new NavLabel(groupBox_3);
        navLabelIllumination->setObjectName(QString::fromUtf8("navLabelIllumination"));
        navLabelIllumination->setGeometry(QRect(290, 170, 71, 21));
        navLabelIllumination->setLayoutDirection(Qt::LeftToRight);
        navLabelIllumination->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        navLabelIllumination->setBackground(QColor(100, 100, 100));
        navLabelIllumination->setShowArrow(false);
        navLabel_4 = new NavLabel(groupBox_3);
        navLabel_4->setObjectName(QString::fromUtf8("navLabel_4"));
        navLabel_4->setGeometry(QRect(30, 170, 131, 21));
        navLabel_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        navLabel_4->setBackground(QColor(100, 100, 100));
        navLabel_4->setShowArrow(false);
        navLabelPressure = new NavLabel(groupBox_3);
        navLabelPressure->setObjectName(QString::fromUtf8("navLabelPressure"));
        navLabelPressure->setGeometry(QRect(80, 170, 51, 21));
        navLabelPressure->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        navLabelPressure->setBackground(QColor(100, 100, 100));
        navLabelPressure->setShowArrow(false);
        navLabel_7 = new NavLabel(groupBox_3);
        navLabel_7->setObjectName(QString::fromUtf8("navLabel_7"));
        navLabel_7->setGeometry(QRect(460, 170, 111, 21));
        navLabel_7->setBackground(QColor(100, 100, 100));
        navLabel_7->setShowArrow(false);
        navLabelAltitude = new NavLabel(groupBox_3);
        navLabelAltitude->setObjectName(QString::fromUtf8("navLabelAltitude"));
        navLabelAltitude->setGeometry(QRect(510, 170, 41, 21));
        navLabelAltitude->setBackground(QColor(100, 100, 100));
        navLabelAltitude->setShowArrow(false);
        gaugeSimpleWindSpeed->raise();
        gaugeCompassPanWindDirectionIcon->raise();
        gaugeSimpleHumidity->raise();
        gaugeSimpleTemperature->raise();
        label_30->raise();
        labelTemperature->raise();
        label_3->raise();
        labelHumidity->raise();
        label_6->raise();
        label_25->raise();
        labelWindDirectionIcon->raise();
        label_11->raise();
        label_34->raise();
        label_22->raise();
        labelWindSpeed->raise();
        navLabel->raise();
        navLabelIllumination->raise();
        navLabel_4->raise();
        navLabelPressure->raise();
        navLabel_7->raise();
        navLabelAltitude->raise();
        groupBoxAlarm = new QGroupBox(tab);
        groupBoxAlarm->setObjectName(QString::fromUtf8("groupBoxAlarm"));
        groupBoxAlarm->setGeometry(QRect(0, 200, 511, 121));
        groupBoxAlarm->setFont(font);
        groupBoxAlarm->setMouseTracking(false);
        groupBoxAlarm->setTabletTracking(false);
        groupBoxAlarm->setAcceptDrops(false);
        groupBoxAlarm->setAutoFillBackground(true);
        groupBoxAlarm->setFlat(false);
        groupBoxAlarm->setCheckable(false);
        groupBoxAlarm->setChecked(false);
        label_4 = new QLabel(groupBoxAlarm);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 30, 121, 16));
        QFont font5;
        font5.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\226\260\351\255\217"));
        font5.setPointSize(12);
        font5.setBold(false);
        font5.setWeight(50);
        label_4->setFont(font5);
        label_19 = new QLabel(groupBoxAlarm);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(20, 60, 121, 16));
        label_19->setFont(font);
        label_23 = new QLabel(groupBoxAlarm);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(20, 90, 121, 16));
        label_23->setFont(font);
        label_24 = new QLabel(groupBoxAlarm);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(350, 30, 31, 16));
        label_24->setFont(font5);
        label_26 = new QLabel(groupBoxAlarm);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(350, 60, 31, 16));
        label_26->setFont(font5);
        label_27 = new QLabel(groupBoxAlarm);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(350, 90, 31, 16));
        label_27->setFont(font5);
        lightPoint = new LightPoint(groupBoxAlarm);
        lightPoint->setObjectName(QString::fromUtf8("lightPoint"));
        lightPoint->setGeometry(QRect(410, 20, 91, 81));
        lightPoint->setStep(0);
        lightPoint->setBgColor(QColor(0, 255, 0, 0));
        xsliderWindSpeedLimit = new XSlider(groupBoxAlarm);
        xsliderWindSpeedLimit->setObjectName(QString::fromUtf8("xsliderWindSpeedLimit"));
        xsliderWindSpeedLimit->setGeometry(QRect(120, 20, 211, 36));
        xsliderWindSpeedLimit->setMaximum(50);
        xsliderWindSpeedLimit->setSliderHeight(13);
        xsliderWindSpeedLimit->setNormalColor(QColor(80, 80, 80));
        xsliderWindSpeedLimit->setGrooveColor(QColor(70, 70, 70));
        xsliderWindSpeedLimit->setHandleBorderColor(QColor(60, 60, 60));
        xsliderTemperatureLimit = new XSlider(groupBoxAlarm);
        xsliderTemperatureLimit->setObjectName(QString::fromUtf8("xsliderTemperatureLimit"));
        xsliderTemperatureLimit->setGeometry(QRect(120, 50, 211, 36));
        xsliderTemperatureLimit->setMaximum(50);
        xsliderTemperatureLimit->setSliderHeight(13);
        xsliderTemperatureLimit->setNormalColor(QColor(80, 80, 80));
        xsliderTemperatureLimit->setGrooveColor(QColor(70, 70, 70));
        xsliderTemperatureLimit->setHandleBorderColor(QColor(60, 60, 60));
        xsliderIlluminationLimit = new XSlider(groupBoxAlarm);
        xsliderIlluminationLimit->setObjectName(QString::fromUtf8("xsliderIlluminationLimit"));
        xsliderIlluminationLimit->setGeometry(QRect(120, 80, 211, 36));
        xsliderIlluminationLimit->setMaximum(1000);
        xsliderIlluminationLimit->setSliderHeight(13);
        xsliderIlluminationLimit->setNormalColor(QColor(80, 80, 80));
        xsliderIlluminationLimit->setGrooveColor(QColor(70, 70, 70));
        xsliderIlluminationLimit->setHandleBorderColor(QColor(60, 60, 60));
        imageSwitchAlarm = new ImageSwitch(groupBoxAlarm);
        imageSwitchAlarm->setObjectName(QString::fromUtf8("imageSwitchAlarm"));
        imageSwitchAlarm->setGeometry(QRect(80, 0, 51, 21));
        imageSwitchAlarm->setProperty("isChecked", QVariant(false));
        imageSwitchAlarm->setButtonStyle(ImageSwitch::ButtonStyle_2);
        groupBoxUART_2 = new QGroupBox(tab);
        groupBoxUART_2->setObjectName(QString::fromUtf8("groupBoxUART_2"));
        groupBoxUART_2->setGeometry(QRect(0, 320, 801, 111));
        groupBoxUART_2->setFont(font);
        groupBoxUART_2->setAutoFillBackground(true);
        textEditLog = new QTextEdit(groupBoxUART_2);
        textEditLog->setObjectName(QString::fromUtf8("textEditLog"));
        textEditLog->setGeometry(QRect(0, 20, 721, 81));
        QFont font6;
        font6.setPointSize(10);
        textEditLog->setFont(font6);
        pushButtonClearLog = new QPushButton(groupBoxUART_2);
        pushButtonClearLog->setObjectName(QString::fromUtf8("pushButtonClearLog"));
        pushButtonClearLog->setGeometry(QRect(720, 20, 71, 81));
        groupBoxMode = new QGroupBox(tab);
        groupBoxMode->setObjectName(QString::fromUtf8("groupBoxMode"));
        groupBoxMode->setGeometry(QRect(510, 200, 291, 121));
        groupBoxMode->setFont(font);
        groupBoxMode->setAutoFillBackground(true);
        radioButtonManualMode = new QRadioButton(groupBoxMode);
        radioButtonManualMode->setObjectName(QString::fromUtf8("radioButtonManualMode"));
        radioButtonManualMode->setGeometry(QRect(20, 40, 121, 16));
        radioButtonManualMode->setFont(font);
        radioButtonAutoMode = new QRadioButton(groupBoxMode);
        radioButtonAutoMode->setObjectName(QString::fromUtf8("radioButtonAutoMode"));
        radioButtonAutoMode->setGeometry(QRect(20, 80, 121, 16));
        radioButtonAutoMode->setFont(font);
        radioButtonAutoMode->setCheckable(true);
        radioButtonAutoMode->setChecked(false);
        pushButtonGetInputData = new QPushButton(groupBoxMode);
        pushButtonGetInputData->setObjectName(QString::fromUtf8("pushButtonGetInputData"));
        pushButtonGetInputData->setGeometry(QRect(150, 90, 121, 23));
        pushButtonGetInputData->setFont(font);
        pushButtonGetRandomData = new QPushButton(groupBoxMode);
        pushButtonGetRandomData->setObjectName(QString::fromUtf8("pushButtonGetRandomData"));
        pushButtonGetRandomData->setGeometry(QRect(150, 60, 121, 23));
        pushButtonGetRandomData->setFont(font);
        pushButtonGetHardwareData = new QPushButton(groupBoxMode);
        pushButtonGetHardwareData->setObjectName(QString::fromUtf8("pushButtonGetHardwareData"));
        pushButtonGetHardwareData->setGeometry(QRect(150, 30, 121, 23));
        pushButtonGetHardwareData->setFont(font);
        tabWidget->addTab(tab, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QString::fromUtf8("tab2"));
        waveChartTemperature = new WaveChart(tab2);
        waveChartTemperature->setObjectName(QString::fromUtf8("waveChartTemperature"));
        waveChartTemperature->setGeometry(QRect(0, 0, 401, 211));
        waveChartTemperature->setMaxValue(50.000000000000000);
        waveChartTemperature->setXStep(5.000000000000000);
        waveChartTemperature->setBgColorStart(QColor(235, 235, 235));
        waveChartTemperature->setBgColorEnd(QColor(225, 225, 225));
        waveChartTemperature->setTextColor(QColor(0, 0, 0));
        waveChartWindSpeed = new WaveChart(tab2);
        waveChartWindSpeed->setObjectName(QString::fromUtf8("waveChartWindSpeed"));
        waveChartWindSpeed->setGeometry(QRect(0, 210, 401, 211));
        waveChartWindSpeed->setMaxValue(50.000000000000000);
        waveChartWindSpeed->setXStep(5.000000000000000);
        waveChartWindSpeed->setBgColorStart(QColor(235, 235, 235));
        waveChartWindSpeed->setBgColorEnd(QColor(225, 225, 225));
        waveChartWindSpeed->setTextColor(QColor(0, 0, 0));
        waveChartHumidity = new WaveChart(tab2);
        waveChartHumidity->setObjectName(QString::fromUtf8("waveChartHumidity"));
        waveChartHumidity->setGeometry(QRect(400, 0, 401, 211));
        waveChartHumidity->setBgColorStart(QColor(235, 235, 235));
        waveChartHumidity->setBgColorEnd(QColor(225, 225, 225));
        waveChartHumidity->setTextColor(QColor(0, 0, 0));
        waveChartIllumination = new WaveChart(tab2);
        waveChartIllumination->setObjectName(QString::fromUtf8("waveChartIllumination"));
        waveChartIllumination->setGeometry(QRect(400, 210, 401, 211));
        waveChartIllumination->setMaxValue(30.000000000000000);
        waveChartIllumination->setXStep(3.000000000000000);
        waveChartIllumination->setBgColorStart(QColor(235, 235, 235));
        waveChartIllumination->setBgColorEnd(QColor(225, 225, 225));
        waveChartIllumination->setTextColor(QColor(0, 0, 0));
        tabWidget->addTab(tab2, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1069, 23));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_D = new QMenu(menubar);
        menu_D->setObjectName(QString::fromUtf8("menu_D"));
        menu_A = new QMenu(menubar);
        menu_A->setObjectName(QString::fromUtf8("menu_A"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_D->menuAction());
        menubar->addAction(menu_A->menuAction());
        menu->addAction(readINIFile);
        menu->addAction(writeINIFile);
        menu->addSeparator();
        menu->addAction(menuClose);
        menu_D->addAction(menuGetHardwareData);
        menu_D->addAction(menuGetRandomData);
        menu_D->addAction(menuGetInputData);
        menu_A->addAction(menuAbout);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        readINIFile->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226\351\205\215\347\275\256\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(shortcut)
        readINIFile->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        writeINIFile->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\351\205\215\347\275\256\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(shortcut)
        writeINIFile->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+D", nullptr));
#endif // QT_CONFIG(shortcut)
        menuClose->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
#if QT_CONFIG(shortcut)
        menuClose->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        menuGetRandomData->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\346\250\241\346\213\237\346\225\260\346\215\256", nullptr));
#if QT_CONFIG(shortcut)
        menuGetRandomData->setShortcut(QCoreApplication::translate("MainWindow", "W", nullptr));
#endif // QT_CONFIG(shortcut)
        menuGetInputData->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\346\250\241\346\213\237\346\225\260\346\215\256", nullptr));
#if QT_CONFIG(shortcut)
        menuGetInputData->setShortcut(QCoreApplication::translate("MainWindow", "E", nullptr));
#endif // QT_CONFIG(shortcut)
        menuGetHardwareData->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226\346\265\213\351\207\217\346\225\260\346\215\256", nullptr));
#if QT_CONFIG(shortcut)
        menuGetHardwareData->setShortcut(QCoreApplication::translate("MainWindow", "Q", nullptr));
#endif // QT_CONFIG(shortcut)
        menuAbout->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
#if QT_CONFIG(shortcut)
        menuAbout->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        groupBoxUART->setTitle(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\346\223\215\344\275\234", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\346\260\224\350\261\241\344\277\241\346\201\257\344\270\262\345\217\243\357\274\232", nullptr));
        comboBoxUart->setItemText(0, QCoreApplication::translate("MainWindow", "COM1", nullptr));
        comboBoxUart->setItemText(1, QCoreApplication::translate("MainWindow", "COM2", nullptr));
        comboBoxUart->setItemText(2, QCoreApplication::translate("MainWindow", "COM3", nullptr));
        comboBoxUart->setItemText(3, QCoreApplication::translate("MainWindow", "COM4", nullptr));
        comboBoxUart->setItemText(4, QCoreApplication::translate("MainWindow", "COM5", nullptr));

        label_8->setText(QCoreApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207\357\274\232", nullptr));
        lineEditBaudRate->setText(QCoreApplication::translate("MainWindow", "9600", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "bps", nullptr));
        pushButtonOpenUart->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\2431", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\346\227\266\351\227\264", nullptr));
        labelWeek->setText(QCoreApplication::translate("MainWindow", "\346\230\237\346\234\237\346\227\245", nullptr));
        labelCalendar->setText(QCoreApplication::translate("MainWindow", "2023-05-28", nullptr));
        labelTime->setText(QCoreApplication::translate("MainWindow", "00:00:00", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\346\260\224\350\261\241\344\277\241\346\201\257", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "\342\204\203", nullptr));
        labelTemperature->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\346\270\251\345\272\246\357\274\232", nullptr));
        labelHumidity->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\346\271\277\345\272\246\357\274\232", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "%RH", nullptr));
        labelWindDirectionIcon->setText(QCoreApplication::translate("MainWindow", "\345\214\227", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\351\243\216\345\220\221\357\274\232", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "m/s", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "\351\243\216\351\200\237\357\274\232", nullptr));
        labelWindSpeed->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        navLabel->setText(QCoreApplication::translate("MainWindow", "\345\205\211\347\205\247\345\272\246\357\274\232               lux", nullptr));
        navLabelIllumination->setText(QCoreApplication::translate("MainWindow", "0000.00", nullptr));
        navLabel_4->setText(QCoreApplication::translate("MainWindow", "\346\260\224\345\216\213\357\274\232             kPa", nullptr));
        navLabelPressure->setText(QCoreApplication::translate("MainWindow", "000.00", nullptr));
        navLabel_7->setText(QCoreApplication::translate("MainWindow", "\346\265\267\346\213\224\357\274\232          m", nullptr));
        navLabelAltitude->setText(QCoreApplication::translate("MainWindow", "0000", nullptr));
        groupBoxAlarm->setTitle(QCoreApplication::translate("MainWindow", "\346\212\245\350\255\246\346\216\247\345\210\266", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\351\243\216\351\200\237\344\270\212\351\231\220", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "\346\270\251\345\272\246\344\270\212\351\231\220", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "\345\205\211\347\205\247\345\272\246\344\270\212\351\231\220", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "m/s", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "\342\204\203", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "lux", nullptr));
        groupBoxUART_2->setTitle(QCoreApplication::translate("MainWindow", "\346\227\245\345\277\227", nullptr));
        pushButtonClearLog->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        groupBoxMode->setTitle(QCoreApplication::translate("MainWindow", "\345\267\245\344\275\234\346\250\241\345\274\217", nullptr));
        radioButtonManualMode->setText(QCoreApplication::translate("MainWindow", "\346\211\213\345\212\250\351\207\207\351\233\206\346\250\241\345\274\217", nullptr));
        radioButtonAutoMode->setText(QCoreApplication::translate("MainWindow", "\350\207\252\345\212\250\351\207\207\351\233\206\346\250\241\345\274\217", nullptr));
        pushButtonGetInputData->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\346\250\241\346\213\237\346\225\260\346\215\256", nullptr));
        pushButtonGetRandomData->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\346\250\241\346\213\237\346\225\260\346\215\256", nullptr));
        pushButtonGetHardwareData->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226\346\265\213\351\207\217\346\225\260\346\215\256", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\345\256\236\346\227\266\346\225\260\346\215\256", nullptr));
        waveChartTemperature->setTitle(QCoreApplication::translate("MainWindow", "\346\270\251\345\272\246()", nullptr));
        waveChartWindSpeed->setTitle(QCoreApplication::translate("MainWindow", "\351\243\216\351\200\237()", nullptr));
        waveChartHumidity->setTitle(QCoreApplication::translate("MainWindow", "\346\271\277\345\272\246()", nullptr));
        waveChartIllumination->setTitle(QCoreApplication::translate("MainWindow", "\345\205\211\347\205\247\345\272\246()", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QCoreApplication::translate("MainWindow", "\345\216\206\345\217\262\346\225\260\346\215\256", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266(F)", nullptr));
        menu_D->setTitle(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256(D)", nullptr));
        menu_A->setTitle(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216(A)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
