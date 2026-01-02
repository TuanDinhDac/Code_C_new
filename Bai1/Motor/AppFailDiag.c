#include "AppFailDiag.h"

static FaultCode_t faultCode = FAULT_NONE;

static const uint16_t CURRENT_LIMIT = 5000;     // mA
static const uint16_t VOLTAGE_LIMIT = 13000;    // mV

// Ngưỡng phát hiện motor không quay
static const float SPEED_MIN_RPM = 50.0f;       // tốc độ gần như đứng yên
static const float TARGET_MIN_RPM = 200.0f;     // tốc độ đặt đủ lớn để motor phải quay
static const uint8_t STALL_DEBOUNCE = 10;       // số chu kỳ liên tiếp (ví dụ 10 × 10ms = 100ms)

static uint8_t stallCounter = 0;

void AppFailDiag_Init(void)
{
    faultCode = FAULT_NONE;
    stallCounter = 0;
}

void AppFailDiag_Update(uint16_t current_mA,
                        uint16_t voltage_mV,
                        float targetSpeedRPM,
                        float actualSpeedRPM)
{
    faultCode = FAULT_NONE;

    // 1. Quá dòng
    if (current_mA > CURRENT_LIMIT)
    {
        faultCode = FAULT_OVERCURRENT;
        return;
    }

    // 2. Quá áp
    if (voltage_mV > VOLTAGE_LIMIT)
    {
        faultCode = FAULT_OVERVOLTAGE;
        return;
    }

    // 3. Motor không quay (Stall)
    bool tryingToSpin = (targetSpeedRPM > TARGET_MIN_RPM);
    bool notMoving    = (actualSpeedRPM < SPEED_MIN_RPM);

    if (tryingToSpin && notMoving)
    {
        if (stallCounter < STALL_DEBOUNCE)
            stallCounter++;

        if (stallCounter >= STALL_DEBOUNCE)
        {
            faultCode = FAULT_MOTOR_NOT_SPINNING;
            return;
        }
    }
    else
    {
        stallCounter = 0;
    }
}

bool AppFailDiag_HasFault(void)
{
    return faultCode != FAULT_NONE;
}

FaultCode_t AppFailDiag_GetFaultCode(void)
{
    return faultCode;
}
