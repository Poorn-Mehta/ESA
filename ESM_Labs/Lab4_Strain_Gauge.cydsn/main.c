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
/*******************UART PART STARTS*********************/
char print[6];
uint8_t i;
#if defined (__GNUC__)
/* Add an explicit reference to the floating point printf library
*/
/* to allow usage of the floating point conversion specifiers. */
/* This is not linked in by default with the newlib-nano library.
*/
asm (".global _printf_float");
#endif
#define USBFS_DEVICE (0u)
/* The buffer size is equal to the maximum packet size of the IN and
OUT bulk
* endpoints.
*/
#define USBUART_BUFFER_SIZE (64u)
uint8_t buffer[USBUART_BUFFER_SIZE];
uint8_t buffer2[USBUART_BUFFER_SIZE];
/*****************UART PART ENDS************************/
void display(char *ptr, char ID)
{
    
    for(i = 0; i < 10; i ++)
    {
        if(ID == 0) buffer[i] = ' ';
        else buffer2[i] = ' ';
    }

    for(i = 0; *ptr != 0; i ++, ptr ++)
    {
        if(ID == 0) buffer[i] = (uint8_t)(*ptr);
        else buffer2[i] = (uint8_t)(*ptr);
    }

}
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    ADC_Start();
    PGA_Start();
    DAC_Start();
    Opamp_Start();
    LCD_Start();
    int16_t adc_out, adc_mv, adc_mv_neg;
    uint16_t offset_mv;
    uint8_t DAC_offset_val = 0;
//    int16_t adc_mv_neg;
    uint16_t weight;
    /************************UART PART BEGINS***************/
