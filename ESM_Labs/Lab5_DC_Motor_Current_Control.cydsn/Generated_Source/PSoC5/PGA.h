/*******************************************************************************
* File Name: PGA.h  
* Version 2.0
*
* Description:
*  This file contains the function prototypes and constants used in
*  the PGA User Module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PGA_PGA_H) 
#define CY_PGA_PGA_H 

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PGA_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


#if(!CY_PSOC5A)
    #if(CYDEV_VARIABLE_VDDA == 1)
        #if (!defined(CY_LIB_SC_BST_CLK_EN))
            #error Component PGA_v2_0 requires cy_boot v3.30 or later
        #endif /* (!defined(CY_LIB_SC_BST_CLK_EN)) */
    #endif /* CYDEV_VARIABLE_VDDA == 1 */
#endif /* (!CY_PSOC5A) */

/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
    uint8   enableState;
    uint8   scCR1Reg;
    uint8   scCR2Reg;
    uint8   scCR3Reg;
}   PGA_BACKUP_STRUCT;


/* variable describes init state of the component */
extern uint8 PGA_initVar;


/***************************************
*        Function Prototypes 
***************************************/

void PGA_Start(void)                 ; 
void PGA_Stop(void)                  ; 
void PGA_SetPower(uint8 power)       ;
void PGA_SetGain(uint8 gain)         ;
void PGA_Sleep(void)                 ; 
void PGA_Wakeup(void)                ;
void PGA_SaveConfig(void)            ; 
void PGA_RestoreConfig(void)         ;
void PGA_Init(void)                  ;
void PGA_Enable(void)                ;


/***************************************
*            API Constants
***************************************/

/* Power constants for SetPower function */
#define PGA_MINPOWER                 (0x00u)
#define PGA_LOWPOWER                 (0x01u)
#define PGA_MEDPOWER                 (0x02u)
#define PGA_HIGHPOWER                (0x03u)

/* Constants for SetGain function */
#define PGA_GAIN_01                  (0x00u)
#define PGA_GAIN_02                  (0x01u)
#define PGA_GAIN_04                  (0x02u)
#define PGA_GAIN_08                  (0x03u)
#define PGA_GAIN_16                  (0x04u)
#define PGA_GAIN_24                  (0x05u)
#define PGA_GAIN_32                  (0x06u)
#define PGA_GAIN_48                  (0x07u)
#define PGA_GAIN_50                  (0x08u)
#define PGA_GAIN_MAX                 (0x08u)


/***************************************
*       Initialization Values
***************************************/

#define PGA_DEFAULT_GAIN             (3u)
#define PGA_VREF_MODE                ((1u != 0x00u) ? (0x00u) : PGA_GNDVREF_E)
#define PGA_DEFAULT_POWER            (3u)


/***************************************
*              Registers
***************************************/

#define PGA_CR0_REG                  (* (reg8 *) PGA_SC__CR0 )
#define PGA_CR0_PTR                  (  (reg8 *) PGA_SC__CR0 )
#define PGA_CR1_REG                  (* (reg8 *) PGA_SC__CR1 )
#define PGA_CR1_PTR                  (  (reg8 *) PGA_SC__CR1 )
#define PGA_CR2_REG                  (* (reg8 *) PGA_SC__CR2 )
#define PGA_CR2_PTR                  (  (reg8 *) PGA_SC__CR2 )
  /* Power manager */
#define PGA_PM_ACT_CFG_REG           (* (reg8 *) PGA_SC__PM_ACT_CFG )
#define PGA_PM_ACT_CFG_PTR           (  (reg8 *) PGA_SC__PM_ACT_CFG )  
#define PGA_PM_STBY_CFG_REG          (* (reg8 *) PGA_SC__PM_STBY_CFG )
  /* Power manager */
#define PGA_PM_STBY_CFG_PTR          (  (reg8 *) PGA_SC__PM_STBY_CFG )  
#define PGA_BSTCLK_REG               (* (reg8 *) PGA_SC__BST )
#define PGA_BSTCLK_PTR               (  (reg8 *) PGA_SC__BST )
/* Pump clock selectin register */
#define PGA_PUMP_CR1_REG             (* (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)
#define PGA_PUMP_CR1_PTR             (  (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)

/* Pump Register for SC block */
#define PGA_SC_MISC_REG              (* (reg8 *) CYDEV_ANAIF_RT_SC_MISC)
#define PGA_SC_MISC_PTR              (  (reg8 *) CYDEV_ANAIF_RT_SC_MISC)

/* PM_ACT_CFG (Active Power Mode CFG Register)mask */ 
#define PGA_ACT_PWR_EN               PGA_SC__PM_ACT_MSK 

/* PM_STBY_CFG (Alternate Active Power Mode CFG Register)mask */ 
#define PGA_STBY_PWR_EN              PGA_SC__PM_STBY_MSK 


/***************************************
*            Register Constants
***************************************/

