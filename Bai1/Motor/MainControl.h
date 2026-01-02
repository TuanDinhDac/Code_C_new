#ifndef MAINCONTROL_H
#define MAINCONTROL_H

void MainControl_Init(void);

/**
 * Tính toán FOC từ tốc độ đầu vào → điện áp 3 pha
 * @param targetSpeedRPM: tốc độ mong muốn
 * @param phaseVoltage: mảng float[3] chứa kết quả điện áp pha A, B, C
 */
void MainControl_ComputeFOC(float targetSpeedRPM, float phaseVoltage[3]);

#endif // MAINCONTROL_H
