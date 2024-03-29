/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
/**USART1 GPIO Configuration
PA9     ------> USART1_TX
PA10     ------> USART1_RX
*/
/**USART2 GPIO Configuration
PA2     ------> USART2_TX
PA3     ------> USART2_RX
*/
/**USART3 GPIO Configuration
PA5     ------> USART3_TX
PB0     ------> USART3_RX
*/
/**USART4 GPIO Configuration
PA0     ------> USART4_TX
PA1     ------> USART4_RX
*/
#include "main.h"
#include "string.h"
#include "stdio.h"
#include "usart.h"
#include "delay.h"

#include "main_global.h"

RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;
TIM_HandleTypeDef htim14;
TIM_HandleTypeDef htim16;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart4;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USART4_UART_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM7_Init(void);
static void MX_TIM14_Init(void);
static void MX_TIM16_Init(void);
static void MX_RTC_Init(void);

uint8_t errorBuffer[]="\r\nerror\r\n"; //错误提示

uint8_t HMI_buf[1];
uint8_t HMI_data[24];
uint8_t HMI_send[24];

uint8_t raw_data[24]= {0};
uint8_t Receive_ok=0;//获取到的数据和接收完成标志位
uint8_t rx_buf;//接收缓存
uint8_t lora_slow=0;//数据减速
uint8_t lora_flag=1;//LORA标志位
uint8_t uart2_flag=0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    UNUSED(huart);

    if (huart->Instance == USART1)
    {
        HAL_UART_Receive_IT(&huart1, &rx_buf, sizeof(rx_buf));
        g_uart1RxBuffer[g_uart1RxBufferLen] = rx_buf;
        g_uart1RxBufferLen++;
    }

    if (huart->Instance == USART2)
    {
        HAL_UART_Receive_IT(&huart2, &rx_buf, sizeof(rx_buf));
        g_uart2RxBuffer[g_uart2RxBufferLen] = rx_buf;
        g_uart2RxBufferLen++;
    }

    if (huart->Instance == USART3)
    {
        HAL_UART_Receive_IT(&huart3, &rx_buf, sizeof(rx_buf));
        g_uart3RxBuffer[g_uart3RxBufferLen] = rx_buf;
        g_uart3RxBufferLen++;

        HMI_buf[0] = g_uart3RxBuffer[0];
    }

    if (huart->Instance == USART4)
    {
        HAL_UART_Receive_IT(&huart4, &rx_buf, sizeof(rx_buf));
        g_uart4RxBuffer[g_uart4RxBufferLen] = rx_buf;
        g_uart4RxBufferLen++;

        __HAL_TIM_CLEAR_FLAG(&htim6,TIM_FLAG_UPDATE);//清除TIM6中断标志
        HAL_TIM_Base_Start_IT(&htim6);//启动定时器
        __HAL_TIM_SET_COUNTER(&htim6,0);//定时器初值置零
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim==(&htim6))//GY39定时器获取数据
    {
        if (g_uart4RxBufferLen>0x18)//error
        {
            g_uart4RxBufferLen=0;
            memset(g_uart4RxBuffer,0,sizeof(g_uart4RxBufferLen));
            HAL_UART_Transmit(&huart1, (uint8_t *)errorBuffer,sizeof(errorBuffer),0xffff);
        }
        if (g_uart4RxBuffer[0]==0x5a && g_uart4RxBuffer[1]==0x5a && g_uart4RxBuffer[9]==0x5a && g_uart4RxBuffer[10]==0x5a)//帧头
        {
            if(g_uart4RxBufferLen!=0x18)//判断是否接收一帧数据完毕
                return;
            if(!Receive_ok)//当数据处理完成后才接收新的数据
            {
                memcpy(raw_data,g_uart4RxBuffer,24);//拷贝接收到的数据
                Receive_ok=1;//接收完成标志
            }
        }
        HAL_TIM_Base_Stop_IT(&htim6);//关闭定时
    }
}

//GY39获取数据
void send_com()//配置GY39
{
    uint8_t bytes[3]= {0};
    bytes[0]=0xa5;
    bytes[1]=0x83;
    bytes[2]=0x28;
    HAL_UART_Transmit(&huart4, bytes, 3, 0xffff);//发送帧头、功能字节、校验和
}

typedef struct
{
    uint16_t Lux; //光照
    uint32_t P;   //气压
    uint16_t Temp;//温度
    uint16_t Hum; //湿度
    uint16_t Alt; //海拔
} bme;

