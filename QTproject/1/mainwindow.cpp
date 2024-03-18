#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //数据
    m_Data = new ClassData();

    //串口
    m_serialData = new QSerialPort();

    //时间
    m_timerAutoGetData = new QTimer();

    //文件
    m_qstrConfigFilePath.append(QString(QDir::currentPath() + "/cconfig.ini"));
    readINIFile();//读取INI文件
    writeINIFile();//写入INI文件

    //更新页面
    connect(this, SIGNAL(signal_newDataArrived()), this, SLOT(slot_updateUI()));

    //报警事件处理器
    ui->imageSwitchAlarm->installEventFilter(this);

    //串口获取
    connect(m_timerAutoUpdateSerial, SIGNAL(timeout()), this, SLOT(slot_updateSerialInfo()));
    m_timerAutoUpdateSerial->start(1000);

    //时间获取
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slot_timerUpdate()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//*************************更新界面*************************//
void MainWindow::slot_updateUI()
{
    ui->gaugeSimpleHumidity->setValue(m_Data->getHumidity());
    ui->gaugeSimpleTemperature->setValue(m_Data->getTemperature());
    ui->gaugeSimpleWindSpeed->setValue(m_Data->getWindSpeed());
    ui->gaugeCompassPanWindDirectionIcon->setValue(m_Data->getWindDirection());

    ui->navLabelPressure->setText(QString::number(m_Data->getPressure(),'f',3));
    ui->navLabelIllumination->setText(QString::number(m_Data->getIllumination()));
    ui->navLabelAltitude->setText(QString::number(m_Data->getAltitude()));

    ui->waveChartTemperature->addData(m_Data->getTemperature());
    ui->waveChartHumidity->addData(m_Data->getHumidity());
    ui->waveChartIllumination->addData(m_Data->getIllumination() / 1000);
    ui->waveChartWindSpeed->addData(m_Data->getWindSpeed());

    ui->labelHumidity->setText(QString::number(m_Data->getHumidity()));
    ui->labelTemperature->setText(QString::number(m_Data->getTemperature()));
    ui->labelWindSpeed->setText(QString::number(m_Data->getWindSpeed()));
}

//*************************时间功能*************************//
void MainWindow::slot_timerUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString Calendar = time.toString("yyyy-MM-dd");
    ui->labelCalendar->setText(Calendar);
    QString Time = time.toString("hh:mm:ss");
    ui->labelTime->setText(Time);
    QString Week = time.toString("dddd");
    ui->labelWeek->setText(Week);
}

//*************************日志功能*************************//
//日志打印
void MainWindow::printLog(QString log1, QString log2)
{
    QString time = QDateTime::currentDateTime().time().toString();//获取当前时间
    QString log = QString("%1 %2 %3").arg(time).arg(log1).arg(log2);
    ui->textEditLog->append(log);
}

//清除日志
void MainWindow::on_pushButtonClearLog_clicked()
{
    ui->textEditLog->clear();
}

//*************************菜单功能*************************//
//读取数据
void MainWindow::on_menuGetHardwareData_triggered()
{
    on_pushButtonGetHardwareData_clicked();
}

//随机数据
void MainWindow::on_menuGetRandomData_triggered()
{
    on_pushButtonGetRandomData_clicked();
}

//输入数据
void MainWindow::on_menuGetInputData_triggered()
{
    on_pushButtonGetInputData_clicked();
}

//关闭页面
void MainWindow::on_menuClose_triggered()
{
    this->close();
}

//关于
void MainWindow::on_menuAbout_triggered()
{
    QMessageBox::information(this,"关于","简易气象站\r\n(／(･ᴗ･)＼)\r\n");
}

//写入INI文件
void MainWindow::on_writeINIFile_triggered()
{
    writeINIFile();
}

//读取INI文件
void MainWindow::on_readINIFile_triggered()
{
    readINIFile();
}