//    uint16_t count;
    uint8_t volts[5] = {"mV: "};
    uint8_t grams[5] = {"gm: "};
    USBUART_Start(USBFS_DEVICE, USBUART_5V_OPERATION);
    /***********************UART PART ENDS*****************/
    
    DAC_SetValue(DAC_offset_val);
    
    adc_out = ADC_Read16(); 
    adc_mv = ADC_CountsTo_mVolts(adc_out);
    offset_mv = abs(adc_mv);
    
    LCD_ClearDisplay();
    LCD_Position(0,0);
    LCD_PrintString("Auto Calibration");
    
    CyDelay(1000);
    
    while(offset_mv >  0)
    {
        adc_out = ADC_Read16(); 
        adc_mv = ADC_CountsTo_mVolts(adc_out);
        offset_mv = abs(adc_mv);
        DAC_offset_val += 1;
        DAC_SetValue(DAC_offset_val);
    }
    
    LCD_ClearDisplay();
    LCD_Position(0,0);
    LCD_PrintString("Calibrated");
    
    CyDelay(1000);
    
    LCD_ClearDisplay();
    
    while(1)
    {
        LCD_Position(0,0);
        LCD_PrintString("V: ");
        adc_out = ADC_Read16(); 
        adc_mv = ADC_CountsTo_mVolts(adc_out);
        adc_mv_neg = 65535 - adc_mv;
        weight = ((adc_mv * 2) / 3); // Using the equation:((adc_mv/50) / 3 mV)* 100) for finding weight in grams
        /************************UART PART BEGINS***************/
        /* Host can send double SET_INTERFACE request. */
        if (0u != USBUART_IsConfigurationChanged())
        {
            /* Initialize IN endpoints when device is configured. */
            if (0u != USBUART_GetConfiguration())
            {
            /* Enumeration is done, enable OUT endpoint to receive
            data
            * from host. */
                USBUART_CDC_Init();
            }
        }
        /***********************UART PART ENDS*****************/
        /* Conditions for output/display */
        if(adc_mv >= 0)
        {
            LCD_Position(1,0);
            LCD_PrintString("W: ");
            LCD_Position(1,3);
            LCD_PrintNumber(weight);
            if(adc_mv <= 9)
            {
                LCD_Position(0,3);
                LCD_PrintNumber(adc_mv);
                LCD_Position(0,4);
                LCD_PrintString(" ");
            }
            if(adc_mv >= 10 && adc_mv < 100)
            {
                LCD_Position(0,3);
                LCD_PrintNumber(adc_mv);
                LCD_Position(0,5);
                LCD_PrintString(" ");
            }
            if(adc_mv >= 100 && adc_mv <1000)
            {
                LCD_Position(0,3);
                LCD_PrintNumber(adc_mv);
                LCD_Position(0,6);
                LCD_PrintString(" ");
            }
            if(adc_mv >= 1000)
            {
                LCD_Position(0,3);
                LCD_PrintNumber(adc_mv);
                LCD_Position(0,7);
                LCD_PrintString(" ");
            }
            LCD_Position(0,9);
            LCD_PrintString("mV");
            LCD_Position(1,9);
            LCD_PrintString("g");
            /*UART Part*/
            if (0u != USBUART_GetConfiguration())
            {
            itoa(adc_mv, print, 10);
            display(print, 0);
            itoa(weight, print, 10);
            display(print, 1);
            while (0u == USBUART_CDCIsReady());
            USBUART_PutData(volts, 5);
            while (0u == USBUART_CDCIsReady());
            USBUART_PutData(buffer, 10);
            while (0u == USBUART_CDCIsReady());
            USBUART_PutCRLF();
            while (0u == USBUART_CDCIsReady());
            USBUART_PutData(grams, 5);
            while (0u == USBUART_CDCIsReady());
            USBUART_PutData(buffer2, 10);
            while (0u == USBUART_CDCIsReady());
            USBUART_PutCRLF();
            while (0u == USBUART_CDCIsReady());
            USBUART_PutCRLF();
            }
        }
        
        else
        {
            LCD_Position(1,0);
            LCD_PrintString("W: ");
            LCD_Position(1,3);
            LCD_PrintString("0");
            //Conditions for the negative values of ADC output
            if(adc_mv_neg == 0)
            {
                LCD_Position(0,3);
                LCD_PrintNumber(adc_mv_neg);
                LCD_Position(0,4);
                LCD_PrintString(" ");
            }
            if(adc_mv_neg <= 9)
            {
                LCD_Position(0,3);
                LCD_PrintString("-");
                LCD_Position(0,4);
                LCD_PrintNumber(adc_mv_neg);
                LCD_Position(0,5);
                LCD_PrintString(" ");
            }
            if(adc_mv_neg >= 10 && adc_mv_neg < 100)
            {
                LCD_Position(0,3);
                LCD_PrintString("-");
                LCD_Position(0,4);
                LCD_PrintNumber(adc_mv_neg);
                LCD_Position(0,6);
                LCD_PrintString(" ");
            }
            if(adc_mv_neg >= 100 && adc_mv_neg <1000)
            {
                LCD_Position(0,3);
                LCD_PrintString("-");
                LCD_Position(0,4);
                LCD_PrintNumber(adc_mv_neg);
                LCD_Position(0,7);
                LCD_PrintString(" ");
            }
            if(adc_mv_neg >= 1000)
            {
                LCD_Position(0,3);
                LCD_PrintString("-");
                LCD_Position(0,4);
                LCD_PrintNumber(adc_mv_neg);
                LCD_Position(0,8);
                LCD_PrintString(" ");
            }
            LCD_Position(0,9);
            LCD_PrintString("mV");
            LCD_Position(1,9);
            LCD_PrintString("g");
            // UART Part 
            if (0u != USBUART_GetConfiguration())
            {
                while (0u == USBUART_CDCIsReady());
                USBUART_PutData(volts, 5);
                while (0u == USBUART_CDCIsReady());
                USBUART_PutString("-");
                while (0u == USBUART_CDCIsReady());
                itoa(adc_mv_neg, print, 10);
                display(print, 0);
                while (0u == USBUART_CDCIsReady());
                USBUART_PutData(buffer, 10);
                while (0u == USBUART_CDCIsReady());
                USBUART_PutCRLF();
                while (0u == USBUART_CDCIsReady());
                USBUART_PutData(grams, 5);
                while (0u == USBUART_CDCIsReady());
                USBUART_PutString("0");
                while (0u == USBUART_CDCIsReady());
                USBUART_PutCRLF();
                while (0u == USBUART_CDCIsReady());
                USBUART_PutCRLF();
            }
        }
        CyDelay(1000);
        LCD_ClearDisplay();
    }
}

/* [] END OF FILE */