bme Bme= {0,0,0,0,0};

uint8_t lora_data[40];
uint8_t lora_GY39[24];
uint8_t lora_WS[7];
uint8_t lora_WD[9];

void GY39()
{
    uint8_t sum1=0,sum2,i=0;
    uint16_t data_16[2]= {0};

    if(Receive_ok)//串口接收完毕
    {
        for(sum1=0,i=0; i<8; i++) //判断光照是否正确
            sum1+=raw_data[i];
        for(sum2=0,i=9; i<23; i++) //判断剩下参数是否正确
            sum2+=raw_data[i];
        if(sum1==raw_data[8] && sum2==raw_data[23])//校验位判断
        {
            memcpy(lora_GY39,raw_data,24);
            //数据处理
            Bme.Lux=(raw_data[4]<<24)|(raw_data[5]<<16)|(raw_data[6]<<8)|raw_data[7];
            Bme.Temp=(raw_data[13]<<8)|raw_data[14];
            data_16[0]=(((uint16_t)raw_data[15])<<8)|raw_data[16];
            data_16[1]=(((uint16_t)raw_data[17])<<8)|raw_data[18];
            Bme.P=(((uint32_t)data_16[0])<<16)|data_16[1];
            Bme.Hum=(raw_data[19]<<8)|raw_data[20];

            //串口屏发送
            if(HMI_buf[0] == 0x00)
            {
                g_uart3TxBufferLen=sprintf((char *)HMI_send,"t10.txt=\"%.2f\"\xff\xff\xff",(float)Bme.Lux/100);
                HAL_UART_Transmit(&huart3,HMI_send, g_uart3TxBufferLen, 0xffff);
                g_uart3TxBufferLen=sprintf((char *)HMI_send,"t11.txt=\"%.2f\"\xff\xff\xff",(float)Bme.Temp/100);
                HAL_UART_Transmit(&huart3,HMI_send, g_uart3TxBufferLen, 0xffff);
                g_uart3TxBufferLen=sprintf((char *)HMI_send,"t12.txt=\"%.2f\"\xff\xff\xff",(float)Bme.P/100);
                HAL_UART_Transmit(&huart3,HMI_send, g_uart3TxBufferLen, 0xffff);
                g_uart3TxBufferLen=sprintf((char *)HMI_send,"t13.txt=\"%.2f\"\xff\xff\xff",(float)Bme.Hum/100);
                HAL_UART_Transmit(&huart3,HMI_send, g_uart3TxBufferLen, 0xffff);
                if(raw_data[21]==0xff)//海拔负数判断
                {
                    Bme.Alt=255 - raw_data[22];
                    g_uart3TxBufferLen=sprintf((char *)HMI_send,"t14.txt=\"-%d\"\xff\xff\xff",Bme.Alt);
                    HAL_UART_Transmit(&huart3,HMI_send, g_uart3TxBufferLen, 0xffff);
                }
                else
                {
                    Bme.Alt=(raw_data[21]<<8)|raw_data[22];
                    g_uart3TxBufferLen=sprintf((char *)HMI_send,"t14.txt=\"%d\"\xff\xff\xff",Bme.Alt);
                    HAL_UART_Transmit(&huart3,HMI_send, g_uart3TxBufferLen, 0xffff);
                }
            }
//			HAL_UART_Transmit(&huart3,g_uart3RxBuffer,g_uart3RxBufferLen,0xffff);
        }
        memcpy(HMI_data,raw_data,24);
        for(int i=0; i<g_uart3RxBufferLen; i++) //清零
            g_uart3RxBuffer[i]=0;
        g_uart3RxBufferLen=0;//清零
        for(int j=0; j<g_uart4RxBufferLen; j++) //清零
            raw_data[j]=0;
        g_uart4RxBufferLen=0;//清零
        Receive_ok=0;//处理数据完毕标志
    }
}

//CRC校验
uint8_t reverse8(uint8_t data)
{
    uint8_t i;
    uint8_t temp=0;
    for(i=0; i<8; i++)	//字节反转
        temp|=((data>>i)&0x01)<<(7-i);
    return temp;
}

uint16_t reverse16(uint16_t data)
{
    uint8_t i;
    uint16_t temp=0;
    for(i=0; i<16; i++)		//反转
        temp|=((data>>i)&0x0001)<<(15-i);
    return temp;
}

