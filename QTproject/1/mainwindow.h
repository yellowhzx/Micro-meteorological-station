#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include <ClassData.h>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QEvent>
#include <QMouseEvent>
#include <QAbstractItemView>
#include <InputWindow.h>
#include <QRandomGenerator>
#include <QDir>
#include <QSettings>
#include <QIODevice>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static QList <QSerialPortInfo> availablePorts();

    void printLog(QString log1, QString log2 = " ");//日志打印
    void alarm();//标志位，不为零则需要报警
    void readINIFile();//读取INI文件
    void writeINIFile();//写入INI文件

private:
    Ui::MainWindow *ui;

    ClassData *m_Data;
    QSerialPort *m_serialData;
    QSerialPort *m_serialTime;
    QTimer *m_timerAutoGetData;
    QTimer *m_timerAutoUpdateSerial = new QTimer(this);
    QByteArray m_qstrConfigFilePath;//配置文件路径

public slots:
    void on_pushButtonOpenUart_clicked();
    void on_pushButtonGetHardwareData_clicked();
    void on_pushButtonClearLog_clicked();

    void on_menuClose_triggered();
    void on_menuAbout_triggered();
    void on_menuGetHardwareData_triggered();
    void on_menuGetRandomData_triggered();
    void on_menuGetInputData_triggered();

    void on_radioButtonAutoMode_clicked();
    void on_radioButtonManualMode_clicked();

    void on_pushButtonGetInputData_clicked();
    void on_pushButtonGetRandomData_clicked();

    void on_readINIFile_triggered();
    void on_writeINIFile_triggered();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void slot_alarm();
    void slot_updateUI();
    void slot_updateSerialInfo();
    void slot_timerUpdate();
    void slot_autoGetData_Timeout();
    void slot_getInputData(int nFlag, ClassData &info39, ClassData &info3000);

signals:
    void signal_newDataArrived();
};
#endif // MAINWINDOW_H
