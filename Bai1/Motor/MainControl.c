#include "MainControl.h"
#include <math.h>

static float Kp = 0.01f;
static float Ki = 0.001f;
static float integral = 0.0f;

void MainControl_Init(void)
{
    integral = 0.0f;
}

void MainControl_ComputeFOC(float targetSpeedRPM, float phaseVoltage[3])
{
    float actualSpeedRPM = ReadActualSpeed(); // giả sử có hàm đọc tốc độ thực tế
    float error = targetSpeedRPM - actualSpeedRPM;

    integral += error;
    float controlOutput = Kp * error + Ki * integral;

    // Giả sử điện áp max là 12V, scale ra 3 pha dạng sin
    float angle = ReadRotorAngle(); // giả sử có encoder
    phaseVoltage[0] = controlOutput * sinf(angle);
    phaseVoltage[1] = controlOutput * sinf(angle - 2.094f); // -120°
    phaseVoltage[2] = controlOutput * sinf(angle + 2.094f); // +120°
}
