#include "InputWindow.h"
#include "ui_InputWindow.h"

InputWindow::InputWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("输入模拟数据");
}

InputWindow::~InputWindow()
{
    delete ui;
}

//*************************子窗口功能*************************//
//子窗口中显示当前数据
void InputWindow::showDataFromMainWindow(ClassData &info39, ClassData &info3000)
{
    ui->lineEditIllumination->setText(QString::number(info39.getIllumination() / 1000));
    ui->lineEditTemperature->setText(QString::number(info39.getTemperature()));
    ui->lineEditPressure->setText(QString::number(info39.getPressure()));
    ui->lineEditHumidity->setText(QString::number(info39.getHumidity()));
    ui->lineEditAltitude->setText(QString::number(info39.getAltitude()));
    ui->lineEditWindSpeed->setText(QString::number(info3000.getWindSpeed()));
    ui->lineEditWindDirection->setText(QString::number(info3000.getWindDirection()));
}

//确定
void InputWindow::on_pushButtonOK_clicked()
{
    m_InputData.setIllumination(ui->lineEditIllumination->text().toInt() * 1000);
    m_InputData.setTemperature(ui->lineEditTemperature->text().toFloat());
    m_InputData.setPressure(ui->lineEditPressure->text().toFloat());
    m_InputData.setHumidity(ui->lineEditHumidity->text().toInt());
    m_InputData.setAltitude(ui->lineEditAltitude->text().toInt());
    m_InputData.setWindSpeed(ui->lineEditWindSpeed->text().toFloat());
    m_InputData.setWindDirection(ui->lineEditWindDirection->text().toFloat());
    emit signal_sendDataToMainWindow(1, m_InputData, m_InputData);
    this->close();
}

//取消
void InputWindow::on_pushButtonCancel_clicked()
{
    emit signal_sendDataToMainWindow(0, m_InputData, m_InputData);
    this->close();
}

//关闭
void InputWindow::closeEvent(QCloseEvent *event)
{
    emit signal_sendDataToMainWindow(0, m_InputData, m_InputData);
}
