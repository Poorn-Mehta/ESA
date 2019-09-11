/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "math.h"
#include "float.h"

void Main_Init(void)
{
    ADC_DelSig_1_Start();
    LCD_Start();
    LCD_Position(0, 0);
    LCD_PrintString(" Thermistor");
    P1_6_Write(0);
    P1_7_Write(0);
}

uint16_t R1_Raw, R1_mV, Rt_Raw, Rt_mV, temperature, count;
float Current, Rt_val, Rt_val2, R1_mV_f, Rt_mV_f, xyz;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    Main_Init();
    while(1)
    {
        count += 1;
        P1_6_Write(1);
        ADC_DelSig_1_StartConvert();
        ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_WAIT_FOR_RESULT);
        P1_6_Write(0);
        Rt_Raw = ADC_DelSig_1_GetResult16();
        Rt_mV = ADC_DelSig_1_CountsTo_mVolts(Rt_Raw);
        Rt_mV_f = Rt_mV;
        xyz = Rt_mV_f / (3300 - Rt_mV_f);
        xyz *= 10000;
        temperature = Thermistor_1_GetTemperature(xyz);
        CyDelay(1);
        if(count > 100)
        {
            P1_7_Write(1);
            LCD_ClearDisplay();
            LCD_Position(0, 0);
            LCD_PrintString("Thermistor");
            LCD_Position(1, 0);
            LCD_PrintU32Number(temperature/100);
            if((temperature/100) < 10)
            {
                LCD_Position(1, 1);
                LCD_PrintString(".");
                LCD_Position(1, 2);
            }
            else
            {
                LCD_Position(1, 2);
                LCD_PrintString(".");
                LCD_Position(1, 3);
            }
            if((temperature%100) < 10)
            {
                LCD_PrintString("0");
            }
            LCD_PrintU32Number(temperature%100);
            LCD_Position(1, 5);
            LCD_PrintString("C");
            count = 0;
            P1_7_Write(0);
        }
    }
}

/* [] END OF FILE */
