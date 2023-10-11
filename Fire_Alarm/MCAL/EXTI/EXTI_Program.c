/*
*    EXTI_Program.c
*    Name : Omar Elsherif
*    Version: 1.0
*    Date: 12-9-2023
*    Desc: Code file contains the code for External interrupt driver 
*/

// Include header files
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../DIO/DIO_Interface.h"
#include "EXTI_Register.h"
#include "EXTI_Config.h"

// Function to initialize the external interrupt
void EXTI_VoidInit(u8 arr[])
{
	// Loop over interrupts to be enabled
	for(u8 i=0; i<=sizeof(arr)/sizeof(arr[0]); i++)
	{
		// INT0
		if(INT0_NUM == arr[i] && INT0_EN == ENABLE)
		{
			// Switch over ISC mode
			switch(ISC_MODE)
			{
				// Low level
				case LOW_LEVEL:
					CLR_BIT(MCUCR, ISC00);
					CLR_BIT(MCUCR, ISC01);
					break;
				// Any logical change
				case OCH:
					SET_BIT(MCUCR, ISC00);
					CLR_BIT(MCUCR, ISC01);
					break;
				// Falling edge
				case FALLING:
					CLR_BIT(MCUCR, ISC00);
					SET_BIT(MCUCR, ISC01);
					break;
				// Raising edge
				case RAISING:
					SET_BIT(MCUCR, ISC00);
					SET_BIT(MCUCR, ISC01);
					break;
			}

			// Enable the interrupt
			SET_BIT(GICR, INT0);
		}

		// INT1
		if(INT1_NUM == arr[i] && INT1_EN == ENABLE)
		{
			// Switch over ISC mode
			switch(ISC_MODE)
			{
				// Low level
				case LOW_LEVEL:
					CLR_BIT(MCUCR, ISC10);
					CLR_BIT(MCUCR, ISC11);
					break;
				// Any logical change
				case OCH:
					SET_BIT(MCUCR, ISC10);
					CLR_BIT(MCUCR, ISC11);
					break;
				// Falling edge
				case FALLING:
					CLR_BIT(MCUCR, ISC10);
					SET_BIT(MCUCR, ISC11);
					break;
				// Raising edge
				case RAISING:
					SET_BIT(MCUCR, ISC10);
					SET_BIT(MCUCR, ISC11);
					break;
			}

			// Enable the interrupt
			SET_BIT(GICR, INT1);
		}

		// INT2
		if(INT2_NUM == arr[i] && INT2_EN == ENABLE)
		{
			// Switch over ISC mode
			switch(ISC_MODE)
			{
				// Falling edge
				case FALLING:
					CLR_BIT(MCUCSR, ISC2);
					break;
				// Raising edge
				case RAISING:
					SET_BIT(MCUCSR, ISC2);
					break;
			}

			// Enable the interrupt
			SET_BIT(GICR, INT2);
		}
	}
}

// Function to enable General Interrupt Enable (GIE)
void EXTI_VoidEnableGIE(void)
{
	// Enable GIE
	SET_BIT(SREG, PIN7);
}

// Function to disable General Interrupt Enable (GIE)
void EXTI_VoidDisableGIE(void)
{
	// Disable GIE
	CLR_BIT(SREG, PIN7);
}

// INT0 ISR
void __vector_1(void)
{
    // Turn off led and buzzer
	DIO_VoidSetPinValue(PORT_B, PIN0, LOW);
	DIO_VoidSetPinValue(PORT_B, PIN1, LOW);

	// Turn on stability led and run dc motor
	DIO_VoidSetPinValue(PORT_D, PIN3, HIGH);
	DIO_VoidSetPinValue(PORT_D, PIN4, HIGH);

	// Display safe state on LCD
	LCD_VoidWriteCommand(1);
	LCD_VoidWriteString("EME MODE ON");
	LCD_VoidSetPosition(1, 0);
	LCD_VoidWriteString("YOU ARE SAFE!");
}
