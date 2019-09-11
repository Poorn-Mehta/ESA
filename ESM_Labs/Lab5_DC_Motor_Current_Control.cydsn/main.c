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
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
int main(void)
{
    CyGlobalIntEnable;
    DAC_Start();
    COMP_Start();
    PGA_Start();
    Clock_1_Start();
    PWM_Start();
    SH_Start();
    ADC_Start();
    LCD_Start();
    LCD_ClearDisplay();
    uint8_t DAC_value;
    uint16_t DAC_mA, i;
    uint16_t ADC_output, ADC_counts, ADC_counts_mA, ADC_mA;
    while(1)
    {
        LCD_Position(0,0);
        LCD_PrintString("DAC: ");
        
            DAC_value = 40; // for 100 mA//0x28
            DAC_SetValue(DAC_value);
            DAC_mA = 100;
            

            ADC_mA = 0;
            
            for(i = 0; i < 10; i ++)
            {
                CyDelay(200);            
                ADC_output = ADC_GetResult16();
                ADC_counts = ADC_CountsTo_mVolts(ADC_output);
                ADC_counts_mA = (ADC_counts*10)/64;
                if(ADC_counts_mA > ADC_mA)
                {
                    ADC_mA = ADC_counts_mA;
                    
                    LCD_Position(0,5);
                    LCD_PrintNumber(DAC_mA);
                    LCD_Position(0,10);
                    LCD_PrintString("mA");
                    
                    LCD_Position(1,0);
                    LCD_PrintString("ADC: ");
                    LCD_Position(1,5);
                    if(ADC_mA < 100)
                    {
                        LCD_PrintString("0");
                    }
                    LCD_PrintNumber(ADC_mA);
                    LCD_Position(1,10);
                    LCD_PrintString("mA");
                }
            }
        
        
        
            DAC_value = 80; // for 200 mA//0x50
            DAC_SetValue(DAC_value);
            DAC_mA = 200;
            
            
            ADC_mA = 0;
            
            for(i = 0; i < 10; i ++)
            {
                CyDelay(200);            
                ADC_output = ADC_GetResult16();
                ADC_counts = ADC_CountsTo_mVolts(ADC_output);
                ADC_counts_mA = (ADC_counts*10)/64;
                if(ADC_counts_mA > ADC_mA)
                {
                    ADC_mA = ADC_counts_mA;
                    
                    LCD_Position(0,5);
                    LCD_PrintNumber(DAC_mA);
                    LCD_Position(0,10);
                    LCD_PrintString("mA");
                    
                    LCD_Position(1,0);
                    LCD_PrintString("ADC: ");
                    LCD_Position(1,5);
                    if(ADC_mA < 100)
                    {
                        LCD_PrintString("0");
                    }
                    LCD_PrintNumber(ADC_mA);
                    LCD_Position(1,10);
                    LCD_PrintString("mA");
                }
            }
        
            DAC_value = 120; // for 300 mA//0x78
            DAC_SetValue(DAC_value);
            DAC_mA = 300;
            LCD_Position(0,5);
            LCD_PrintNumber(DAC_mA);
            LCD_Position(0,10);
            LCD_PrintString("mA");
            
            ADC_mA = 0;
            
            for(i = 0; i < 10; i ++)
            {
                CyDelay(200);            
                ADC_output = ADC_GetResult16();
                ADC_counts = ADC_CountsTo_mVolts(ADC_output);
                ADC_counts_mA = (ADC_counts*10)/64;
                if(ADC_counts_mA > ADC_mA)
                {
                    ADC_mA = ADC_counts_mA;
                    
                    LCD_Position(0,5);
                    LCD_PrintNumber(DAC_mA);
                    LCD_Position(0,10);
                    LCD_PrintString("mA");
                    
                    LCD_Position(1,0);
                    LCD_PrintString("ADC: ");
                    LCD_Position(1,5);
                    if(ADC_mA < 100)
                    {
                        LCD_PrintString("0");
                    }
                    LCD_PrintNumber(ADC_mA);
                    LCD_Position(1,10);
                    LCD_PrintString("mA");
                }
            }
        
    }
}

/* [] END OF FILE */
