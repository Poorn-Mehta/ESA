/*******************************************************************************
* File Name: OA_2_PM.c
* Version 1.90
*
* Description:
*  This file provides the power management source code to the API for the 
*  OpAmp (Analog Buffer) component.
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

static OA_2_BACKUP_STRUCT  OA_2_backup;


/*******************************************************************************  
* Function Name: OA_2_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration registers.
* 
* Parameters:
*  void
* 
* Return:
*  void
*
*******************************************************************************/
void OA_2_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: OA_2_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration registers.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void OA_2_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: OA_2_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  OA_2_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void OA_2_Sleep(void) 
{
    /* Save OpAmp enable state */
    if((OA_2_PM_ACT_CFG_REG & OA_2_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        OA_2_backup.enableState = 1u;
         /* Stops the component */
         OA_2_Stop();
    }
    else
    {
        /* Component is disabled */
        OA_2_backup.enableState = 0u;
    }
    /* Saves the configuration */
    OA_2_SaveConfig();
}


/*******************************************************************************  
* Function Name: OA_2_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  OA_2_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void OA_2_Wakeup(void) 
{
    /* Restore the user configuration */
    OA_2_RestoreConfig();

    /* Enables the component operation */
    if(OA_2_backup.enableState == 1u)
    {
        OA_2_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
