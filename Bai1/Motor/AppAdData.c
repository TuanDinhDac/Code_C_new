#include "AppAdData.h"
#include <math.h>

#define M_PI 3.14f;

/**
 * Biến lưu dữ liệu cảm biến
 */
static AppAdData_t sensorData;

/**
 * Hàm giả lập đọc phần cứng (bạn thay bằng hàm MCU thật)
 */
static float MCU_ReadMotorTempC(void);
static float MCU_ReadMotorSpeedRPM(void);
static float MCU_ReadMotorAngleRad(void);
static float MCU_ReadMotorCurrentA(void);

void AppAdData_Init(void)
{
    sensorData.motorTempC    = 0.0f;
    sensorData.motorSpeedRPM = 0.0f;
    sensorData.motorAngleRad = 0.0f;
    sensorData.motorCurrentA = 0.0f;
}

void AppAdData_Update(void)
{
    sensorData.motorTempC    = MCU_ReadMotorTempC();
    sensorData.motorSpeedRPM = MCU_ReadMotorSpeedRPM();
    sensorData.motorAngleRad = MCU_ReadMotorAngleRad();
    sensorData.motorCurrentA = MCU_ReadMotorCurrentA();
}

AppAdData_t AppAdData_GetData(void)
{
    return sensorData;
}

/* ============================================================
   Các hàm đọc phần cứng – bạn thay bằng code MCU thực tế
   ============================================================ */

static float MCU_ReadMotorTempC(void)
{
    // Ví dụ: đọc ADC kênh nhiệt độ
    uint16_t adcValue = ADC_ReadChannel(ADC_CHANNEL_TEMP);
    float tempC = (adcValue * 3.3f / 4096.0f) * 100.0f; // ví dụ scale
    return tempC;
}

static float MCU_ReadMotorSpeedRPM(void)
{
    // Ví dụ: đọc encoder hoặc hall sensor
    int32_t pulse = Encoder_GetSpeedPulse();
    float rpm = pulse * 60.0f / ENCODER_PPR;
    return rpm;
}

static float MCU_ReadMotorAngleRad(void)
{
    // Ví dụ: đọc góc từ encoder
    uint16_t pos = Encoder_GetPosition();
    float angle = (pos / (float)ENCODER_MAX_COUNT) * 2.0f * M_PI;
    return angle;
}

static float MCU_ReadMotorCurrentA(void)
{
    // Ví dụ: đọc dòng từ shunt resistor qua ADC
    uint16_t adcValue = ADC_ReadChannel(ADC_CHANNEL_CURRENT);
    float voltage = adcValue * 3.3f / 4096.0f;
    float current = voltage / SHUNT_RESISTOR_OHMS / CURRENT_AMP_GAIN;
    return current;
}
