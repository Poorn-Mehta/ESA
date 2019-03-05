/* ========================================
 * ECEN 5053-003 ESA LAB 6 (PID Control)
 * 
 * Created by: Rushi James Macwan and 
 *             Poorn Mehta
 *
 * FALL 2018 - 12/08/2018
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

//#define USBFS_DEVICE    (0u)
//#define USBUART_BUFFER_SIZE (64u)

#define SAMPLES 200
//#define p 130
//#define d 130
//#define i 1000
#define p 150
#define d 100
#define i 800

#define ref 100

/*.................................Variables............................................*/

//uint8_t buffer[USBUART_BUFFER_SIZE];     
//uint8_t buffer2[USBUART_BUFFER_SIZE]; 

int32 Vmeas, Vmeas_last, Vmeas_delta, Verror, Vmeas_buffer[SAMPLES];
int8 Vmeas_raw;
int32 Verror_sum, Verror_sum_limited = 1000;
int32 Kd_scale_factor = p, Kp_scale_factor = d, Ki_scale_factor = i;
int32 Kd_term, Kp_term, Ki_term, FF_term = ref;
int32 Vout;
//int32 Vref = ref;
int32 Vref = ref+20;
//int32 Vref = (ref+20)*1.25;  // input set for 100 --> output obtained for 83 ; multiply input by 1.203 to compensate for the error

uint8 dac_in;
uint32 loop_count;

uint8 x; // can read upto 230 for example: 230/1.25

int32 Kp = 1000, Kd = 3000, Ki = 1000;
//int32 Kp = 13, Kd = 500, Ki = 100;
//int32 Kp = 13, Kd = 3, Ki = -3;
//int32 Kp = 30, Kd = -15, Ki = 7;
//int32 Kp = 40, Kd = -15, Ki = 8; // final one (new one)
//int32 Kp = 3, Kd = -7, Ki = 8;
//int32 Kp = 4, Kd = -10, Ki = 8;
//int32 Kp = 8, Kd = -10, Ki = 5;
//int32 Kp = 15, Kd = -10, Ki = 3;
//int32 Kp = 30, Kd = -30, Ki = 8;



//uint64 Vout_x;


//char print[6];
//char n;
//uint8 mV[5] = {"CN: "}; 
//
//void display(char *ptr, char ID)
//{
//    for(n = 0; n < 10; n++)
//    {
//        if(ID == 0)     buffer[n] = ' ';
//        else    buffer2[n] = ' ';
//    }
//     for(n = 0; *ptr != 0; n++, ptr ++)
//    {
//        if(ID == 0)     buffer[n] = (uint8_t)(*ptr);
//        else        buffer2[n] = (uint8_t)(*ptr);
//    }
//}


/*....................................MAIN..............................................*/

int main(void)
{
    CyGlobalIntEnable; 
    ADC_Start();
    DAC_1_Start(); DAC_2_Start(); // DAC_3_Start();
    OA_1_Start(); OA_2_Start(); OA_3_Start(); OA_4_Start();
    LCD_Start(); LCD_ClearDisplay();
    
//    usbuart_start(usbfs_device, usbuart_5v_operation); 
	
	/*.......while loop........*/   
    
    while(1)
    {
        DAC_2_SetValue(80);
//        x++;
//        if (0u != USBUART_IsConfigurationChanged())
//        {
//            /* Initialize IN endpoints when device is configured. */
//            if (0u != USBUART_GetConfiguration())
//            {
//                /* Enumeration is done, enable OUT endpoint to receive data 
//                 * from host. */
//                USBUART_CDC_Init();
//            }
//        }

        
//        loop_count++; // Loop count that keeps a track of the number of times the loop is executed
        Vmeas_last = Vmeas;
        
        ADC_StartConvert();
        ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
        Vmeas_raw = ADC_GetResult8();
//        Vmeas_raw = ADC_Read8();
        Vmeas = (uint8)Vmeas_raw;
//        Vmeas = Vmeas_raw;
        
        Vmeas_buffer[loop_count] = Vmeas;
        
        
        
		/**********Kd term************/
        
        if(loop_count == 1)
        {
            Vmeas_delta = 0;
        }
        else
        {
            Vmeas_delta = Vmeas - Vmeas_last;
        }
        
        Kd_term = Kd * Vmeas_delta / Kd_scale_factor;
        if(Kd_term > d) {Kd_term = d;}
        if(Kd_term < -d) {Kd_term = -d;}
            	
		/**********Kd term************/
        
        
        
        /**********Kp term************/
        
        Verror = Vref - Vmeas;
        Kp_term = Kp * Verror / Kp_scale_factor;
        if(Kp_term > p) {Kp_term = p;}
        if(Kp_term < -p) {Kp_term = -p;}
        
        /**********Kp term************/
        
        
        
        /**********Ki term************/
        
        Verror_sum += Verror;
        if(Verror_sum > Verror_sum_limited) {Verror_sum = Verror_sum_limited;}
        if(Verror_sum < -Verror_sum_limited) {Verror_sum = -Verror_sum_limited;}
        Ki_term = Ki * Verror_sum / Ki_scale_factor;
        if(Ki_term > i) {Ki_term = i;}
        if(Ki_term < -i) {Ki_term = -i;}
        
        /**********Ki term************/
        
        
        
        /***********PID term**********/
        
        Vout = FF_term + Kd_term + Kp_term + Ki_term;
        
        /***********PID term**********/
        
//        Vout_x = (uint64) (((2147483648 + Vout)/4294967295)*255);
//        dac_in = (uint8) Vout_x;
        
        if(Vout > 230)
        {
            dac_in = 230;
//            Vout = 255;
        }
        if(Vout < 0)
        {
            dac_in = 0;
//            Vout = 0;
        }
        else
        {
            dac_in = Vout;
        }
        
//        dac_in = 110;
//        CyDelay(1000);
        x = (uint8)(2*dac_in + 30)/1.25;
        DAC_1_SetValue(x);
//        DAC_3_SetValue(Vmeas); 
//        DAC_3_SetValue(dac_in);
        
//        {
//            loop_count = 0;
////            dac_in = 0;
//        }
//        
//        else
        {
            LCD_Position(0,0);
            LCD_PrintString("Dc: ");		
            LCD_Position(0,4);
            LCD_PrintNumber(dac_in-20);
            LCD_Position(0,8);
            LCD_PrintString("Vm: ");
            LCD_Position(0,12);
            LCD_PrintNumber(Vmeas);
            LCD_Position(1,0);
            LCD_PrintString("Vr: ");
            LCD_Position(1,4);
            LCD_PrintNumber(Vref-20);
//            CyDelay(250);
            LCD_ClearDisplay();
        }
        
//        if (0u != USBUART_GetConfiguration())
//        {
//            itoa(dac_in, print, 10);
//            display(print, 0);
//            itoa(Vref, print, 10);
//            display(print, 1);
//            while (0u == USBUART_CDCIsReady());
//            USBUART_PutData(mV, 5);
//            while (0u == USBUART_CDCIsReady());
//            USBUART_PutData(buffer, 10);
//            while (0u == USBUART_CDCIsReady());
//            USBUART_PutCRLF();
//            while (0u == USBUART_CDCIsReady());
//            USBUART_PutData(mV, 5);
//            while (0u == USBUART_CDCIsReady());
//            USBUART_PutData(buffer2, 10);
//            while (0u == USBUART_CDCIsReady());
//            USBUART_PutCRLF();
//            while (0u == USBUART_CDCIsReady());
//            USBUART_PutCRLF();
//        }
        
        
      
    }
}
