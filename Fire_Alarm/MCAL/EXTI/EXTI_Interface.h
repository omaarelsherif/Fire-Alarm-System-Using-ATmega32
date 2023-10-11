/*
*    EXTI_Interface.h
*    Name : Omar Elsherif
*    Version: 1.0
*    Date: 12-9-2023
*    Desc: Header file contains functions prototypes for External interrupt driver 
*/

#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

// Functions prototypes
void EXTI_VoidInit(u8 arr[]);
void EXTI_VoidEnableGIE(void);
void EXTI_VoidDisableGIE(void);
void __vector_1(void) __attribute__((signal));

#endif
