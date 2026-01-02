#include "AppFailDiag.h"

static FaultCode_t faultCode = FAULT_NONE;
static const uint16_t CURRENT_LIMIT = 5000; // mA
static const uint16_t VOLTAGE_LIMIT = 13000; // mV

void AppFailDiag_Init(void)
{
    faultCode = FAULT_NONE;
}

void AppFailDiag_Update(uint16_t current_mA, uint16_t voltage_mV)
{
    faultCode = FAULT_NONE;

    if (current_mA > CURRENT_LIMIT)
        faultCode = FAULT_OVERCURRENT;
    else if (voltage_mV > VOLTAGE_LIMIT)
        faultCode = FAULT_OVERVOLTAGE;
}

bool AppFailDiag_HasFault(void)
{
    return faultCode != FAULT_NONE;
}

FaultCode_t AppFailDiag_GetFaultCode(void)
{
    return faultCode;
}
