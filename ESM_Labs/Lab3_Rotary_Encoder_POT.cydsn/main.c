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
#define Rotary_Mode 0
#define POT_Mode 1
#define Mode POT_Mode
void rotary(void)
{
    QuadDec_1_Start();
    LCD_Start();
    LCD_Position(0,0);
    LCD_PrintString("Software: ");
    int8_t soft_counter, hard_counter, s2;
    uint8_t pin0_status, pin1_status, update;
    uint32_t loop_counter = 0;
    s2 = 0;
    soft_counter = 0;
    hard_counter = 0;
    update = 1;
    /*Pins P1_6 and P1_7 are used to calculate the critical loop times
    */
    while(1)
    {
        loop_counter +=1;
        pin1_status = P4_1_Read();
        pin0_status = P4_0_Read();
        if(pin1_status == 0)
        {
            //raise one pin
            P1_6_Write(1);
            do{
                pin0_status = P4_0_Read();
            }while(pin0_status != 0);
            
            do{
                pin0_status = P4_0_Read();
                CyDelay(1);
            }while(pin0_status != 1);
            
            if(s2 > 0)
            {
                s2 -= 1;
            }
            else
            {
                soft_counter += 1;
            }
            update = 1;
            //clear that pin, measure time
            P1_6_Write(0);
        }
        
        else if(pin0_status == 0)
        {
            //raise one pin
            P1_6_Write(1);
            do{
                pin1_status = P4_1_Read();
            }while(pin1_status == 1);
            
            do{
                pin0_status = P4_0_Read();
                CyDelay(1);
            }while(pin0_status != 1);
            
            if(soft_counter < 1)
            {
                s2 += 1;
            }
            
            else
            {
                soft_counter -= 1;
            }
            update = 1;
            //clear that pin, measure time
            P1_6_Write(0);
        }
        
        hard_counter = QuadDec_1_GetCounter();
        
        if(update == 1)
        {
            //raise pin 2
            P1_7_Write(1);
            update = 0;
            loop_counter = 0;
            LCD_ClearDisplay();
            LCD_Position(0,0);
            LCD_PrintString("Hardware: ");
            LCD_Position(0,10);
            
            if(hard_counter < 0)
            {
                LCD_PrintString("-");
                hard_counter &= ~(1 << 7);
                hard_counter = 128 - hard_counter;
            }
            
            LCD_PrintNumber(hard_counter);
            LCD_Position(1,0);
            LCD_PrintString("Software: ");
            LCD_Position(1,10);
            
            if(s2 > 0)
            {
                LCD_PrintString("-");
                LCD_PrintNumber(s2);
            }
            
            else
            {
                LCD_PrintNumber(soft_counter);
            }
            //clear that pin
            P1_7_Write(0);
        }
    }
}
void pot(void)
{
    uint16_t pot1,pot2,pot3;
    ADC_SAR_1_Start();
    while(1)
    {
        //raise 1 pin
        P1_6_Write(1);
        ADC_SAR_1_StartConvert();
        ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
        //clear that pin
        P1_6_Write(0);
        pot1 = ADC_SAR_1_GetResult16();
        pot2 = ADC_SAR_1_CountsTo_mVolts(pot1);
        pot3 = (pot2*270) / 5000;
        //raise second pin
        P1_7_Write(1);
        LCD_ClearDisplay();
        LCD_Position(0,0);
        LCD_PrintString("Angle: ");
        LCD_Position(0,7);
        LCD_PrintNumber(pot3);
        //clear that pin
        P1_7_Write(0);
        CyDelay(100);
    }
}
int main(void)
{
    if(Mode == POT_Mode)
    {
        pot();
    }
    else
    {
        rotary();
    }
}
/* [] END OF FILE */
