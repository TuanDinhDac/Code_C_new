#include "Main.h"
#include "MainControl.h"
#include "AppFailDiag.h"
#include "AppAdData.h"

void Main_Init(void)
{
    MainControl_Init();
    AppFailDiag_Init();
}

void Main_Loop(void)
{
    float targetSpeedRPM = ReadTargetSpeed(); // giả sử có hàm đọc tốc độ mong muốn
    float phaseVoltage[3];
    float actualSpeedRPM = 10.f; //10rpm

    MainControl_ComputeFOC(targetSpeedRPM, phaseVoltage);

    ApplyPhaseVoltage(phaseVoltage); // giả sử có hàm xuất điện áp

    float current_mA = ReadMotorCurrent();
    float voltage_mV = ReadBusVoltage();

    AppFailDiag_Update(current_mA,
                   voltage_mV,
                   targetSpeedRPM,
                   actualSpeedRPM);

    if (AppFailDiag_HasFault())
    {
        HandleMotorFault(AppFailDiag_GetFaultCode());
    }

    AppAdData_Update(); 
    AppAdData_t data = AppAdData_GetData();
}
