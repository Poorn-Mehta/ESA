// This file tells the compiler details about the particular PSoC chip in use.
 #include "project.h"
 #include "stdio.h"	// This brings in libraray functions needed for using the UARI.

 #define SAMPLE_LIMIT 300


 uint8 current_l = 50, source = 0 ;
 uint32 adc_wait_count, last_adc_wait_count, test_mode = 0 ;
 uint32 button_not_pushed_count ;
 uint16 adc_result ;	// This result will always be positive based on the ADC configuration used.
 uint16 adc_limit = 4000 ; // Using 12 resolution, the maximum value is 4095.
 int sample_count = 0 ;	


 // Variables used for PID control:
 uint8 Vmeas_raw, Vmeas_buffer[SAMPLE_LIMIT] ;
 uint32 Vmeas_buffer_index = 0, buffer_limit_reached ;
 int32 Vref = 120, Vmeas, Vmeas_last, Vmeas_delta, Verror, Vout, Vout_limited ; // Signed math is required here.
 int32 Verror_sum, Verror_sum_limit = 10000 ;
 int32 Kp = 33, Kd = -105, Ki = 12; // PID constants.
 int32 Kp_term, Kd_term, Ki_term, FF_term = 100 ; // PID variables.
 int32 Kp_term_limited, Kd_term_limited, Ki_term_limited ; // PID variables.
 // uint32 Kp_term_overflow_count, Kp_term_underflow_count, 
 uint32 loop_count ;
 // uint32 Kd_term_overflow_count, Kd_term_underflow_count ;
 uint32 Kd_display_gain = 8 ;
 uint32 Ki_term_overflow_count, Ki_term_underflow_count ;
 uint32 Vout_term_underflow_count, Vout_term_overflow_count ;
 int32 Kp_scale_factor = 128, Kd_scale_factor = 128, Ki_scale_factor = 1024;
 int32 feedforward_only = 0;

 int main()
 {
 	ADC_Start(); ADC_StartConvert();
 	DAC_1_Start(); DAC_2_Start(); DAC_3_Start();
 	OA_1_Start(); OA_2_Start(); OA_3_Start(); OA_4_Start();

 	while(1)
	{
		loop_count++;
		Vmeas_last = Vmeas;
		adc_wait_count = 0;
        DAC_3_SetValue(Vref);

		
		ADC_StartConvert();

		while(ADC_IsEndConversion(ADC_RETURN_STATUS) == 0)
        {
			adc_wait_count++;
        }

		last_adc_wait_count = adc_wait_count;

		Vmeas_raw = (int32)ADC_GetResult8();
		DAC_2_SetValue(127+Vmeas_raw);

		Vmeas_buffer[loop_count] = Vmeas_raw;
		Vmeas = (int32)Vmeas_raw;

		if(loop_count == 1)
		{
			Vmeas_delta = 0;
		}
		else
		{
			Vmeas_delta = Vmeas - Vmeas_last;
		}

		//DAC_3_SetValue(127 + Kd_display_gain*Vmeas_delta);

		// Derivative term

		Kd_term = (Kd*Vmeas_delta) / Kd_scale_factor ;

		Kd_term_limited  =Kd_term;

		if(Kd_term_limited > 127)
		{
			Kd_term_limited = 127;
		}
		if(Kd_term_limited < -127)
		{
			Kd_term_limited = -127;
		}

		// Proportional Term

		Verror = Vref - Vmeas;

		Kp_term = (Kp*Verror)/Kp_scale_factor;

		Kp_term_limited  =Kp_term;

		if(Kp_term_limited > 127)
		{
			Kp_term_limited = 127;
		}
		if(Kp_term_limited < -127)
		{
			Kp_term_limited = -127;
		}	

		// Integral term

		Verror_sum  += Verror;

		if(Verror_sum > Verror_sum_limit)
		{
			Verror_sum = Verror_sum_limit;
		}
		if(Verror_sum < -Verror_sum_limit)
		{
			Verror_sum = -Verror_sum_limit;
		}

		Ki_term = (Ki*Verror_sum) / Ki_scale_factor;

		Vout = FF_term + Kp_term + Kd_term + Ki_term;

		Vout_limited = Vout;
		if(Vout_limited > 255)
		{
			Vout_limited = 255;
		}
		if(Vout_limited < 0)
		{
			Vout_limited = 0;
		}

		DAC_1_SetValue(Vout_limited);

		if(loop_count >= SAMPLE_LIMIT)
		{
			DAC_1_SetValue(0);
			CyDelay(200);

            if(Vref == 120)
            {
                Vref = 140;
            }
            
            else if(Vref == 140)
            {
                Vref = 160;
            }
            
            else
            {
                Vref = 120;
            }
            
			Vmeas_buffer_index = 0;

            Verror_sum = 0;
            Vmeas = 0;
            Vmeas_last = Vmeas;
			loop_count = 0; //BREAK POINT

		}





	}


 }