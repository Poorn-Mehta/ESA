/*******************************************************************************
* File Name: OA_1.c
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

#include "OA_1.h"

uint8 OA_1_initVar = 0u;


/*******************************************************************************   
* Function Name: OA_1_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  OA_1_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void OA_1_Init(void) 
{
    OA_1_SetPower(OA_1_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: OA_1_Enable
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
void OA_1_Enable(void) 
{
    /* Enable negative charge pumps in ANIF */
    OA_1_PUMP_CR1_REG  |= (OA_1_PUMP_CR1_CLKSEL | OA_1_PUMP_CR1_FORCE);

    /* Enable power to buffer in active mode */
    OA_1_PM_ACT_CFG_REG |= OA_1_ACT_PWR_EN;

    /* Enable power to buffer in alternative active mode */
    OA_1_PM_STBY_CFG_REG |= OA_1_STBY_PWR_EN;
}


/*******************************************************************************
* Function Name:   OA_1_Start
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
*  OA_1_initVar: Used to check the initial configuration, modified 
*  when this function is called for the first time.
*
*******************************************************************************/
void OA_1_Start(void) 
{
    if(OA_1_initVar == 0u)
    {
        OA_1_initVar = 1u;
        OA_1_Init();
    }

    OA_1_Enable();
}


/*******************************************************************************
* Function Name: OA_1_Stop
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
void OA_1_Stop(void) 
{
    /* Disable power to buffer in active mode template */
    OA_1_PM_ACT_CFG_REG &= (uint8)(~OA_1_ACT_PWR_EN);

    /* Disable power to buffer in alternative active mode template */
    OA_1_PM_STBY_CFG_REG &= (uint8)(~OA_1_STBY_PWR_EN);
    
    /* Disable negative charge pumps for ANIF only if all ABuf is turned OFF */
    if(OA_1_PM_ACT_CFG_REG == 0u)
    {
        OA_1_PUMP_CR1_REG &= (uint8)(~(OA_1_PUMP_CR1_CLKSEL | OA_1_PUMP_CR1_FORCE));
    }
}


/*******************************************************************************
* Function Name: OA_1_SetPower
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
void OA_1_SetPower(uint8 power) 
{
    #if (CY_PSOC3 || CY_PSOC5LP)
        OA_1_CR_REG &= (uint8)(~OA_1_PWR_MASK);
        OA_1_CR_REG |= power & OA_1_PWR_MASK;      /* Set device power */
    #else
        CYASSERT(OA_1_HIGHPOWER == power);
    #endif /* CY_PSOC3 || CY_PSOC5LP */
}


/* [] END OF FILE */
