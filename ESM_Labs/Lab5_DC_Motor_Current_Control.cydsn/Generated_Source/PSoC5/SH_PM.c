/*******************************************************************************
* File Name: SH.c
* Version 1.40
*
* Description:
*  This file provides the power manager source code to the API for 
*  the SAMPLE/TRACK AND HOLD component.
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

static SH_backupStruct  SH_backup;


/*******************************************************************************
* Function Name: SH_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*  
* Parameters:  
*  void.
*
* Return: 
*  void.
*
*******************************************************************************/
void SH_SaveConfig(void) 
{
    /* Nothing to save before entering into sleep mode as all the registers used 
       here are retention registers. */
}


/*******************************************************************************
* Function Name: SH_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void.
*
* Return: 
*  void
*
*******************************************************************************/
void SH_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************
* Function Name: SH_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  SH_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void SH_Sleep(void) 
{
    /* Save TIA enable state */
    if((SH_PM_ACT_CFG_REG & SH_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        SH_backup.enableState = 1u;
        /* Stop the configuration */
        SH_Stop();
    }
    else
    {
        /* Component is disabled */
        SH_backup.enableState = 0u;
    }
    /* Saves the user configuration */
    SH_SaveConfig();
}


/*******************************************************************************
* Function Name: SH_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  void
*
* Global variables:
*  SH_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void SH_Wakeup(void) 
{
    /* Restore the user configuration */
    SH_RestoreConfig();
    
    /* Enable's the component operation */
    if(SH_backup.enableState == 1u)
    {
        SH_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
