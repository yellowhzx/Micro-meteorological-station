#ifndef CLASSDATA_H
#define CLASSDATA_H
#include <QSerialPort>
#include <QByteArray>
#include <QEventLoop>
#include <QTimer>
#include <QDateTime>
#include <QObject>

class ClassData
{
private:
    float m_nIllumination = 0;//光照度，0~200000Lux
    float m_fTemperature = 0;//温度，-20~45℃
    float m_fPressure = 0;//气压，90~110kPa
    float m_nHumidity = 0;//湿度，0~100%RH
    int m_nAltitude = 0;//海拔，-200~9000m
    float m_fWindSpeed = 0;//风速
    int m_nWindDirection = 0;//风向

public:
    float getIllumination();
    void setIllumination(int nIllumi);
    float getTemperature();
    void setTemperature(float fTemp);
    float getPressure();
    void setPressure(float fPres);
    float getHumidity();
    void setHumidity(int nHumi);
    int getAltitude();
    void setAltitude(int nAlti);
    float getWindSpeed ();
    void setWindSpeed(float fWS);
    int getWindDirection();
    void setWindDirection(int nWD);

    int readSerialData(QSerialPort *serialPort);
    int verifySerialData(QByteArray qbaSerialData);
    int parseSerialData(QByteArray qbaSerialData);
    int crc16Verify(QByteArray qbaData, QByteArray qbaCheckSum);
};

#endif // CLASSDATA_H