/* SC_MISC constants */
#define PGA_PUMP_FORCE               (0x20u)
#define PGA_PUMP_AUTO                (0x10u)
#define PGA_DIFF_PGA_1_3             (0x02u)
#define PGA_DIFF_PGA_0_2             (0x01u)

/* ANIF.PUMP.CR1 Constants */
#define PGA_PUMP_CR1_SC_CLKSEL       (0x80u)

/* CR0 SC/CT Control Register 0 definitions */
#define PGA_MODE_PGA                 (0x0Cu)

/* CR1 SC/CT Control Register 1 definitions */

/* Bit Field  SC_COMP_ENUM */
#define PGA_COMP_MASK                (0x0Cu)
#define PGA_COMP_3P0PF               (0x00u)
#define PGA_COMP_3P6PF               (0x04u)
#define PGA_COMP_4P35PF              (0x08u)
#define PGA_COMP_5P1PF               (0x0Cu)

/* Bit Field  SC_DIV2_ENUM */
#define PGA_DIV2_MASK                (0x10u)
#define PGA_DIV2_DISABLE             (0x00u)
#define PGA_DIV2_ENABLE              (0x10u)

/* Bit Field  SC_DRIVE_ENUM */
#define PGA_DRIVE_MASK               (0x03u)
#define PGA_DRIVE_280UA              (0x00u)
#define PGA_DRIVE_420UA              (0x01u)
#define PGA_DRIVE_530UA              (0x02u)
#define PGA_DRIVE_650UA              (0x03u)

/* Bit Field  SC_PGA_MODE_ENUM */
#define PGA_PGA_MODE_MASK            (0x20u)
#define PGA_PGA_INV                  (0x00u)
#define PGA_PGA_NINV                 (0x20u)

/* CR2 SC/CT Control Register 2 definitions */

/* Bit Field  SC_BIAS_CONTROL_ENUM */
#define PGA_BIAS_MASK                (0x01u)
#define PGA_BIAS_NORMAL              (0x00u)
#define PGA_BIAS_LOW                 (0x01u)

/* Bit Field  SC_PGA_GNDVREF_ENUM  */
#define PGA_GNDVREF_MASK             (0x80u)
#define PGA_GNDVREF_DI               (0x00u)
#define PGA_GNDVREF_E                (0x80u)

/* Bit Field  SC_R20_40B_ENUM */
#define PGA_R20_40B_MASK             (0x02u)
#define PGA_R20_40B_40K              (0x00u)
#define PGA_R20_40B_20K              (0x02u)

/* Bit Field  SC_REDC_ENUM */
#define PGA_REDC_MASK                (0x0Cu)
#define PGA_REDC_00                  (0x00u)
#define PGA_REDC_01                  (0x04u)
#define PGA_REDC_10                  (0x08u)
#define PGA_REDC_11                  (0x0Cu)

/* Bit Field  SC_RVAL_ENUM */
#define PGA_RVAL_MASK                (0x70u)
#define PGA_RVAL_0K                  (0x00u)
#define PGA_RVAL_40K                 (0x10u)
#define PGA_RVAL_120K                (0x20u)
#define PGA_RVAL_280K                (0x30u)
#define PGA_RVAL_600K                (0x40u)
#define PGA_RVAL_460K                (0x60u)
#define PGA_RVAL_620K                (0x50u)
#define PGA_RVAL_470K                (0x60u)
#define PGA_RVAL_490K                (0x70u)

/* Bit Field  PGA_GAIN_ENUM */
#define PGA_PGA_GAIN_MASK            (0x72u)
#define PGA_PGA_GAIN_01              (0x00u)
#define PGA_PGA_GAIN_02              (0x10u)
#define PGA_PGA_GAIN_04              (0x20u)
#define PGA_PGA_GAIN_08              (0x30u)
#define PGA_PGA_GAIN_16              (0x40u)
#define PGA_PGA_GAIN_24              (0x50u)
#define PGA_PGA_GAIN_25              (0x70u)
#define PGA_PGA_GAIN_32              (0x52u)
#define PGA_PGA_GAIN_48              (0x62u)
#define PGA_PGA_GAIN_50              (0x72u)

#define PGA_BST_CLK_EN               (0x08u)
#define PGA_BST_CLK_INDEX_MASK       (0x07u)
#define PGA_PM_ACT_CFG_MASK          (0x0Fu)

/* Constant for VDDA Threshold */
#define PGA_CYDEV_VDDA_MV       (CYDEV_VDDA_MV)
#define PGA_MINIMUM_VDDA_THRESHOLD_MV   (2700u)

/*******************************************************************************
* Following code are OBSOLETE and must not be used starting from PGA 2.0
*******************************************************************************/
#define PGA_BST_REG            (PGA_BSTCLK_REG)
#define PGA_BST_PTR            (PGA_BSTCLK_PTR)
#define PGA_SC_REG_CLR         (0x00u)
#define PGA_BST_REG_EN         (0x08u)


#endif /* CY_PGA_PGA_H */


/* [] END OF FILE */
