/*******************************************************************************
* File Name: Blanking.h  
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

#if !defined(CY_PINS_Blanking_H) /* Pins Blanking_H */
#define CY_PINS_Blanking_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Blanking_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Blanking__PORT == 15 && ((Blanking__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Blanking_Write(uint8 value);
void    Blanking_SetDriveMode(uint8 mode);
uint8   Blanking_ReadDataReg(void);
uint8   Blanking_Read(void);
void    Blanking_SetInterruptMode(uint16 position, uint16 mode);
uint8   Blanking_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Blanking_SetDriveMode() function.
     *  @{
     */
        #define Blanking_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Blanking_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Blanking_DM_RES_UP          PIN_DM_RES_UP
        #define Blanking_DM_RES_DWN         PIN_DM_RES_DWN
        #define Blanking_DM_OD_LO           PIN_DM_OD_LO
        #define Blanking_DM_OD_HI           PIN_DM_OD_HI
        #define Blanking_DM_STRONG          PIN_DM_STRONG
        #define Blanking_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Blanking_MASK               Blanking__MASK
#define Blanking_SHIFT              Blanking__SHIFT
#define Blanking_WIDTH              1u

/* Interrupt constants */
#if defined(Blanking__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Blanking_SetInterruptMode() function.
     *  @{
     */
        #define Blanking_INTR_NONE      (uint16)(0x0000u)
        #define Blanking_INTR_RISING    (uint16)(0x0001u)
        #define Blanking_INTR_FALLING   (uint16)(0x0002u)
        #define Blanking_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Blanking_INTR_MASK      (0x01u) 
#endif /* (Blanking__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Blanking_PS                     (* (reg8 *) Blanking__PS)
/* Data Register */
#define Blanking_DR                     (* (reg8 *) Blanking__DR)
/* Port Number */
#define Blanking_PRT_NUM                (* (reg8 *) Blanking__PRT) 
/* Connect to Analog Globals */                                                  
#define Blanking_AG                     (* (reg8 *) Blanking__AG)                       
/* Analog MUX bux enable */
#define Blanking_AMUX                   (* (reg8 *) Blanking__AMUX) 
/* Bidirectional Enable */                                                        
#define Blanking_BIE                    (* (reg8 *) Blanking__BIE)
/* Bit-mask for Aliased Register Access */
#define Blanking_BIT_MASK               (* (reg8 *) Blanking__BIT_MASK)
/* Bypass Enable */
#define Blanking_BYP                    (* (reg8 *) Blanking__BYP)
/* Port wide control signals */                                                   
#define Blanking_CTL                    (* (reg8 *) Blanking__CTL)
/* Drive Modes */
#define Blanking_DM0                    (* (reg8 *) Blanking__DM0) 
#define Blanking_DM1                    (* (reg8 *) Blanking__DM1)
#define Blanking_DM2                    (* (reg8 *) Blanking__DM2) 
/* Input Buffer Disable Override */
#define Blanking_INP_DIS                (* (reg8 *) Blanking__INP_DIS)
/* LCD Common or Segment Drive */
#define Blanking_LCD_COM_SEG            (* (reg8 *) Blanking__LCD_COM_SEG)
/* Enable Segment LCD */
#define Blanking_LCD_EN                 (* (reg8 *) Blanking__LCD_EN)
/* Slew Rate Control */
#define Blanking_SLW                    (* (reg8 *) Blanking__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Blanking_PRTDSI__CAPS_SEL       (* (reg8 *) Blanking__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Blanking_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Blanking__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Blanking_PRTDSI__OE_SEL0        (* (reg8 *) Blanking__PRTDSI__OE_SEL0) 
#define Blanking_PRTDSI__OE_SEL1        (* (reg8 *) Blanking__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Blanking_PRTDSI__OUT_SEL0       (* (reg8 *) Blanking__PRTDSI__OUT_SEL0) 
#define Blanking_PRTDSI__OUT_SEL1       (* (reg8 *) Blanking__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Blanking_PRTDSI__SYNC_OUT       (* (reg8 *) Blanking__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Blanking__SIO_CFG)
    #define Blanking_SIO_HYST_EN        (* (reg8 *) Blanking__SIO_HYST_EN)
    #define Blanking_SIO_REG_HIFREQ     (* (reg8 *) Blanking__SIO_REG_HIFREQ)
    #define Blanking_SIO_CFG            (* (reg8 *) Blanking__SIO_CFG)
    #define Blanking_SIO_DIFF           (* (reg8 *) Blanking__SIO_DIFF)
#endif /* (Blanking__SIO_CFG) */

/* Interrupt Registers */
#if defined(Blanking__INTSTAT)
    #define Blanking_INTSTAT            (* (reg8 *) Blanking__INTSTAT)
    #define Blanking_SNAP               (* (reg8 *) Blanking__SNAP)
    
	#define Blanking_0_INTTYPE_REG 		(* (reg8 *) Blanking__0__INTTYPE)
#endif /* (Blanking__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Blanking_H */


/* [] END OF FILE */