uint16_t crc16(uint8_t *addr, int num)
{
    uint8_t data;
    uint16_t poly=0x8005;//多项式
    uint16_t xor16=0x0000;//结果异或值
    uint16_t crc=0xFFFF;//初始值
    int i;
    for(; num>0; num--)
    {
        data=*addr++;
        data=reverse8(data);				//字节反转
        crc=crc^(data<<8) ;					//与crc初始值高8位异或
        for(i=0; i<8; i++)					//循环8位
        {
            if(crc&0x8000)					//左移移出的位为1，左移后与多项式异或
                crc=(crc<<1)^poly;
            else		                        //否则直接左移
                crc<<=1;
        }
    }
    crc=reverse16(crc);
    crc=crc^xor16;	                        //最后返与结果异或值异或
    return(crc);                                //返回最终校验值
}

//风速、风向获取数据
uint8_t rs485_slow=0;//数据减速
uint8_t rs485_flag=1;//485标志位
uint8_t rs485_sendok=1;
uint8_t S_data[12];
uint8_t D_data1[12];
uint8_t D_data2[12];
uint8_t Wind_lora;
uint16_t Wind_speed;
uint16_t Wind_direction;

void RS485()
{
    uint8_t S_address[8]= {0x01,0x03,0x00,0x00,0x00,0x01,0x84,0x0A};
    uint8_t D_address[8]= {0x02,0x03,0x00,0x00,0x00,0x02,0xC4,0x38};
    uint8_t crc_t[2]= {0};
    uint16_t crc_rev=0;
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    if(rs485_flag == 1)
    {
        if(rs485_sendok == 1)
        {
            rs485_sendok = 0;
            //发送风速
            HAL_UART_Transmit(&huart2,S_address, 8, 0xffff);
            HAL_Delay(30);
            memcpy(lora_WS,g_uart2RxBuffer,7);

            crc_rev=crc16(lora_WS,5);
            crc_t[0]=crc_rev;
            crc_t[1]=crc_rev>>8;

            if(lora_WS[0]==0x01 && lora_WS[5]==crc_t[0] && lora_WS[6]==crc_t[1])
            {
//				HAL_UART_Transmit(&huart3,lora_WS, 7, 0xffff);
                Wind_speed=(lora_WS[3]<<8)|lora_WS[4];
                if(HMI_buf[0] == 0x00)
                {
                    g_uart3TxBufferLen=sprintf((char *)S_data,"t17.txt=\"%.1f\"\xff\xff\xff",(float)Wind_speed/10.0);
                    HAL_UART_Transmit(&huart3,S_data, g_uart3TxBufferLen, 0xffff);
                }
            }
            g_uart2RxBufferLen=0;//清零
        }
    }
    else if(rs485_flag == 0)
    {
        if(rs485_sendok == 0)
        {
            rs485_sendok = 1;
            //发送风向
            HAL_UART_Transmit(&huart2,D_address, 8, 0xffff);
            HAL_Delay(30);
            memcpy(lora_WD,g_uart2RxBuffer,9);

            crc_rev=crc16(lora_WD,7);
            crc_t[0]=crc_rev;
            crc_t[1]=crc_rev>>8;

            if(lora_WD[0]==0x02 && lora_WD[7]==crc_t[0] && lora_WD[8]==crc_t[1])
            {
//				HAL_UART_Transmit(&huart3,lora_WD, 9, 0xffff);
                switch(lora_WD[4])
                {
                case 0:
                    g_uart3TxBufferLen=sprintf((char *)D_data1,"t18.txt=\"北风\"\xff\xff\xff");
                    Wind_lora=0;
                    break;
                case 1:
                    g_uart3TxBufferLen=sprintf((char *)D_data1,"t18.txt=\"东北风\"\xff\xff\xff");
                    Wind_lora=1;
                    break;
                case 2:
                    g_uart3TxBufferLen=sprintf((char *)D_data1,"t18.txt=\"东风\"\xff\xff\xff");
                    Wind_lora=2;
                    break;
                case 3:
                    g_uart3TxBufferLen=sprintf((char *)D_data1,"t18.txt=\"东南风\"\xff\xff\xff");
                    Wind_lora=3;
                    break;
                case 4:
                    g_uart3TxBufferLen=sprintf((char *)D_data1,"t18.txt=\"南风\"\xff\xff\xff");
                    Wind_lora=4;
                    break;
                case 5:
                    g_uart3TxBufferLen=sprintf((char *)D_data1,"t18.txt=\"西南风\"\xff\xff\xff");
                    Wind_lora=5;
                    break;
                case 6:
                    g_uart3TxBufferLen=sprintf((char *)D_data1,"t18.txt=\"西风\"\xff\xff\xff");
                    Wind_lora=6;
                    break;
                case 7:
                    g_uart3TxBufferLen=sprintf((char *)D_data1,"t18.txt=\"西北风\"\xff\xff\xff");
                    Wind_lora=7;
                    break;
                }
                if(HMI_buf[0] == 0x00)
                {
                    HAL_UART_Transmit(&huart3,D_data1, g_uart3TxBufferLen, 0xffff);
                    Wind_direction=(lora_WD[5]<<8)|lora_WD[6];
                    g_uart3TxBufferLen=sprintf((char *)D_data2,"t20.txt=\"%d\"\xff\xff\xff",Wind_direction);
                    HAL_UART_Transmit(&huart3,D_data2, g_uart3TxBufferLen, 0xffff);
                }
            }
            g_uart2RxBufferLen=0;//清零
        }
    }
}

