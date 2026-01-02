#ifndef APPFAILDIAG_H
#define APPFAILDIAG_H

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    FAULT_NONE = 0,
    FAULT_OVERCURRENT,
    FAULT_OVERVOLTAGE
} FaultCode_t;

void AppFailDiag_Init(void);
void AppFailDiag_Update(uint16_t current_mA, uint16_t voltage_mV);
bool AppFailDiag_HasFault(void);
FaultCode_t AppFailDiag_GetFaultCode(void);

#endif // APPFAILDIAG_H
