/*******************************************************************************
* File Name: dso_pin1.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_dso_pin1_H) /* Pins dso_pin1_H */
#define CY_PINS_dso_pin1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "dso_pin1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 dso_pin1__PORT == 15 && ((dso_pin1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    dso_pin1_Write(uint8 value);
void    dso_pin1_SetDriveMode(uint8 mode);
uint8   dso_pin1_ReadDataReg(void);
uint8   dso_pin1_Read(void);
void    dso_pin1_SetInterruptMode(uint16 position, uint16 mode);
uint8   dso_pin1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the dso_pin1_SetDriveMode() function.
     *  @{
     */
        #define dso_pin1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define dso_pin1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define dso_pin1_DM_RES_UP          PIN_DM_RES_UP
        #define dso_pin1_DM_RES_DWN         PIN_DM_RES_DWN
        #define dso_pin1_DM_OD_LO           PIN_DM_OD_LO
        #define dso_pin1_DM_OD_HI           PIN_DM_OD_HI
        #define dso_pin1_DM_STRONG          PIN_DM_STRONG
        #define dso_pin1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define dso_pin1_MASK               dso_pin1__MASK
#define dso_pin1_SHIFT              dso_pin1__SHIFT
#define dso_pin1_WIDTH              1u

/* Interrupt constants */
#if defined(dso_pin1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in dso_pin1_SetInterruptMode() function.
     *  @{
     */
        #define dso_pin1_INTR_NONE      (uint16)(0x0000u)
        #define dso_pin1_INTR_RISING    (uint16)(0x0001u)
        #define dso_pin1_INTR_FALLING   (uint16)(0x0002u)
        #define dso_pin1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define dso_pin1_INTR_MASK      (0x01u) 
#endif /* (dso_pin1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define dso_pin1_PS                     (* (reg8 *) dso_pin1__PS)
/* Data Register */
#define dso_pin1_DR                     (* (reg8 *) dso_pin1__DR)
/* Port Number */
#define dso_pin1_PRT_NUM                (* (reg8 *) dso_pin1__PRT) 
/* Connect to Analog Globals */                                                  
#define dso_pin1_AG                     (* (reg8 *) dso_pin1__AG)                       
/* Analog MUX bux enable */
#define dso_pin1_AMUX                   (* (reg8 *) dso_pin1__AMUX) 
/* Bidirectional Enable */                                                        
#define dso_pin1_BIE                    (* (reg8 *) dso_pin1__BIE)
/* Bit-mask for Aliased Register Access */
#define dso_pin1_BIT_MASK               (* (reg8 *) dso_pin1__BIT_MASK)
/* Bypass Enable */
#define dso_pin1_BYP                    (* (reg8 *) dso_pin1__BYP)
/* Port wide control signals */                                                   
#define dso_pin1_CTL                    (* (reg8 *) dso_pin1__CTL)
/* Drive Modes */
#define dso_pin1_DM0                    (* (reg8 *) dso_pin1__DM0) 
#define dso_pin1_DM1                    (* (reg8 *) dso_pin1__DM1)
#define dso_pin1_DM2                    (* (reg8 *) dso_pin1__DM2) 
/* Input Buffer Disable Override */
#define dso_pin1_INP_DIS                (* (reg8 *) dso_pin1__INP_DIS)
/* LCD Common or Segment Drive */
#define dso_pin1_LCD_COM_SEG            (* (reg8 *) dso_pin1__LCD_COM_SEG)
/* Enable Segment LCD */
#define dso_pin1_LCD_EN                 (* (reg8 *) dso_pin1__LCD_EN)
/* Slew Rate Control */
#define dso_pin1_SLW                    (* (reg8 *) dso_pin1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define dso_pin1_PRTDSI__CAPS_SEL       (* (reg8 *) dso_pin1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define dso_pin1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) dso_pin1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define dso_pin1_PRTDSI__OE_SEL0        (* (reg8 *) dso_pin1__PRTDSI__OE_SEL0) 
#define dso_pin1_PRTDSI__OE_SEL1        (* (reg8 *) dso_pin1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define dso_pin1_PRTDSI__OUT_SEL0       (* (reg8 *) dso_pin1__PRTDSI__OUT_SEL0) 
#define dso_pin1_PRTDSI__OUT_SEL1       (* (reg8 *) dso_pin1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define dso_pin1_PRTDSI__SYNC_OUT       (* (reg8 *) dso_pin1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(dso_pin1__SIO_CFG)
    #define dso_pin1_SIO_HYST_EN        (* (reg8 *) dso_pin1__SIO_HYST_EN)
    #define dso_pin1_SIO_REG_HIFREQ     (* (reg8 *) dso_pin1__SIO_REG_HIFREQ)
    #define dso_pin1_SIO_CFG            (* (reg8 *) dso_pin1__SIO_CFG)
    #define dso_pin1_SIO_DIFF           (* (reg8 *) dso_pin1__SIO_DIFF)
#endif /* (dso_pin1__SIO_CFG) */

/* Interrupt Registers */
#if defined(dso_pin1__INTSTAT)
    #define dso_pin1_INTSTAT            (* (reg8 *) dso_pin1__INTSTAT)
    #define dso_pin1_SNAP               (* (reg8 *) dso_pin1__SNAP)
    
	#define dso_pin1_0_INTTYPE_REG 		(* (reg8 *) dso_pin1__0__INTTYPE)
#endif /* (dso_pin1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_dso_pin1_H */


/* [] END OF FILE */
