/*
*    EXTI_Register.h
*    Name : Omar Elsherif
*    Version: 1.0
*    Date: 12-9-2023
*    Desc: Header file contains registers addresses for External interrupt driver 
*/

#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

// Macros to define registers addreses
#define MCUCR    *((volatile u8 *) 0x55)
#define MCUCSR   *((volatile u8 *) 0x54)
#define GICR     *((volatile u8 *) 0x5B)
#define GIFR     *((volatile u8 *) 0x5A)
#define SREG     *((volatile u8 *) 0x5F)

#endif
