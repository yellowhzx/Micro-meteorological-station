#include <ClassData.h>

//*************************数据*************************//
//光照度
float ClassData::getIllumination()
{
   return m_nIllumination;
}
void ClassData::setIllumination(int nIllumi)
{
    m_nIllumination = nIllumi;
}
//温度
float ClassData::getTemperature()
{
   return m_fTemperature;
}
void ClassData::setTemperature(float fTemp)
{
    m_fTemperature = fTemp;
}
//气压
float ClassData::getPressure()
{
    return m_fPressure;
}
void ClassData::setPressure(float fPres)
{
    m_fPressure = fPres;
}
//湿度
float ClassData::getHumidity()
{
   return m_nHumidity;
}
void ClassData::setHumidity(int nHumi)
{
    m_nHumidity = nHumi;
}
//海拔
int ClassData::getAltitude()
{
   return m_nAltitude;
}
void ClassData::setAltitude(int nAlti)
{
    m_nAltitude = nAlti;
}
//风速
float ClassData::getWindSpeed()
{
    return m_fWindSpeed;
}
void ClassData::setWindSpeed(float fWS)
{
    m_fWindSpeed = fWS;
}
//风向
int ClassData::getWindDirection()
{
    return m_nWindDirection;
}
void ClassData::setWindDirection(int nWD)
{
    m_nWindDirection = nWD;
}

//*************************GY39*************************//
//GY39校验数据
int ClassData::verifySerialData(QByteArray qbaSerialData)
{
    unsigned int nSum = 0;//保存求和结果
    foreach(char cTmp, qbaSerialData.left(8))//开始校验光照强度数据
    {
        nSum += cTmp;//进行累加操作
    }
    if((nSum % 256) != (unsigned char)qbaSerialData.at(8))//求和结果是否等于校验位
    {
        return -1;//不等于则返回-1，等于则继续
    }
    nSum=0;//求和结果清零
    foreach(char cTmp, qbaSerialData.right(15).left(14))//开始校验气象数据
    {
        nSum += cTmp;//进行累加操作
    }
    if ((nSum % 256) != (unsigned char)qbaSerialData.at(23))//求和结果是否等于校验位
    {
        return -2;//不等于则返回-2，等于则继续
    }
    return 0;
}

//GY39处理数据
int ClassData::parseSerialData(QByteArray qbaSerialData)
{
    unsigned char *cData = (unsigned char *)qbaSerialData.data();//转换为无符号数组

    float nIllumi = ((cData[4] << 24) + (cData[5] << 16) + (cData[6] << 8) + cData[7]) / 100;//光照数据恒正，采用无符号的数据进行计算
    float fTemp = ((qbaSerialData[13] << 8) + cData[14]) / 100.0; //温度数据高字节采用有符号的数据计算，低字节采用无符号的数据计算
    float fPre =((cData[15] << 24) + (cData[16] << 16) + (cData[17] << 8) + cData [18]) / 100.0 / 1000.0;
    float nHum =((cData[19] << 8) + cData[20]) / 100.0;
    int nAlti =(qbaSerialData[21] << 8) + cData[22];

    setIllumination(nIllumi);
    setTemperature (fTemp);
    setPressure(fPre);
    setHumidity(nHum);
    setAltitude(nAlti);

    return 0;
}

//*************************PR3000*************************//
//风速风向CRC校验
int ClassData::crc16Verify(QByteArray qbaData, QByteArray qbaCheckSum)
{
    quint16 data8, crc16 = 0xFFFF;

    for (int i = 0; i < qbaData.size(); i++)
    {
        data8 = qbaData.at(i) & 0x00FF;
        crc16 ^= data8;
        for (int j= 0; j<8; j++)
        {
            if (crc16 & 0x0001)
            {
                crc16 >>= 1;
                crc16 ^= 0xA001;
            }
            else
            {
                crc16 >>= 1;
            }
        }
    }
    crc16 = (crc16 >> 8) + (crc16 << 8);

    if ((crc16 / 256) == (unsigned char) qbaCheckSum.at(0))
    {
        if ((crc16 % 256) == (unsigned char) qbaCheckSum.at(1))
        {
            return 0;
        }
    }
    return 1;
}

//*************************读取数据*************************//
int ClassData::readSerialData(QSerialPort *serialPort)
{
    QEventLoop eventLoop;//定义事件循环
    QTimer::singleShot(5000, &eventLoop, SLOT(quit()));
    eventLoop.exec();

    QByteArray qbaData = serialPort->readAll();

    if(qbaData.length() % 40 != 0)//判断数据长度
        return -1;

    if(verifySerialData(qbaData.mid(0, 24)) != 0)//GY39数据校验
        return -2;
    parseSerialData(qbaData.mid(0, 24));//GY39数据处理

    //风速数据处理
    if (0 != crc16Verify(qbaData.mid(24, 5), qbaData.mid(29, 2)) && qbaData.at(24) != 0x01)
        return -1;
    float fWindSpeed = (qbaData.at(27) * 256 + qbaData.at(28)) / 10.0;
    setWindSpeed(fWindSpeed);

    //风向数据处理
    if (0 != crc16Verify(qbaData.mid(31, 7), qbaData.mid(38, 2)) && qbaData.at(31) != 0x02)
        return -1;
    int nWindDirection;
    switch (qbaData.at(35)) {
        case 0x00: nWindDirection = 0;break;
        case 0x01: nWindDirection = 45;break;
        case 0x02: nWindDirection = 90;break;
        case 0x03: nWindDirection = 135;break;
        case 0x04: nWindDirection = 180;break;
        case 0x05: nWindDirection = 225;break;
        case 0x06: nWindDirection = 270;break;
        case 0x07: nWindDirection = 315;break;
    }
    setWindDirection(nWindDirection);

    QDateTime time = QDateTime::currentDateTime();
    QString timeString = time.toString("yyyy-MM-dd hh:mm:ss");
    QByteArray timeData = timeString.toUtf8();
//    serialPort->write(timeData);

    return 0;
}
