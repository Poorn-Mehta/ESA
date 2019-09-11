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
#define Duty_Cycle 80
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    LCD_Start();
    LCD_Position(0, 0);
    LCD_PrintString("Motor");
    ADC_SAR_1_Start();
    // ADC_SAR_2_Start();
    PGA_1_Start();
    AMux_1_Start();
    uint16_t Vdrop, Vcounts, Rdrop, Rcounts, Current, loop_counter, Constant, Vmotor,
    RPM;
    uint16_t Varray[30], Carray[30];
    uint32_t Vsum, Csum;
    loop_counter = 0;
    P4_1_Write(1);
    CyDelay(100);
    P4_1_Write(0);
    CyDelay(1);
    AMux_1_Select(0);
    ADC_SAR_1_StartConvert();
    ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
    Vcounts = ADC_SAR_1_GetResult16();
    Vdrop = ADC_SAR_1_CountsTo_mVolts(Vcounts);
    Vmotor = 5000 - Vdrop;
    Constant = 14000 / Vmotor;
    
    while(1)
    {
        P4_1_Write(1);
        CyDelay((Duty_Cycle*10)/100);
        AMux_1_Select(1);
        ADC_SAR_1_StartConvert();
        ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
        Rcounts = ADC_SAR_1_GetResult16();
        Rdrop = (ADC_SAR_1_CountsTo_mVolts(Rcounts));
        Current = (Rdrop*10) / 64;
        Carray[loop_counter] = Current;
        P4_5_Write(1);
        P4_1_Write(0);
        CyDelayUs(500);
        AMux_1_Select(0);
        ADC_SAR_1_StartConvert();
        ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
        Vcounts = ADC_SAR_1_GetResult16();
        Vdrop = ADC_SAR_1_CountsTo_mVolts(Vcounts);
        Vmotor = 5000 - Vdrop;
        Varray[loop_counter] = Vmotor;
        P4_5_Write(0);
        loop_counter += 1;
        if(loop_counter > 29)
        {
            P4_6_Write(1);
            Vsum = 0;
            Csum = 0;
            for(uint8_t count = 0; count < 30; count ++)
            {
                Vsum += Varray[count];
                Csum += Carray[count];
            }
            Vsum /= 30;
            Csum /= 30;
            Vmotor = (uint16_t)Vsum;
            Current = (uint16_t)Csum;
            RPM = Constant*Vmotor;
            LCD_ClearDisplay();
            loop_counter = 0;
            LCD_Position(0, 0);
            LCD_PrintString("B:");
            LCD_Position(0, 2);
            if(Vmotor < 1000) LCD_PrintString("0");
            else LCD_PrintU32Number(Vmotor/1000);
            LCD_Position(0, 3);
            LCD_PrintString(".");
            if((Vmotor%1000) < 10)
            {
                LCD_PrintString("00");
            }
            else if((Vmotor%1000) < 100)
            {
                LCD_PrintString("0");
                LCD_Position(0,5);
                LCD_PrintU32Number((Vmotor%1000)/10);
            }
            else
            {
                LCD_Position(0,4);
                LCD_PrintU32Number((Vmotor%1000)/10);
            }
            LCD_Position(0,6);
            LCD_PrintString("V");
            LCD_Position(0, 8);
            LCD_PrintString("C:");
            LCD_Position(0, 10);
            if(Current < 1000)
            {
                LCD_PrintString("0");
            }
            else
            {
                LCD_PrintU32Number(Current/1000);
            }
            LCD_Position(0, 11);
            LCD_PrintString(".");
            if((Current%1000) < 10)
            {
                LCD_PrintString("00");
                LCD_Position(0, 14);
                LCD_PrintU32Number(Current%1000);
            }
            else if((Current%1000) < 100)
            {
                LCD_PrintString("0");
                LCD_Position(0,13);
                LCD_PrintU32Number(Current%1000);
            }
            else
            {
                LCD_Position(0,12);
                LCD_PrintU32Number(Current%1000);
            }
            LCD_Position(0,15);
            LCD_PrintString("A");
            LCD_Position(1,0);
            LCD_PrintString("RPM:");
            LCD_Position(1,4);
            LCD_PrintU32Number(RPM);
            P4_6_Write(0);
        }
    }
}

/* [] END OF FILE */