//RTC获取时间数据
RTC_DateTypeDef GetData;//获取日期结构体
RTC_TimeTypeDef GetTime;//获取时间结构体
uint8_t rtc_slow;
uint8_t rtc_flag;

void TIME()
{
    if(rtc_flag==1)
    {
        rtc_flag=0;
        HAL_RTC_GetTime(&hrtc, &GetTime, RTC_FORMAT_BIN);
        HAL_RTC_GetDate(&hrtc, &GetData, RTC_FORMAT_BIN);
        //串口屏发送曲线
        switch(HMI_buf[0])
        {
        case 0x00:
            g_uart3TxBufferLen=sprintf((char *)HMI_send,"t21.txt=\"%d\"\xff\xff\xff",GetTime.Hours);
            HAL_UART_Transmit(&huart3,HMI_send, g_uart3TxBufferLen, 0xffff);
            g_uart3TxBufferLen=sprintf((char *)HMI_send,"t22.txt=\"%d\"\xff\xff\xff",GetTime.Minutes);
            HAL_UART_Transmit(&huart3,HMI_send, g_uart3TxBufferLen, 0xffff);
            g_uart3TxBufferLen=sprintf((char *)HMI_send,"t23.txt=\"%d\"\xff\xff\xff",GetTime.Seconds);
            HAL_UART_Transmit(&huart3,HMI_send, g_uart3TxBufferLen, 0xffff);
            g_uart3TxBufferLen=sprintf((char *)HMI_send,"t26.txt=\"%d\"\xff\xff\xff",2000 + GetData.Year);
            HAL_UART_Transmit(&huart3,HMI_send, g_uart3TxBufferLen, 0xffff);
            g_uart3TxBufferLen=sprintf((char *)HMI_send,"t27.txt=\"%d\"\xff\xff\xff",GetData.Month);
            HAL_UART_Transmit(&huart3,HMI_send, g_uart3TxBufferLen, 0xffff);
            g_uart3TxBufferLen=sprintf((char *)HMI_send,"t28.txt=\"%d\"\xff\xff\xff",GetData.Date);
            HAL_UART_Transmit(&huart3,HMI_send, g_uart3TxBufferLen, 0xffff);
            break;
        case 0x01:
            g_uart3TxBufferLen=sprintf((char *)HMI_send,"add 1,0,%d\xff\xff\xff",Bme.Lux*160/100000);
            HAL_UART_Transmit(&huart3,HMI_send, g_uart3TxBufferLen, 0xffff);
            break;
        case 0x02:
            g_uart3TxBufferLen=sprintf((char *)HMI_send,"add 2,0,%d\xff\xff\xff",Bme.Temp*160/4000);
            HAL_UART_Transmit(&huart3,HMI_send, g_uart3TxBufferLen, 0xffff);
            break;
        case 0x03:
            g_uart3TxBufferLen=sprintf((char *)HMI_send,"add 3,0,%d\xff\xff\xff",(Bme.P/100-90000)*160/20000);
            HAL_UART_Transmit(&huart3,HMI_send, g_uart3TxBufferLen, 0xffff);
            break;
        case 0x04:
            g_uart3TxBufferLen=sprintf((char *)HMI_send,"add 4,0,%d\xff\xff\xff",Bme.Hum*160/10000);
            HAL_UART_Transmit(&huart3,HMI_send, g_uart3TxBufferLen, 0xffff);
            break;
        case 0x05:
            if(HMI_data[21]==0xff)
            {
                g_uart3TxBufferLen=sprintf((char *)HMI_send,"add 5,0,%d\xff\xff\xff",40-Bme.Alt*40/1000);
                HAL_UART_Transmit(&huart3,HMI_send, g_uart3TxBufferLen, 0xffff);
            }
            else
            {
                g_uart3TxBufferLen=sprintf((char *)HMI_send,"add 5,0,%d\xff\xff\xff",40+Bme.Alt*40/1000);
                HAL_UART_Transmit(&huart3,HMI_send, g_uart3TxBufferLen, 0xffff);
            }
            break;
        case 0x06:
            g_uart3TxBufferLen=sprintf((char *)HMI_send,"add 6,0,%d\xff\xff\xff",Wind_speed*40/50);
            HAL_UART_Transmit(&huart3,HMI_send, g_uart3TxBufferLen, 0xffff);
            break;
        }
    }
}

