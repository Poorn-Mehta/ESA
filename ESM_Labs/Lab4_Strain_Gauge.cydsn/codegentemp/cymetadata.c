/*******************************************************************************
* File Name: cymetadata.c
* 
* PSoC Creator  4.2
*
* Description:
* This file defines all extra memory spaces that need to be included.
* This file is automatically generated by PSoC Creator.
*
********************************************************************************
* Copyright (c) 2007-2018 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#include "stdint.h"


#if defined(__GNUC__) || defined(__ARMCC_VERSION)
#ifndef CY_CONFIG_ECC_SECTION
#define CY_CONFIG_ECC_SECTION __attribute__ ((__section__(".cyconfigecc"), used))
#endif
CY_CONFIG_ECC_SECTION
#elif defined(__ICCARM__)
#pragma  location=".cyconfigecc"
#else
#error "Unsupported toolchain"
#endif
const uint8_t cy_meta_configecc[] = {
    0x01u, 0x45u, 0x00u, 0x40u, 0x01u, 0x52u, 0x00u, 0x40u,
    0x01u, 0x09u, 0x01u, 0x40u, 0x04u, 0x0Au, 0x01u, 0x40u,
    0x01u, 0x0Bu, 0x01u, 0x40u, 0x01u, 0x15u, 0x01u, 0x40u,
    0x02u, 0x17u, 0x01u, 0x40u, 0x02u, 0x19u, 0x01u, 0x40u,
    0x01u, 0x1Bu, 0x01u, 0x40u, 0x03u, 0x40u, 0x01u, 0x40u,
    0x03u, 0x41u, 0x01u, 0x40u, 0x03u, 0x42u, 0x01u, 0x40u,
    0x03u, 0x43u, 0x01u, 0x40u, 0x02u, 0x44u, 0x01u, 0x40u,
    0x01u, 0x45u, 0x01u, 0x40u, 0x03u, 0x46u, 0x01u, 0x40u,
    0x07u, 0x47u, 0x01u, 0x40u, 0x06u, 0x48u, 0x01u, 0x40u,
    0x01u, 0x49u, 0x01u, 0x40u, 0x03u, 0x4Cu, 0x01u, 0x40u,
    0x02u, 0x4Du, 0x01u, 0x40u, 0x01u, 0x51u, 0x01u, 0x40u,
    0x7Eu, 0x02u, 0x7Cu, 0x40u, 0xB5u, 0x02u, 0xB8u, 0x02u,
    0xBEu, 0x01u, 0xD8u, 0x04u, 0xDFu, 0x01u, 0x1Du, 0x02u,
    0xECu, 0x10u, 0xEAu, 0x02u, 0xEEu, 0x0Au, 0xEAu, 0x02u,
    0xEEu, 0x0Au, 0xECu, 0x10u, 0x33u, 0x81u, 0x36u, 0x40u,
    0xCCu, 0x70u, 0x9Fu, 0x01u, 0xA6u, 0x40u, 0xA7u, 0x80u,
    0x9Fu, 0x01u, 0xA6u, 0x40u, 0xA7u, 0x80u, 0x9Fu, 0x01u,
    0xA6u, 0x40u, 0xA7u, 0x80u, 0x7Cu, 0x01u, 0xDEu, 0x01u,
    0x94u, 0x01u, 0x45u, 0x08u, 0x94u, 0x01u, 0xD0u, 0x01u,
    0x08u, 0x08u, 0x0Bu, 0x04u, 0x0Fu, 0x40u, 0xA5u, 0x08u,
    0xB4u, 0x01u, 0xC2u, 0x0Eu, 0xECu, 0x08u, 0x25u, 0x10u,
    0xAEu, 0x40u, 0xAFu, 0x81u, 0xC8u, 0x20u, 0xEAu, 0x40u,
    0xEEu, 0x50u, 0xB5u, 0x10u, 0xA5u, 0x08u, 0xACu, 0x08u,
    0xAFu, 0x44u, 0xB5u, 0x08u, 0xECu, 0x08u, 0x00u, 0x2Au,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x80u, 0x00u,
    0x40u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0xC0u, 0x00u, 0x00u, 0x00u, 0x00u, 0x0Bu, 0x0Bu, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x7Fu, 0x7Fu, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x80u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x30u, 0x00u, 0x4Au, 0x00u, 0x18u, 0x01u
};

#if defined(__GNUC__) || defined(__ARMCC_VERSION)
#ifndef CY_CUST_NVL_SECTION
#define CY_CUST_NVL_SECTION __attribute__ ((__section__(".cycustnvl"), used))
#endif
CY_CUST_NVL_SECTION
#elif defined(__ICCARM__)
#pragma  location=".cycustnvl"
#else
#error "Unsupported toolchain"
#endif
const uint8_t cy_meta_custnvl[] = {
    0x00u, 0x00u, 0x40u, 0x05u
};

#if defined(__GNUC__) || defined(__ARMCC_VERSION)
#ifndef CY_WO_NVL_SECTION
#define CY_WO_NVL_SECTION __attribute__ ((__section__(".cywolatch"), used))
#endif
CY_WO_NVL_SECTION
#elif defined(__ICCARM__)
#pragma  location=".cywolatch"
#else
#error "Unsupported toolchain"
#endif
const uint8_t cy_meta_wonvl[] = {
    0xBCu, 0x90u, 0xACu, 0xAFu
};

#if defined(__GNUC__) || defined(__ARMCC_VERSION)
#ifndef CY_FLASH_PROT_SECTION
#define CY_FLASH_PROT_SECTION __attribute__ ((__section__(".cyflashprotect"), used))
#endif
CY_FLASH_PROT_SECTION
#elif defined(__ICCARM__)
#pragma  location=".cyflashprotect"
#else
#error "Unsupported toolchain"
#endif
const uint8_t cy_meta_flashprotect[] = {
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u
};

#if defined(__GNUC__) || defined(__ARMCC_VERSION)
#ifndef CY_META_SECTION
#define CY_META_SECTION __attribute__ ((__section__(".cymeta"), used))
#endif
CY_META_SECTION
#elif defined(__ICCARM__)
#pragma  location=".cymeta"
#else
#error "Unsupported toolchain"
#endif
const uint8_t cy_metadata[] = {
    0x00u, 0x01u, 0x2Eu, 0x12u, 0x30u, 0x69u, 0x00u, 0x01u,
    0x00u, 0x00u, 0x00u, 0x00u
};
