/*******************************************************************************
* File Name: OA_2.c
* Version 1.90
*
* Description:
*  This file provides the source code to the API for OpAmp (Analog Buffer) 
*  Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "OA_2.h"

uint8 OA_2_initVar = 0u;


/*******************************************************************************   
* Function Name: OA_2_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  OA_2_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void OA_2_Init(void) 
{
    OA_2_SetPower(OA_2_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: OA_2_Enable
********************************************************************************
*
* Summary:
*  Enables the OpAmp block operation
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void OA_2_Enable(void) 
{
    /* Enable negative charge pumps in ANIF */
    OA_2_PUMP_CR1_REG  |= (OA_2_PUMP_CR1_CLKSEL | OA_2_PUMP_CR1_FORCE);

    /* Enable power to buffer in active mode */
    OA_2_PM_ACT_CFG_REG |= OA_2_ACT_PWR_EN;

    /* Enable power to buffer in alternative active mode */
    OA_2_PM_STBY_CFG_REG |= OA_2_STBY_PWR_EN;
}


/*******************************************************************************
* Function Name:   OA_2_Start
********************************************************************************
*
* Summary:
*  The start function initializes the Analog Buffer with the default values and 
*  sets the power to the given level. A power level of 0, is same as 
*  executing the stop function.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  OA_2_initVar: Used to check the initial configuration, modified 
*  when this function is called for the first time.
*
*******************************************************************************/
void OA_2_Start(void) 
{
    if(OA_2_initVar == 0u)
    {
        OA_2_initVar = 1u;
        OA_2_Init();
    }

    OA_2_Enable();
}


/*******************************************************************************
* Function Name: OA_2_Stop
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
void OA_2_Stop(void) 
{
    /* Disable power to buffer in active mode template */
    OA_2_PM_ACT_CFG_REG &= (uint8)(~OA_2_ACT_PWR_EN);

    /* Disable power to buffer in alternative active mode template */
    OA_2_PM_STBY_CFG_REG &= (uint8)(~OA_2_STBY_PWR_EN);
    
    /* Disable negative charge pumps for ANIF only if all ABuf is turned OFF */
    if(OA_2_PM_ACT_CFG_REG == 0u)
    {
        OA_2_PUMP_CR1_REG &= (uint8)(~(OA_2_PUMP_CR1_CLKSEL | OA_2_PUMP_CR1_FORCE));
    }
}


/*******************************************************************************
* Function Name: OA_2_SetPower
********************************************************************************
*
* Summary:
*  Sets power level of Analog buffer.
*
* Parameters: 
*  power: PSoC3: Sets power level between low (1) and high power (3).
*         PSoC5: Sets power level High (0)
*
* Return:
*  void
*
**********************************************************************************/
void OA_2_SetPower(uint8 power) 
{
    #if (CY_PSOC3 || CY_PSOC5LP)
        OA_2_CR_REG &= (uint8)(~OA_2_PWR_MASK);
        OA_2_CR_REG |= power & OA_2_PWR_MASK;      /* Set device power */
    #else
        CYASSERT(OA_2_HIGHPOWER == power);
    #endif /* CY_PSOC3 || CY_PSOC5LP */
}


/* [] END OF FILE */