void LORA()
{
    if(lora_flag==1)//LORA发送
    {
        lora_flag=0;
        for(int i = 0; i < 24; i++)
        {
            lora_data[i] = lora_GY39[i];
        }
        for(int j = 24; j < 31; j++)
        {
            lora_data[j] = lora_WS[j - 24];
        }
        for(int k = 31; k < 40; k++)
        {
            lora_data[k] = lora_WD[k - 31];
        }
        HAL_UART_Transmit(&huart1,lora_data, 40, 0xffff);
    }
}

int main(void)
{
    HAL_Init();

    SystemClock_Config();

    while (0)
    {
        MX_GPIO_Init();
    }
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();
    MX_USART3_UART_Init();
    MX_USART4_UART_Init();

    memset(g_uart1TxBuffer, 0, USART1_txSize);
    memset(g_uart1RxBuffer, 0, USART1_rxSize);

    memset(g_uart2TxBuffer, 0, USART2_txSize);
    memset(g_uart2RxBuffer, 0, USART2_rxSize);

    memset(g_uart3TxBuffer, 0, USART3_txSize);
    memset(g_uart3RxBuffer, 0, USART3_rxSize);

    memset(g_uart4TxBuffer, 0, USART4_txSize);
    memset(g_uart4RxBuffer, 0, USART4_rxSize);

    HAL_UART_Receive_IT(&huart1, &rx_buf, sizeof(rx_buf));
    HAL_UART_Receive_IT(&huart2, &rx_buf, sizeof(rx_buf));
    HAL_UART_Receive_IT(&huart3, &rx_buf, sizeof(rx_buf));
    HAL_UART_Receive_IT(&huart4, &rx_buf, sizeof(rx_buf));
    MX_TIM6_Init();
    MX_TIM7_Init();
    MX_TIM14_Init();
    MX_TIM16_Init();
    MX_RTC_Init();

    HAL_TIM_Base_Start_IT(&htim6);
    HAL_TIM_Base_Start_IT(&htim7);
    HAL_TIM_Base_Start_IT(&htim14);
    HAL_TIM_Base_Start_IT(&htim16);

    send_com();//发送读气压温湿度指令

    while (1)
    {
        GY39();
        RS485();
        TIME();
        LORA();
    }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
    */
    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
    RCC_OscInitStruct.PLL.PLLN = 72;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV8;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                  |RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief TIME Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

    /* USER CODE BEGIN RTC_Init 0 */

    /* USER CODE END RTC_Init 0 */

    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    /* USER CODE BEGIN RTC_Init 1 */

    /* USER CODE END RTC_Init 1 */

    /** Initialize TIME Only
    */
    hrtc.Instance = RTC;
    hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
    hrtc.Init.AsynchPrediv = 127;
    hrtc.Init.SynchPrediv = 255;
    hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
    hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
    hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
    hrtc.Init.OutPutPullUp = RTC_OUTPUT_PULLUP_NONE;
    if (HAL_RTC_Init(&hrtc) != HAL_OK)
    {
        Error_Handler();
    }

    /* USER CODE BEGIN Check_RTC_BKUP */

    /* USER CODE END Check_RTC_BKUP */

    /** Initialize TIME and set the Time and Date
    */
    sTime.Hours = 15;
    sTime.Minutes = 30;
    sTime.Seconds = 30;
    sTime.SubSeconds = 0;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;
    if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
    {
        Error_Handler();
    }
    sDate.WeekDay = RTC_WEEKDAY_MONDAY;
    sDate.Month = RTC_MONTH_AUGUST;
    sDate.Date = 16;
    sDate.Year = 23;

    if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN RTC_Init 2 */

    /* USER CODE END RTC_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

    /* USER CODE BEGIN TIM6_Init 0 */

    /* USER CODE END TIM6_Init 0 */

    TIM_MasterConfigTypeDef sMasterConfig = {0};

    /* USER CODE BEGIN TIM6_Init 1 */

    /* USER CODE END TIM6_Init 1 */
    htim6.Instance = TIM6;
    htim6.Init.Prescaler = 36000-1;
    htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim6.Init.Period = 10-1;
    htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM6_Init 2 */

    /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

    /* USER CODE BEGIN TIM7_Init 0 */

    /* USER CODE END TIM7_Init 0 */

    TIM_MasterConfigTypeDef sMasterConfig = {0};

    /* USER CODE BEGIN TIM7_Init 1 */

    /* USER CODE END TIM7_Init 1 */
    htim7.Instance = TIM7;
    htim7.Init.Prescaler = 36000-1;
    htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim7.Init.Period = 1000-1;
    htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM7_Init 2 */

    /* USER CODE END TIM7_Init 2 */

}

