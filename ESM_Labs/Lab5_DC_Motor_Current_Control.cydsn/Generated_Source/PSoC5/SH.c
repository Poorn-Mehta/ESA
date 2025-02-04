/*******************************************************************************
* File Name: SH.c
* Version 1.40
*
* Description:
*  This file provides the source code to the API for the SAMPLE/TRACK AND HOLD 
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "SH.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

uint8 SH_initVar = 0u;

/* static SH_backupStruct  SH_backup; */
#if (CY_PSOC5A)
    static SH_backupStruct  SH_P5backup;
#endif /* CY_PSOC5A */



/*******************************************************************************   
* Function Name: SH_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  SH_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void SH_Init(void) 
{   
    /* Configure SC Block based on selected Sample/Track type */
    #if (SH_SAMPLE_TRACK_MODE == SH_SAMPLEANDHOLD) /* Sample and hold mode */
        /* SC Block mode -  - SCxx_CR0[3:1] */
        SH_CR0_REG = SH_MODE_SAMPLEANDHOLD;
        
        /* SC Block CR1 */ 
        SH_CR1_REG = (SH_COMP_4P35PF  |
                                SH_GAIN_0DB);
        #if(SH_SAMPLE_CLOCK_EDGE == SH_EDGE_POSITIVENEGATIVE)
            SH_CR1_REG =  SH_CR1_REG  | SH_DIV2_DISABLE ;
        #else
            SH_CR1_REG =  SH_CR1_REG  | SH_DIV2_ENABLE ;
        #endif
         
        #if(SH_VREF_TYPE == SH_EXTERNAL)
            SH_CR2_REG = SH_BIAS_LOW |
                                       SH_REDC_00 | 
                                       SH_GNDVREF_DI;
        #else
            SH_CR2_REG = SH_BIAS_LOW |
                                       SH_REDC_00 | 
                                       SH_GNDVREF_E;
        #endif
    #else
        /* Track and Hold Mode */
        /* SC Block mode -  - SCxx_CR0[3:1] */
        SH_CR0_REG = SH_MODE_TRACKANDHOLD; 
        
        /* SC Block CR1 */ 
        SH_CR1_REG = SH_COMP_4P35PF  |
                                   SH_DIV2_ENABLE |
                                   SH_GAIN_0DB;
                                
        /* SC Block CR2 */
        SH_CR2_REG = SH_BIAS_LOW |
                                   SH_REDC_00 |
                                   SH_GNDVREF_E;
    #endif /* end if - Sample/Track Type */
    
    /* Enable SC Block clocking */
    SH_CLK_REG |= SH_CLK_EN;
    
    /* Set default power */
    SH_SetPower(SH_INIT_POWER);
}


/*******************************************************************************   
* Function Name: SH_Enable
********************************************************************************
*
* Summary:
*  Enables the Sample/Track and Hold block operation
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void SH_Enable(void) 
{
    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
    #if (CY_PSOC5A)
        if(SH_P5backup.enableState == 1u)
        {
            SH_CR1_REG = SH_P5backup.scCR1Reg;
            SH_CR2_REG = SH_P5backup.scCR2Reg;
            SH_P5backup.enableState = 0u;
        }
    #endif /* CY_PSOC5A */
    
    /* Enable power to SC block in active mode */
    SH_PM_ACT_CFG_REG |= SH_ACT_PWR_EN;
    
    /* Enable power to SC block in Alternative active mode */
    SH_PM_STBY_CFG_REG |= SH_STBY_PWR_EN;

    SH_PUMP_CR1_REG |= SH_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                SH_BSTCLK_REG &= (uint8)(~SH_BST_CLK_INDEX_MASK);
                SH_BSTCLK_REG |= SH_BST_CLK_EN | CyScBoostClk__INDEX;
                SH_SC_MISC_REG |= SH_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                SH_BSTCLK_REG &= (uint8)(~SH_BST_CLK_EN);
                SH_SC_MISC_REG &= (uint8)(~SH_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: SH_Start
********************************************************************************
*
* Summary:
*  The start function initializes the Sample and Hold with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as 
*  executing the stop function.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void SH_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(SH_initVar == 0u)
    {
        SH_Init();
        SH_initVar = 1u;
    }
    SH_Enable();
}


/*******************************************************************************
* Function Name: SH_Stop
********************************************************************************
*
* Summary:
*  Powers down amplifier to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void SH_Stop(void) 
{   
    /* Disble power to the Amp in Active mode template */
    SH_PM_ACT_CFG_REG &= (uint8)(~SH_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative Active mode template */
    SH_PM_STBY_CFG_REG &= (uint8)(~SH_STBY_PWR_EN);
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            SH_BSTCLK_REG &= (uint8)(~SH_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((SH_PM_ACT_CFG_REG & SH_PM_ACT_CFG_MASK) == 0u)
            {
                SH_SC_MISC_REG &= (uint8)(~SH_PUMP_FORCE);
                SH_PUMP_CR1_REG &= (uint8)(~SH_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
 
    /* This sets Sample and hold in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        SH_P5backup.scCR1Reg = SH_CR1_REG;
        SH_P5backup.scCR2Reg = SH_CR2_REG;
        SH_CR1_REG = 0x00u;
        SH_CR2_REG = 0x00u;
        SH_P5backup.enableState = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: SH_SetPower
********************************************************************************
*
* Summary:
*  Set the power of the Sample/Track and Hold.
*
* Parameters:
*  power: Sets power level between (0) and (3) high power
*
* Return:
*  void
*
*******************************************************************************/
void SH_SetPower(uint8 power) 
{
    uint8 tmpCR;

    /* Sets drive bits in SC Block Control Register 1:  SCxx_CR[1:0] */
    tmpCR = SH_CR1_REG & (uint8)(~SH_DRIVE_MASK);
    tmpCR |= (power & SH_DRIVE_MASK);
    SH_CR1_REG = tmpCR;
}


/* [] END OF FILE */