//*************************报警功能*************************//
//报警
void MainWindow::slot_alarm()
{
    int nAlarmFlag = 0;
    if(m_Data->getTemperature() > ui->xsliderTemperatureLimit->value())
    {
        nAlarmFlag = 1;
        printLog("温度过高");
    }
    if(m_Data->getIllumination() > ui->xsliderIlluminationLimit->value())
    {
        nAlarmFlag = 1;
        printLog("光照度过高");
    }
    if(m_Data->getWindSpeed() > ui->xsliderWindSpeedLimit->value())
    {
        nAlarmFlag = 1;
        printLog("风速过高");
    }
    if(nAlarmFlag == 1)
    {
        ui->lightPoint->setBgColor(QColor(255, 0, 0));//指示灯设为红色
        ui->lightPoint->setStep(10);                  //指示灯闪烁
    }
    else
    {
        ui->lightPoint->setBgColor(QColor(0, 255, 0));//指示灯设为绿色
        ui->lightPoint->setStep(0);                   //指示灯停止闪烁
    }
}

//报警控制
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->imageSwitchAlarm)//是否是报警控件发生事件
    {
        if (event->type() == QEvent::MouseButtonPress)//是否是鼠标事件
        {
            QMouseEvent *event2 = static_cast<QMouseEvent *>(event);//将基类指针赋值给派生类指针
            if (event2->button() == Qt::LeftButton)//是否是左键单击
            {
                if (!ui->imageSwitchAlarm->getChecked())//如果启用了报警功能
                {
                    connect(this, SIGNAL(signal_newDataArrived()), this, SLOT(slot_alarm()));//连接槽函数
                    printLog("启用报警功能");
                }
                else
                {
                    disconnect(this, SIGNAL(signal_newDataArrived()),this, SLOT(slot_alarm()));//断开槽函数
                    ui->lightPoint->setBgColor(QColor(0, 255, 0));//关闭指示灯
                    ui->lightPoint->setStep(0);
                    printLog("关闭报警功能");
                }
            }
        }
    }
    return QObject::eventFilter(obj, event);
}

//*************************采集数据功能*************************//
//自动采集
void MainWindow::on_radioButtonAutoMode_clicked()
{
    connect(m_timerAutoGetData, SIGNAL(timeout()), this, SLOT(slot_autoGetData_Timeout()));
    m_timerAutoGetData->start(5000);
    printLog("自动采集");
}

//手动采集
void MainWindow::on_radioButtonManualMode_clicked()
{
    m_timerAutoGetData->stop();
    disconnect(m_timerAutoGetData, SIGNAL(timeout()), this, SLOT(slot_autoGetData_Timeout()));
    printLog("手动采集");
}

//数据处理
void MainWindow::slot_autoGetData_Timeout()
{
    on_pushButtonGetHardwareData_clicked();
}

//*************************串口功能*************************//
//定时串口更新
void MainWindow::slot_updateSerialInfo()
{
    if (QSerialPortInfo::availablePorts().count() == ui->comboBoxUart->count())//判断串口数量是否发生改变
    {
        return;
    }
    ui->comboBoxUart->clear();
    printLog("检测到串口信息：");
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->comboBoxUart->addItem(info.portName());
        printLog(info.portName(), info.description());
    }
    ui->comboBoxUart->model()->sort(0);//对串口列表进行排序
}

int m_nSerialWeatherOpenedFlag;
//串口开关
void MainWindow::on_pushButtonOpenUart_clicked()
{
    if (m_nSerialWeatherOpenedFlag == 0)
    {
        m_serialData->setPortName(ui->comboBoxUart->currentText());

        m_serialData->setBaudRate(ui->lineEditBaudRate->text().toInt());
        m_serialData->setDataBits(QSerialPort::Data8);
        m_serialData->setParity(QSerialPort::NoParity);
        m_serialData->setStopBits(QSerialPort::OneStop);
        m_serialData->setFlowControl(QSerialPort::NoFlowControl);
        m_serialData->open (QIODevice::ReadWrite);

        if (m_serialData->isOpen())
        {
            printLog("串口1己打开",ui->comboBoxUart->currentText());
            ui->pushButtonOpenUart->setText("关闭串口1");
            m_nSerialWeatherOpenedFlag = 1;
        }
        else
        {
            printLog("串口1打开失败");
        }
    }
    else
    {
        printLog("串口1已关闭");
        ui->pushButtonOpenUart->setText("打开串口1");
        m_nSerialWeatherOpenedFlag = 0;
        m_serialData->close();
    }
    if (m_nSerialWeatherOpenedFlag > 0)
    {
        disconnect(m_timerAutoUpdateSerial, SIGNAL(timeout()), this, SLOT(slot_updateSerialInfo()));
    }
    else
    {
        connect(m_timerAutoUpdateSerial, SIGNAL(timeout()), this, SLOT(slot_updateSerialInfo()));
    }
}

