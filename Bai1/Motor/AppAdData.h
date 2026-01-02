#ifndef APP_AD_DATA_H
#define APP_AD_DATA_H

#include <stdint.h>
#include <stdbool.h>

#ifndef APP_AD_CONFIG_H
#define APP_AD_CONFIG_H

/* ============================
   ADC & Cảm biến nhiệt độ
   ============================ */
#define ADC_MAX_VALUE           4096.0f     // 12-bit ADC
#define ADC_REF_VOLTAGE         3.3f        // Volt

// Hệ số chuyển đổi nhiệt độ (ví dụ: cảm biến 10mV/°C)
#define TEMP_SENSOR_MV_PER_C    10.0f       // 10mV = 1°C
#define TEMP_SENSOR_OFFSET_C    0.0f        // offset nếu có

// Kênh ADC
#define ADC_CHANNEL_TEMP        0
#define ADC_CHANNEL_CURRENT     1


/* ============================
   Encoder / Hall Sensor
   ============================ */

// Encoder xung trên vòng quay (PPR)
#define ENCODER_PPR             1024.0f

// Giá trị đếm tối đa của encoder (ví dụ timer 16-bit)
#define ENCODER_MAX_COUNT       65535.0f


/* ============================
   Cảm biến dòng điện
   ============================ */

// Điện trở shunt (ohm)
#define SHUNT_RESISTOR_OHMS     0.01f       // 10 mΩ

// Hệ số khuếch đại của mạch đo dòng (INA181, ACS712…)
#define CURRENT_AMP_GAIN        20.0f       // ví dụ x20

// Điện áp offset (nếu cảm biến dòng có offset 1.65V)
#define CURRENT_SENSOR_OFFSET_V 1.65f


/* ============================
   Tốc độ động cơ
   ============================ */

// Số xung encoder đọc được trong 1 chu kỳ đo tốc độ
#define SPEED_SAMPLE_PERIOD_MS  10.0f

#endif // APP_AD_CONFIG_H

/**
 * Cấu trúc chứa toàn bộ dữ liệu cảm biến đọc được
 */
typedef struct
{
    float motorTempC;        // Nhiệt độ động cơ (°C)
    float motorSpeedRPM;     // Tốc độ động cơ (RPM)
    float motorAngleRad;     // Góc rotor (radian)
    float motorCurrentA;     // Dòng điện pha hoặc tổng (A)
} AppAdData_t;

/**
 * Khởi tạo module đọc dữ liệu
 */
void AppAdData_Init(void);

/**
 * Cập nhật dữ liệu cảm biến (gọi định kỳ mỗi 1ms hoặc 10ms)
 */
void AppAdData_Update(void);

/**
 * Lấy dữ liệu cảm biến mới nhất
 */
AppAdData_t AppAdData_GetData(void);

#endif // APP_AD_DATA_H