/**
  * @brief TIM14 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM14_Init(void)
{

    /* USER CODE BEGIN TIM14_Init 0 */

    /* USER CODE END TIM14_Init 0 */

    /* USER CODE BEGIN TIM14_Init 1 */

    /* USER CODE END TIM14_Init 1 */
    htim14.Instance = TIM14;
    htim14.Init.Prescaler = 36000-1;
    htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim14.Init.Period = 10-1;
    htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM14_Init 2 */

    /* USER CODE END TIM14_Init 2 */

}

/**
  * @brief TIM16 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM16_Init(void)
{

    /* USER CODE BEGIN TIM16_Init 0 */

    /* USER CODE END TIM16_Init 0 */

    /* USER CODE BEGIN TIM16_Init 1 */

    /* USER CODE END TIM16_Init 1 */
    htim16.Instance = TIM16;
    htim16.Init.Prescaler = 36000-1;
    htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim16.Init.Period = 10-1;
    htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim16.Init.RepetitionCounter = 0;
    htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM16_Init 2 */

    /* USER CODE END TIM16_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

    /* USER CODE BEGIN USART1_Init 0 */

    /* USER CODE END USART1_Init 0 */

    /* USER CODE BEGIN USART1_Init 1 */

    /* USER CODE END USART1_Init 1 */
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 9600;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
    huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN USART1_Init 2 */

    /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

    /* USER CODE BEGIN USART2_Init 0 */

    /* USER CODE END USART2_Init 0 */

    /* USER CODE BEGIN USART2_Init 1 */

    /* USER CODE END USART2_Init 1 */
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 4800;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
    huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        Error_Handler();
    }
//  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
//  {
//    Error_Handler();
//  }
    /* USER CODE BEGIN USART2_Init 2 */

    /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

    /* USER CODE BEGIN USART3_Init 0 */

    /* USER CODE END USART3_Init 0 */

    /* USER CODE BEGIN USART3_Init 1 */

    /* USER CODE END USART3_Init 1 */
    huart3.Instance = USART3;
    huart3.Init.BaudRate = 9600;
    huart3.Init.WordLength = UART_WORDLENGTH_8B;
    huart3.Init.StopBits = UART_STOPBITS_1;
    huart3.Init.Parity = UART_PARITY_NONE;
    huart3.Init.Mode = UART_MODE_TX_RX;
    huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;
    huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
    huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart3) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN USART3_Init 2 */

    /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART4_UART_Init(void)
{

    /* USER CODE BEGIN USART4_Init 0 */

    /* USER CODE END USART4_Init 0 */

    /* USER CODE BEGIN USART4_Init 1 */

    /* USER CODE END USART4_Init 1 */
    huart4.Instance = USART4;
    huart4.Init.BaudRate = 9600;
    huart4.Init.WordLength = UART_WORDLENGTH_8B;
    huart4.Init.StopBits = UART_STOPBITS_1;
    huart4.Init.Parity = UART_PARITY_NONE;
    huart4.Init.Mode = UART_MODE_TX_RX;
    huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart4.Init.OverSampling = UART_OVERSAMPLING_16;
    huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart4.Init.ClockPrescaler = UART_PRESCALER_DIV1;
    huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart4) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN USART4_Init 2 */

    /* USER CODE END USART4_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

    /*Configure GPIO pin : PC13 */
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