//*************************工作模式*************************//
//手动读取数据
void MainWindow::on_pushButtonGetHardwareData_clicked()
{
    int nDataValidFlag = -1;
    if (m_nSerialWeatherOpenedFlag == 1)
    {
        nDataValidFlag = m_Data->readSerialData(m_serialData);
    }
    if (nDataValidFlag == 0)
    {
        emit signal_newDataArrived();
    }
}

//生成模拟数据
void MainWindow::on_pushButtonGetRandomData_clicked()
{
    int nSeed = QDateTime::currentDateTime().toSecsSinceEpoch();
    QRandomGenerator generator(nSeed);

    m_Data->setIllumination(generator.bounded(0, 50000));
    m_Data->setTemperature(generator.bounded(-10, 50));
    m_Data->setPressure(generator.bounded(90000, 110000)/1000.0),
    m_Data->setHumidity(generator.bounded(0, 100));
    m_Data->setAltitude(generator.bounded(-200, 5000));

    m_Data->setWindSpeed(generator.bounded(0, 20));
    m_Data->setWindDirection(generator.bounded(0, 359));
}

//输入模拟数据
//打开子窗口
void MainWindow::on_pushButtonGetInputData_clicked()
{
    InputWindow *w = new InputWindow();//创建子窗口
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    connect(w, SIGNAL(signal_sendDataToMainWindow(int, ClassData &, ClassData &)), this, SLOT(slot_getInputData(int, ClassData &, ClassData &)));//连接槽函数
    w->show();//显示子窗口
    w->showDataFromMainWindow(*m_Data, *m_Data);//更新子窗口的数据
    ui->pushButtonGetInputData->setEnabled(0);
}

//子窗口数据获取
void MainWindow::slot_getInputData(int nFlag, ClassData &info39, ClassData &info3000)
{
    if(nFlag == 1)
    {
        m_Data->setIllumination(info39.getIllumination());
        m_Data->setTemperature(info39.getTemperature());
        m_Data->setPressure(info39.getPressure());
        m_Data->setHumidity(info39.getHumidity());
        m_Data->setAltitude(info39.getAltitude());
        m_Data->setWindSpeed(info3000.getWindSpeed());
        m_Data->setWindDirection(info3000.getWindDirection());
        emit signal_newDataArrived();
        printLog("输入成功");
    }
    ui->pushButtonGetInputData->setEnabled(1);
}

//*************************保存报警信息*************************//
//读取INI文件
void MainWindow::readINIFile()
{
    QSettings settings(m_qstrConfigFilePath, QSettings::Format::IniFormat);

    settings.beginGroup("Alarm");//进入报警限值节
    if (settings.contains("WindSpeed"))//存在风速值？
    {
        int nTemp = settings.value("WindSpeed").toInt();//读取键值
        ui->xsliderWindSpeedLimit->setValue(nTemp);//显示键值
    }
    else
    {
        ui->xsliderWindSpeedLimit->setValue(30);//使用默认值
    }
    if (settings.contains("Temperature"))//存在温度值？
    {
        int nTemp = settings.value("Temperature").toInt();//读取键值
        ui->xsliderTemperatureLimit->setValue(nTemp);//显示键值
    }
    else
    {
        ui->xsliderTemperatureLimit->setValue(30);//使用默认值
    }
    if (settings.contains("Illumination"))//存在光照值？
    {
        int nTemp = settings.value("Illumination").toInt();//读取键值
        ui->xsliderIlluminationLimit->setValue(nTemp);//显示键值
    }
    else
    {
        ui->xsliderIlluminationLimit->setValue(30);//使用默认值
    }
    printLog("读取INI文件成功");
    settings.endGroup();//退出报警限值节
}

//写入INI文件
void MainWindow::writeINIFile()
{
    QSettings settings(m_qstrConfigFilePath, QSettings::Format::IniFormat);

    settings.beginGroup("Alarm");//进入报警限值节
    settings.setValue("Windspeed",ui->xsliderWindSpeedLimit->value());
    settings.setValue("Temperature",ui->xsliderTemperatureLimit->value());
    settings.setValue("Illumination",ui->xsliderIlluminationLimit->value());
    printLog("写入INI文件成功");
    settings.endGroup();//退出报警限值节
}
