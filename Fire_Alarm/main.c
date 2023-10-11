/*
 * Fire Alarm
 * Author: OmarElsherif
 */

// Include drivers
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "HAL/LCD/LCD_Interface.h"
#include "MCAL/DIO/DIO_Config.h"
#include "MCAL/DIO/DIO_Interface.h"
#include "MCAL/ADC/ADC_Interface.h"
#include <avr/delay.h>

// Function to initialize the system
void System_init()
{
	// LCD initialization
	LCD_VoidInit();

	// ADC initialization
	ADC_VoidInit();

	// External interrupt initialization
	EXTI_VoidEnableGIE();                            // Enable GIE (Globale Interrupt Enable)
	int interrupts[1] = {0};						 // Array to hold interrupts numbers
	EXTI_VoidInit(interrupts);                       // Initialize external enterrupt (EXTI)
	DIO_VoidSetPinDirection(PORT_D, PIN2, INPUT);    // Set INT0 pin as input
	DIO_VoidSetPinValue(PORT_D, PIN2, HIGH);         // Activate internal pull up resistance

	// Directions initialization for led and buzzer
	DIO_VoidSetPinDirection(PORT_B, PIN0, OUTPUT);   // Set direction as output for the first LED
	DIO_VoidSetPinDirection(PORT_B, PIN1, OUTPUT);   // Set direction as output for the buzzer
	DIO_VoidSetPinDirection(PORT_D, PIN3, OUTPUT);   // Set direction as output for the second led
	DIO_VoidSetPinDirection(PORT_D, PIN4, OUTPUT);   // Set direction as output for the dc motor
}

// Main function
void main(void)
{
	// Initialize the system HAL and MCAL
	System_init();

	// Variables initialization
	u16 digital_value, analog_value;    // ADC digital and analog reading values
	u16 previous_temperature = 0xFFFF;  // Initialize with a value that's unlikely to be a valid temperature

	// Turn on stability mode led by default
	DIO_VoidSetPinValue(PORT_D, PIN3, HIGH);

	// Program loop
	while(1)
	{
		// Get ADC digital reading and convert it into analog
		digital_value = ADC_u16ReadValue(0);
		analog_value = ADC_u16ToTemp(digital_value);

		// Check if the temperature has changed
		if (analog_value != previous_temperature)
		{
			// Update the previous temperature value
			previous_temperature = analog_value;

			// Normal temperature state (no danger)
			if(previous_temperature <= 35)
			{
				// Display temperature on LCD
				LCD_VoidWriteCommand(1);
				LCD_VoidSetPosition(0, 0);
				LCD_VoidWriteString("Temperature= ");
				LCD_VoidWriteNumber(analog_value);
				LCD_VoidWriteString("C");
			}

			// High temperature state (fire!)
			else if(previous_temperature > 35)
			{
				// Get emergency mode switch state
				u8 switch_state = DIO_U8GetPinValue(PORT_D, PIN2);

				// Emergency mode is off
				if(switch_state == 1)
				{
					// Display warning on LCD
					LCD_VoidWriteCommand(1);
					LCD_VoidWriteString("FIRE!, TURN ON");
					LCD_VoidSetPosition(1, 0);
					LCD_VoidWriteString("EMERGENCY MODE!");

					// Turn off stability mode led and motor
					DIO_VoidSetPinValue(PORT_D, PIN3, LOW);
					DIO_VoidSetPinValue(PORT_D, PIN4, LOW);

					// Turn on alarm (led and buzzer)
					DIO_VoidSetPinValue(PORT_B, PIN0, HIGH);
					DIO_VoidSetPinValue(PORT_B, PIN1, HIGH);
				}
				// Emergency mode is on : Go execute ISR of INT0
				else if(switch_state == 0)
				{
					// Stay in emergency mode until siwtch opened
					while(!DIO_U8GetPinValue(PORT_D, PIN2));
				}
			}
		}
		_delay_ms(10);
	}
}
