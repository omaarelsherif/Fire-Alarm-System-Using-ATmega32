/*
*    EXTI_Config.h
*    Name : Omar Elsherif
*    Version: 1.0
*    Date: 12-9-2023
*    Desc: Header file contains configurations for External interrupt driver 
*/

#ifndef EXTI_CONFIG_H
#define EXTI_CONFIG_H

// Include DIO configurations
#include "../DIO/DIO_Config.h"

// Macros to define ISC modes
#define LOW_LEVEL   0
#define OCH			1
#define FALLING		2
#define RAISING		3
#define ISC_MODE    FALLING

// Macros to define ISC bits to set ISC mode for INT0, INT1 and INT2
#define ISC00	0
#define ISC01	1
#define ISC10	2
#define ISC11	3
#define ISC2 	6

// Macros to define intrrupt flags for INT0, INT1 and INT2
#define INTF0	6
#define INTF1	7
#define INTF2	5

// Macros to define interrupt requests
#define INT0	6
#define INT1	7
#define INT2	5

// Macros to define interrupt numbers
#define INT0_NUM	0
#define INT1_NUM	1
#define INT2_NUM	2

// Macros to define enable & disable
#define DISABLE  	0
#define ENABLE   	1
#define INT0_EN 	ENABLE
#define INT1_EN  	ENABLE
#define INT2_EN  	ENABLE

#endif
